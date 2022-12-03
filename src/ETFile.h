// This file is part of ElasticTabstops.
// 
// Copyright (C)2016 Justin Dailey <dail8859@yahoo.com>,
// Copyright (C)2022 Marius Vasiliu <Polytech Paris Saclay>
// 
// ElasticTabstops is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software Foundation;
// either version 2 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef _ET_FILE_
#define _ET_FILE_
#include <iostream>
#include <iomanip>
#include <stdio.h>
// using fast ATL W/A/T -> W/A/T macro conversions
#include <ATLBase.h>
#include "Util.h"
#include "ScintillaEditor.h"
#define MY_DEBUG 1

inline std::ostream& operator<<(std::ostream& os, const wchar_t* wstr) { USES_CONVERSION; os<<W2A(wstr); return os; }

// In this version (1.4) the text range between the line start or a tab and the next tab or the line end is called **item**.
// (In the precedent versions it was a confusion between the Scintilla cell (a pair character+format) and the ElasticTabstops item called sometimes cell too...)
// Each item can have or not an ending tab (normally the last item in a line do not have one but in ElasticTabstops
//   there is no different traitement between last items in a line with or without an ending tab).
// Each item has an 0-based index and items with the same index from different lines form **columns**.
// Columns can be sparse, and this is more likely for higher indexes. A compact zone in a column without absent item is called **column block**.
// So any column is composed of one or more column blocks separated by absent (void) items.
// The **item width** is measured without the next tab, while the **column width** is the width of an item text with its next elastic tab.
// Elastic Tabstops detect and automatically adjust/maximize tab-stop positions in the current range (globally or current selection)
// so successive column widths being the same using one of two possible strategies :
// [1] Global (uniform, unique) tab-stop positions per column
//     Every item in the current range with the same index will have a unique column width
//     The width of each column is determined by the larger item width (in this column) + minimum tab width padding (a user option)
// [2] Local blocks (neighbors) on the same column with uniform tab-stop positions
//     Every item in the current range will have the same column width as the next or previous neighbor with the same index
//     but different column blocks of the same column can have different width.
//     The width of each column block is determined by the larger item width (in this block) + minimum tab width padding (a user option)
// Both strategies can be quite compute intensive and can slow down Notepad++ responsiveness for very big files.
// We recommend to keep activated size and line number thresholds, adapted to your CPU/memory speed.

class ETFile: public ScintillaEditor
{
public:
  // current configuration for a opened file
  bool enabled;          // ElasticTabstops enabled (or disabled)
  bool selOnly;          // only on current selection (or global file)
  bool globTabs;         // global (or local) strategy
  bool isDirty;          // must be recomputed (or not)
  DWORD posIdx;          // index position inside 1st/2nd Scintilla view
  Sci_Position startLine, endLine; // keep the last computed region
  TCHAR fname[MAX_PATH]; // full path file name

  ETFile(unsigned idxView, bool _enabled, bool _selOnly, bool _globTabs, bool _isDirty, DWORD _posIdx, const TCHAR* _fname):
    ScintillaEditor(idxView), enabled(_enabled), selOnly(_selOnly), globTabs(_globTabs), isDirty(_isDirty), posIdx(_posIdx), startLine(0), endLine(0)
  { _tcscpy(fname, _fname); }
#ifdef USE_CONSOLE
  void Dump(std::ostream& os) const
  {
    using namespace std;
    os<<setiosflags(ios::boolalpha)<<setw(6)<<enabled<<setw(6)<<selOnly<<setw(6)<<globTabs<<setw(6)<<isDirty<<setw(6)<<posIdx<<setw(6)<<startLine<<setw(7)<<endLine<<"  \""<<fname<<"\"\n";
  }
  static void DumpHeader(std::ostream& os)
  {
    os<<"enb   sel   glob  dirty posIdx startL endL fname\n";
  }
#endif
  bool FilterName(TCHAR (&_fname)[MAX_PATH]) const
  {
    // filter non-saved files like "new 1" etc.
    if(_tcslen(fname)<=2||fname[1]!=_T(':')) return false;
    // replace '[' by '<' and ']' by '>' in INI section name
    _tcscpy_s(_fname, fname);
    for(TCHAR* p=_fname; *p; ++p) { if(*p==_T('[')) *p=_T('<'); else if(*p==_T(']')) *p=_T('>'); }
    return true;
  }
  bool WriteToIni(IniFile& ini) const
  {
    TCHAR _fname[MAX_PATH];
    if(!FilterName(_fname)) return false;
    if(enabled)
    {
      ini.Write(_fname, SELECTION_ONLY_NAME, selOnly);
      ini.Write(_fname, GLOBAL_TABS_NAME, globTabs);
    }
    else ini.Write(_fname, 0, 0); // delete an eventually section of this file
    return true;
  }
  bool ReadFromIni(IniFile& ini)
  {
    TCHAR _fname[MAX_PATH];
    if(!FilterName(_fname)) return false;
    if(!ini.Read(_fname, SELECTION_ONLY_NAME, selOnly) ||
       !ini.Read(_fname, GLOBAL_TABS_NAME, globTabs)) return false;
    return enabled=true;
  }

private:
  struct ItemData
  {
    int itemWidth, maxWidth;  // item width and column width then cumulated in tabstop position
    Sci_Position tabPos;      // tab position or INVALID_POSITION if item without tab
  };
  // data about all items, created by MeasureCells and used by StretchTabstops and ReplaceTabs
  std::vector<std::vector<ItemData>> grid;
  // Initialised by SwitchToScintilla from ScintillaEditor::TextWidth, used by get_text_width_mono, SwitchToScintilla, ConvertToSpaces
  int charWidth;
  // both initialized by SwitchToScintilla and used by Item2ColWidth
  int tab_width_minimum, tab_width_padding; // min_padding converted in pixels

  int Item2ColWidth(int text_width_in_tab)
  {
    text_width_in_tab = __max(text_width_in_tab, tab_width_minimum);
    return text_width_in_tab+tab_width_padding;
  }
  //Sci_Position FindLineStart(Sci_Position pos) { return PositionFromLine(LineFromPosition(pos)); }
  //Sci_Position FindLineEnd(Sci_Position pos)   { return GetLineEndPosition(LineFromPosition(pos)); }
  int GetTextWidth(Sci_Position start, Sci_Position end)
  {
    std::string s(end-start+1, 0);
    Sci_TextRangeFull range;
    range.chrg.cpMin = start;
    range.chrg.cpMax = end;
    range.lpstrText = &s[0];
    GetTextRange(&range);
    int style = GetStyleAt(start);
    return TextWidth(style, range.lpstrText);
  }
  void StretchTabstops()
  {
    grid.clear();
    grid.resize(endLine-startLine);
    if(startLine>endLine||grid.size()!=endLine-startLine) return;
    std::vector<int> maxColWidth; // used only if globTabs==true
    for(Sci_Position line=startLine; line<endLine; line++)
    {
      const Sci_Position lineEnd = GetLineEndPosition(line);
      Sci_Position currentPos = PositionFromLine(line);
      Sci_Position itemStart = currentPos;
      size_t idx=0;
      while(currentPos!=lineEnd)
      {
        bool isTab= ('\t'==(unsigned char)GetCharAt(currentPos));
        Sci_Position nextPos=PositionAfter(currentPos);
        if(isTab||nextPos==lineEnd)
        {
          // if last item has no ending tab then count current char in the text width
          if(!isTab && nextPos==lineEnd) currentPos=nextPos;
          int itemWidth=(itemStart==currentPos)?0:GetTextWidth(itemStart, currentPos);
          int maxWidth=Item2ColWidth(itemWidth);
          if(line>startLine && grid[line-startLine-1].size()>idx)
            maxWidth=__max(maxWidth, grid[line-startLine-1][idx].maxWidth);
          if(globTabs) // keep max width of each column in maxColWidth
          {
            if(maxColWidth.size()>idx) maxColWidth[idx]=__max(maxColWidth[idx], maxWidth);
            else maxColWidth.push_back(maxWidth);
          }
          grid[line-startLine].push_back({itemWidth, maxWidth, (isTab ? currentPos: INVALID_POSITION)});
          itemStart=nextPos;
          idx++;
        }
        currentPos = nextPos;
      }
    }
    if(globTabs)
    {
      // cumule global tabstop positions
      for(size_t i=1; i<maxColWidth.size(); i++) maxColWidth[i]+=maxColWidth[i-1];
      // diffuse over all items
      for(size_t i=0; i<grid.size(); i++)
        for(size_t j=0; j<grid[i].size(); j++) grid[i][j].maxWidth=maxColWidth[j];
    }
    else
    {
      // locally cumulating and back-tracking over preceding items
      for(size_t i=grid.size(); i-->0; )
      {
        for(size_t j=0; j<grid[i].size(); j++)
          if(i+1<grid.size()&&grid[i+1].size()>j) grid[i][j].maxWidth=grid[i+1][j].maxWidth; // if exist South item
          else grid[i][j].maxWidth+=(j ? grid[i][j-1].maxWidth : 0);                         // else use West item
      }
    }
    for(Sci_Position line=startLine; line<endLine; line++)
      for(size_t i=0; i<grid[line-startLine].size(); i++) AddTabStop(line, grid[line-startLine][i].maxWidth);
    //DumpGrid();
  }
#ifdef USE_CONSOLE
  void DumpGrid()
  {
    using namespace std;
    cout<<"Grid of "<<grid.size()<<" lines (charWidth = "<<charWidth<<" pixels) strategy:"<<(globTabs?"GLOBAL":"LOCAL")<<"\n";
    for(size_t i=0; i<grid.size(); i++)
    {
      for(size_t j=0;j<grid[i].size();j++) cout<<setw(3)<<grid[i][j].itemWidth<<'/'<<setw(3)<<grid[i][j].maxWidth<<(grid[i][j].tabPos==INVALID_POSITION?' ':'*')<<' ';
      cout<<'\n';
    }
  }
#endif
public:
  void ClearAllTabstops(Sci_Position startLine=0, Sci_Position endLine=-1)
  {
    Sci_Position lineCount=GetLineCount();
    if(endLine<0 || endLine>lineCount) endLine=lineCount;
    if(startLine<0) startLine=0;
    for(Sci_Position i=startLine; i<endLine; ++i) ClearTabStops(i);
  }
  void ReplaceTabs()
  {
    std::string spaces;
    BeginUndoAction();
    ClearAllTabstops();
    // replace tabs in reverse order
    for(size_t i=grid.size(); i-->0; )
    {
      for(size_t j=grid[i].size(); j-->0; )
      {
        if(grid[i][j].tabPos==INVALID_POSITION) continue;
        SetTargetRange(grid[i][j].tabPos, grid[i][j].tabPos+1);
        int width=(grid[i][j].maxWidth-(j?grid[i][j-1].maxWidth:0)-grid[i][j].itemWidth)/charWidth;
        if(width>int(spaces.length())) spaces.resize(width, ' ');
        ReplaceTarget(width, &spaces[0]);
      }
    }
    EndUndoAction();
  }
  void ReplaceSpaces()
  {
#if 0
    Sci_Position startPos=0, endPos;
    if(selOnly)
    {
      SetTargetEnd(startPos=PositionFromLine(LineFromPosition(GetSelectionStart())));
      SetTargetStart(endPos=GetLineEndPosition(LineFromPosition(GetSelectionEnd())));
    }
    else
    {
      TargetWholeDocument();
      SetTargetStart(endPos=GetTargetEnd());
      SetTargetEnd(0);
    }
    if(endPos-startPos>NB_LINES_TH && ::MessageBox(0/*NppPlugin::nppData._nppHandle*/, _T("Replacing spaces in more than 1000 lines can block you editor\n for a long time. Are you sure (and patient) to doing this?"),
      _T("Warning"), MB_YESNO|MB_ICONWARNING)==IDNO) return;
    const char tab[]="\t";
    const char spaces[]=" +";
    size_t spaces_sz=strlen(spaces);
    BeginUndoAction();
    // TODO: this search and replace method is very slow, to be replaced by a direct scan + reverse replace
    // replace spaces in reverse order
    SetSearchFlags(SCFIND_REGEXP);
    while(SearchInTarget(spaces_sz, spaces)!=-1)
    {
      ReplaceTarget(1, tab);
      SetTargetEnd(startPos);
    }
    EndUndoAction();
#else
    // this direct/manual search is much, much faster than the 2nd version (RegExp search/replacement)
    Sci_Position startPos=0, endPos;
    if(selOnly)
    {
      startPos=PositionFromLine(LineFromPosition(GetSelectionStart()));
      endPos=GetLineEndPosition(LineFromPosition(GetSelectionEnd()));
    }
    else
    {
      TargetWholeDocument();
      startPos=0;
      endPos=GetTargetEnd();
    }
    if(endPos-startPos>NB_LINES_TH && ::MessageBox(0/*NppPlugin::nppData._nppHandle*/, _T("Replacing spaces in more than 1000 lines can block you editor\nfor a long time. Are you sure (and patient) to doing this?"),
      _T("Warning"), MB_YESNO|MB_ICONWARNING)==IDNO) return;
    struct Range { Sci_Position start, end; };
    std::vector<Range> pos;
    bool first=true;
    for(Sci_Position currentPos=startPos, start; currentPos<endPos; currentPos=PositionAfter(currentPos))
    {
      bool isSpace= (' '==(unsigned char)GetCharAt(currentPos));
      if(isSpace)
      {
        if(first) { first=false; start=currentPos; }
      }
      else
      {
        if(!first) { first=true; pos.push_back({start,currentPos}); }
      }
    }
    const char tab[]="\t";
    BeginUndoAction();
    for(size_t i=pos.size(); i-->0;)
    {
      SetTargetStart(pos[i].start);
      SetTargetEnd(pos[i].end);
      ReplaceTarget(1, tab);
    }
    EndUndoAction();
#endif
  }
  // the default local processing v1.3 produce inconsistent results, function of screen size, file structure etc.
  // the only consistent behaviours are those based on well defined range
  // we will use two ranges : the global one (all the file) and the selected one (defined by the current selection)
  void ComputeView(int min_padding=1) // TODO: move min_padding and keep_leading_tabs
  {
    Sci_Position _startLine, _endLine;
    if(selOnly)
    {
      _startLine=LineFromPosition(GetSelectionStart());
      _endLine=LineFromPosition(GetSelectionEnd())+1;
    }
    else // global range
    {
      _startLine=0;
      _endLine=GetLineCount();
    }
#ifdef USE_CONSOLE
    std::cout<<"  ComputeView: "<<_startLine<<'('<<startLine<<") .. "<<_endLine<<'('<<endLine<<") Dirty="<<(isDirty?'Y':'N')<<" "<<(enabled?'o':'x')<<" "<<(selOnly?'o':'x')<<" "<<(globTabs?'o':'x')<<"\n";
#endif
    if(!isDirty && _startLine==startLine && _endLine==endLine) return;
    // Adjust widths based on space character width
    // The width of a tab is (tab_width_minimum + tab_width_padding)
    // Since the user can adjust the padding we adjust the minimum
    charWidth = TextWidth(STYLE_DEFAULT, " ");
    tab_width_padding = (int)(charWidth * min_padding);
    tab_width_minimum = __max(charWidth * GetTabWidth()-tab_width_padding, 0);
    ClearAllTabstops();
    startLine=_startLine, endLine=_endLine;
    isDirty=false;
    StretchTabstops();
  }
  static const TCHAR SELECTION_ONLY_NAME[];
  static const TCHAR GLOBAL_TABS_NAME[];
  static const Sci_Position NB_LINES_TH=1000;
};
__declspec(selectany) const TCHAR ETFile::SELECTION_ONLY_NAME[] =_T("sel_only");
__declspec(selectany) const TCHAR ETFile::GLOBAL_TABS_NAME[] =_T("glob_tabs");


#ifdef USE_CONSOLE
inline std::ostream& operator<<(std::ostream& os, const ETFile& f) { f.Dump(os); return os; }
#endif

#endif // _ET_FILE_
