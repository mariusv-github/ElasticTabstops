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

#ifndef ELASTIC_TABSTOPS_H
#define ELASTIC_TABSTOPS_H

// All definitions of plugin interface
#include <vector>
#include <string>
#include "resource.h"
#include "PluginInterface.h"
#include "ETFile.h"

// Menu callbacks
void FctToggleEnabled();
void FctToggleSelOnly();
void FctToggleGlobTabs();
void FctConvEt2Spaces();
void FctConvSpaces2Et();
void FctToggleRemember();
void FctEditSettings();
void FctResetSettings();
void FctShowHelp();
void FctShowAbout();

__declspec(selectany) FuncItem funcItem[] ={
  { TEXT("Enable"), FctToggleEnabled, 0, false, nullptr },
  { TEXT("Selection only"), FctToggleSelOnly, 0, false, nullptr },
  { TEXT("Global tabs"), FctToggleGlobTabs, 0, false, nullptr },
  { TEXT(""), nullptr, 0, false, nullptr }, // separator
  { TEXT("Convert Elastic Tabs to Spaces"), FctConvEt2Spaces, 0, false, nullptr },
  { TEXT("Convert Spaces to Elastic Tabs"), FctConvSpaces2Et, 0, false, nullptr },
  { TEXT(""), nullptr, 0, false, nullptr }, // separator
  { TEXT("Remember enabled files"), FctToggleRemember, 0, false, nullptr },
  { TEXT("Save and edit default settings..."), FctEditSettings, 0, false, nullptr },
  { TEXT("Reset and save default settings"), FctResetSettings, 0, false, nullptr },
  { TEXT("Help..."), FctShowHelp, 0, false, nullptr },
  { TEXT("About..."), FctShowAbout, 0, false, nullptr }
};
static const size_t NB_FUNCS=sizeof(funcItem)/sizeof(*funcItem);
enum FctIdx { IdxToggleEnabled=0, IdxToggleSelOnly, IdxToggleGlobTabs, IdxSep1, IdxConvEt2Spaces, IdxConvSpaces2Et, IdxSep2, IdxToggleRemember, IdxEditSettings, IdxResetSettings, IdxShowHelp, IdxShowAbout, LastFctIdx };
static_assert(NB_FUNCS==LastFctIdx, "Incompatible funcItem table size with FctIdx");

class NppPlugin
{
public:
  static const TCHAR NPP_PLUGIN_NAME[];
  static HMODULE hModule;
  static NppData nppData;

  static LRESULT SendMessageNPP(UINT Msg, WPARAM wParam, LPARAM lParam) { return SendMessage(nppData._nppHandle, Msg, wParam, lParam); }
  static bool IsInNppData(HWND hWnd) { return hWnd==nppData._nppHandle||hWnd==nppData._scintillaMainHandle||hWnd==nppData._scintillaSecondHandle; }
  static void SetDirect()
  {
    ScintillaEditor::SetDirect(nppData._scintillaMainHandle, 0);
    ScintillaEditor::SetDirect(nppData._scintillaSecondHandle, 1);
  }
  static HWND GetCurrentScintilla()
  {
    int id;
    SendMessageNPP(NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&id);
    return id ? nppData._scintillaSecondHandle : nppData._scintillaMainHandle;
  }
  static const char* IsWho(HWND hWnd)
  {
    if(hWnd==nppData._nppHandle) return "NPP  ";
    if(hWnd==nppData._scintillaMainHandle) return "SCI_1";
    if(hWnd==nppData._scintillaSecondHandle) return "SCI_2";
    return "UNK??";
  }
  static int IdxView(HWND hWnd) { return hWnd==nppData._scintillaMainHandle ? 0: (hWnd==nppData._scintillaSecondHandle ? 1:-1);  }
  static void DumpOpenFilenames()
  {
    // WARNING: NPP bug (or special design) but initially SECOND_VIEW return 1 file name and the output buffer in never fill-in !!!
    size_t nbFiles1=(size_t)SendMessageNPP(NPPM_GETNBOPENFILES, 0, PRIMARY_VIEW);
    size_t nbFiles2=(size_t)SendMessageNPP(NPPM_GETNBOPENFILES, 0, SECOND_VIEW);
    size_t nbFiles=nbFiles1+nbFiles2;
    TCHAR** fnames=new TCHAR*[nbFiles];
    fnames[0]=new TCHAR[nbFiles*MAX_PATH];
    memset(fnames[0], 0, nbFiles*MAX_PATH*sizeof(TCHAR));
    for(size_t i=1; i<nbFiles; i++) fnames[i]=fnames[0]+i*MAX_PATH;
    size_t nbFiles1_=SendMessageNPP(NPPM_GETOPENFILENAMESPRIMARY, (WPARAM)fnames, (LPARAM)nbFiles1);
    size_t nbFiles2_=SendMessageNPP(NPPM_GETOPENFILENAMESSECOND, (WPARAM)fnames+nbFiles1, (LPARAM)nbFiles2);
    if(nbFiles1_!=nbFiles1||nbFiles2_!=nbFiles2) { /*cout<<"Invalid file numbers\n";*/ return; }
#ifdef USE_CONSOLE
    using namespace std;
    cout<<"  "<<nbFiles1<<" files in PRIMARY VIEW:\n";
    for(size_t i=0; i<nbFiles1; i++)
      cout<<"  * "<<setw(4)<<_tcslen(fnames[i])<<" \""<<fnames[i]<<"\"\n";
    cout<<"  "<<nbFiles1<<" files in SECONDARY VIEW:\n";
    for(size_t i=0; i<nbFiles2; i++)
      cout<<"  * "<<setw(4)<<_tcslen(fnames[nbFiles1+i])<<" \""<<fnames[nbFiles1+i]<<"\"\n";
#endif
    delete[] fnames[0]; delete[] fnames;
  }
};
__declspec(selectany) const TCHAR NppPlugin::NPP_PLUGIN_NAME[] = _T("Elastic Tabstops");
__declspec(selectany) HMODULE NppPlugin::hModule;                   // init in DllMain / DLL_PROCESS_ATTACH
__declspec(selectany) NppData NppPlugin::nppData;                  // init in setInfo

class ConfigManager: public NppPlugin
{
public:
  // global (default) settings
  //bool enabled;                // default value: false // redundant parameter (!* do the same job)
  bool selOnly;                // default value: true
  bool globTabs;               // default value: true
  bool keepLeadingTabs;        // default value: false
  bool rememberEnabledFiles;   // default value: false
  size_t minPadding;           // default value: 1
  // in this version 1.4.x no extensions (empty vector) means no file type is enable, and Reset enforces this by adding "!*" to the empty vector
  std::vector<std::wstring> file_extensions;
  
  std::vector<ETFile> fileCfg;
  DWORD fgIdx[2]={DWORD(-1),DWORD(-1)};   // fileCfg 0-based index for each forground view (or -1 if none)
  DWORD fgView=-1;                        // 0-based index of 1st (or 2nd) Scintilla forground view

  void Reset()
  {
    //enabled=false;
    selOnly=true;
    globTabs=true;
    file_extensions.clear(); file_extensions.push_back(DEFAULT_EXTENSION);
    minPadding=1;
    keepLeadingTabs=false;
    rememberEnabledFiles=false;
  }
  ConfigManager() { Reset(); }
  bool IniIsOpened() const
  {
    size_t nbFiles=(size_t)SendMessageNPP(NPPM_GETNBOPENFILES, 0, ALL_OPEN_FILES);
    TCHAR** fnames=new TCHAR*[nbFiles];
    fnames[0]=new TCHAR[nbFiles*MAX_PATH];
    for(size_t i=1; i<nbFiles; i++) fnames[i]=fnames[0]+i*MAX_PATH;
    size_t nbFiles_=SendMessageNPP(NPPM_GETOPENFILENAMES, (WPARAM)fnames, (LPARAM)nbFiles);
    //std::cout<<__FUNCDNAME__ " # of opened files_="<<nbFiles_<<"\n";
    bool found=false;
    for(size_t i=0; i<nbFiles_-1; i++)
    {
      //std::cout<<"File "<<fnames[i]<<"\n";
      if(_tcscmp(fnames[i], iniFilePath)==0) { found=true; break; }
    }
    delete[] fnames[0]; delete[] fnames;
    return found;
  }
  bool LoadIni()
  {
    //iniFile.Read(INI_SECTION_NAME, ENABLED_NAME, enabled);
    iniFile.Read(INI_SECTION_NAME, SELECTION_ONLY_NAME, selOnly);
    iniFile.Read(INI_SECTION_NAME, GLOBAL_TABS_NAME, globTabs);
    iniFile.Read(INI_SECTION_NAME, MIN_PADDING_NAME, minPadding, (size_t)1, (size_t)255);
    iniFile.Read(INI_SECTION_NAME, KEEP_LEADING_TABS_NAME, keepLeadingTabs);
    iniFile.Read(INI_SECTION_NAME, REMEMBER_ENABLED_FILES_NAME, rememberEnabledFiles);
    iniFile.ReadVect(INI_SECTION_NAME, EXTENSIONS_NAME, file_extensions);
    if(file_extensions.empty()) file_extensions.push_back(DEFAULT_EXTENSION);
    return true;
  }
  bool SaveIni() const
  {
    //iniFile.Write(INI_SECTION_NAME, _T("Comment"), _T("Default configuration for ElasticTabstops"));
    //iniFile.Write(INI_SECTION_NAME, ENABLED_NAME, enabled);
    iniFile.Write(INI_SECTION_NAME, SELECTION_ONLY_NAME, selOnly);
    iniFile.Write(INI_SECTION_NAME, GLOBAL_TABS_NAME, globTabs);
    iniFile.Write(INI_SECTION_NAME, MIN_PADDING_NAME, (int)minPadding);
    iniFile.Write(INI_SECTION_NAME, KEEP_LEADING_TABS_NAME, keepLeadingTabs);
    iniFile.Write(INI_SECTION_NAME, REMEMBER_ENABLED_FILES_NAME, rememberEnabledFiles);
    iniFile.WriteVect(INI_SECTION_NAME, EXTENSIONS_NAME, file_extensions);
    return true;
  }
  void GetIniFilePath()
  {
    // the unique initialisation of iniFilePath
    SendMessageNPP(NPPM_GETPLUGINSCONFIGDIR, MAX_PATH-_tcslen(INI_PATH_SUFFIX), (LPARAM)iniFilePath);
    _tcscat_s(iniFilePath, MAX_PATH, INI_PATH_SUFFIX);
  }
  bool IsIniFilePath(const TCHAR* fname) const { return _tcscmp(fname, iniFilePath)==0; }
  // compare config options with a specific extension (".ext")
  bool shouldEnableExt(const TCHAR* ext) const
  {
    for(const auto &extension:file_extensions)
    {
      if(extension==_T("*")) return true;
      if(extension==_T("!*")) return false;
      bool not = (extension[0]==_T('!'));
      if(_tcsicmp(ext, extension.c_str()+not)==0) return !not;
    }
    return false;
  }
  bool shouldEnableFile(const TCHAR* fname) const
  {
    const TCHAR* p=_tcsrchr(fname, _T('.'));
    if(!p) p=fname+_tcslen(fname);
    return shouldEnableExt(p);
  }
  int AddFile(const TCHAR* fname, unsigned idxView, DWORD posIdx)
  {
    for(int i=0; i<(int)fileCfg.size(); i++)
    {
      ETFile& cfg=fileCfg[i];
      if(_tcscmp(cfg.fname, fname)==0)
      {
        cfg.isDirty=true; /*(cfg.idxView!=idxView)*/
        cfg.idxView=idxView;
        cfg.posIdx=posIdx;
        return i;
      }
    }
    // Priority : individual settings > extension settings > global/defaut enabled
    bool ext_enabled=shouldEnableFile(fname);
    fileCfg.emplace_back(idxView, ext_enabled /*|| enabled*/, selOnly, globTabs, true, posIdx, fname);
    if(rememberEnabledFiles) fileCfg.back().ReadFromIni(iniFile);
    return (int)fileCfg.size()-1;
  }
  int FindFile(const TCHAR* fname)
  {
    for(int i=0; i<(int)fileCfg.size(); i++)
    {
      ETFile& cfg=fileCfg[i];
      if(_tcscmp(cfg.fname, fname)==0) return i;
    }
    return -1;
  }
#ifdef USE_CONSOLE
  void DumpFiles(std::ostream& os)
  {
    os<<"  "; ETFile::DumpHeader(os);
    for(size_t i=0; i<fileCfg.size(); i++) os<<fileCfg[i];
  }
#endif
  void UpdateMenu(ETFile& cfg)
  {
    SendMessageNPP(NPPM_SETMENUITEMCHECK, funcItem[IdxToggleEnabled]._cmdID, cfg.enabled);
    SendMessageNPP(NPPM_SETMENUITEMCHECK, funcItem[IdxToggleSelOnly]._cmdID, cfg.selOnly);
    SendMessageNPP(NPPM_SETMENUITEMCHECK, funcItem[IdxToggleGlobTabs]._cmdID, cfg.globTabs);
    EnableMenuItem(GetMenu(NppPlugin::nppData._nppHandle), funcItem[IdxConvEt2Spaces]._cmdID, cfg.enabled ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(GetMenu(NppPlugin::nppData._nppHandle), funcItem[IdxConvSpaces2Et]._cmdID, cfg.enabled ? MF_ENABLED : MF_GRAYED);
  }
  void OnNppBufferActivated(SCNotification *notify)
  {
    TCHAR fg_fname[MAX_PATH] ={0};
    SendMessageNPP(NPPM_GETFULLPATHFROMBUFFERID, notify->nmhdr.idFrom, (LPARAM)fg_fname);
    LRESULT res=SendMessageNPP(NPPM_GETPOSFROMBUFFERID, notify->nmhdr.idFrom, (LPARAM)fg_fname);
    if(res==-1) return; // internal/unexpected error
    fgView= DWORD(res)>>30;
    DWORD posIdx=DWORD(res)&0x3FFFFFFF;
    if(fgView>1||posIdx>256) return; // unexpected data
    fgIdx[fgView]=AddFile(fg_fname, fgView, posIdx);
    UpdateMenu(fileCfg[fgIdx[fgView]]);
#ifdef USE_CONSOLE
    std::cout<<"  "<<(fgView ? "SEC":"PRI")<<"["<<std::setw(2)<<fgIdx[fgView]<<"] \""<<fg_fname<<"\"\n";
    DumpFiles(std::cout);
#endif
  }
  void OnScnModified(SCNotification *notify)
  {
    // mark for update current forground view if it exist
    int idxView=IdxView((HWND)notify->nmhdr.hwndFrom);
    if(idxView==-1||fgIdx[idxView]==-1) return;
    fileCfg[fgIdx[idxView]].isDirty=true;
  }
  void OnScnZoom(SCNotification *notify)
  {
    // mark for update current forground view if it exist
    int idxView=IdxView((HWND)notify->nmhdr.hwndFrom);
    if(idxView==-1||fgIdx[idxView]==-1) return;
    fileCfg[fgIdx[idxView]].isDirty=true;
  }
  void OnNppWordStyleUpdated(SCNotification *notify)
  {
    // mark for update both views if they exist
    if(fgIdx[0]!=-1) fileCfg[fgIdx[0]].isDirty=true;
    if(fgIdx[1]!=-1) fileCfg[fgIdx[1]].isDirty=true;
  }
  void OnScnUpdateUI(SCNotification *notify)
  {
    // compute current forground view if it exist
    int idxView=IdxView((HWND)notify->nmhdr.hwndFrom);
    if(idxView==-1||fgIdx[idxView]==-1) return;
    ETFile& cfg=fileCfg[fgIdx[idxView]];
    UpdateMenu(cfg);
    SendMessageNPP(NPPM_SETMENUITEMCHECK, funcItem[IdxToggleRemember]._cmdID, rememberEnabledFiles);
#ifdef USE_CONSOLE
    std::cout<<"  "<<(idxView ? "SEC":"PRI")<<"["<<std::setw(2)<<fgIdx[idxView]<<"]:"<<cfg;
#endif
    if(!cfg.enabled) return;
    cfg.ComputeView();
  }
  void OnFileSaved(SCNotification *notify)
  {
    if(fgView==-1||fgIdx[fgView]==-1) return;
    TCHAR fname[MAX_PATH] ={0};
    LRESULT res=SendMessageNPP(NPPM_GETFULLPATHFROMBUFFERID, notify->nmhdr.idFrom, (LPARAM)fname);
#ifdef USE_CONSOLE
    std::cout<<"  Result = "<<int(res)<<"file from BufID: \""<<fname<<"\"\n";
#endif
    if(!fname[0]) return;
    if(_tcscmp(fname, fileCfg[fgIdx[fgView]].fname)!=0) _tcscpy(fileCfg[fgIdx[fgView]].fname, fname);
    if(!IsIniFilePath(fileCfg[fgIdx[fgView]].fname)) return;
    LoadIni(); // global settings change do not apply to current opened files but only to new opened files
    ::MessageBox(nppData._nppHandle, _T("Default settings will be applied only to new opened files"), _T("Information"), MB_OK|MB_ICONINFORMATION);
    return;
  }
  void OnFileClosed(SCNotification *notify)
  {
    // BUG NPP: NPPM_GETFULLPATHFROMBUFFERID always failed with notify->nmhdr.idFrom !!!
  }
  void OnFileBeforeClosed(SCNotification *notify)
  {
    TCHAR fname[MAX_PATH] ={0};
    LRESULT res=SendMessageNPP(NPPM_GETFULLPATHFROMBUFFERID, notify->nmhdr.idFrom, (LPARAM)fname);
    //std::cout<<"  Result = "<<int(res)<<"file from BufID: \""<<fname<<"\"\n";
    if(!fname[0]) return;
    int idx=FindFile(fname);
    if(idx==-1) { ::MessageBox(nppData._nppHandle, _T("Closing file wasn't registed"), _T("Warning"), MB_OK|MB_ICONWARNING); return; }
    for(int i=0; i<2; i++)
      if(fgIdx[i]!=-1)
      {
        if(fgIdx[i]>DWORD(idx)) fgIdx[i]--;
        else if(fgIdx[i]==DWORD(idx)) fgIdx[i]=-1;
      }
    if(rememberEnabledFiles) fileCfg[idx].WriteToIni(iniFile);
    fileCfg.erase(fileCfg.begin()+idx);
  }
  void OnToggleEnabled(int cmdID)
  {
    if(fgView==-1||fgIdx[fgView]==-1) return;
    ETFile& cfg=fileCfg[fgIdx[fgView]];
    SendMessageNPP(NPPM_SETMENUITEMCHECK, cmdID, cfg.enabled=!cfg.enabled);
    EnableMenuItem(GetMenu(NppPlugin::nppData._nppHandle), funcItem[IdxConvEt2Spaces]._cmdID, cfg.enabled ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(GetMenu(NppPlugin::nppData._nppHandle), funcItem[IdxConvSpaces2Et]._cmdID, cfg.enabled ? MF_ENABLED : MF_GRAYED);
    if(cfg.enabled) { cfg.isDirty=true; cfg.ComputeView(); }
    else cfg.ClearAllTabstops(); // Clear all tabstops on the file
  }
  void OnToggleSelOnly(int cmdID)
  {
    if(fgView==-1||fgIdx[fgView]==-1) return;
    ETFile& cfg=fileCfg[fgIdx[fgView]];
    SendMessageNPP(NPPM_SETMENUITEMCHECK, cmdID, cfg.selOnly=!cfg.selOnly);
    if(cfg.enabled) { cfg.isDirty=true; cfg.ComputeView(); }
  }
  void OnToggleGlobTabs(int cmdID)
  {
    if(fgView==-1||fgIdx[fgView]==-1) return;
    ETFile& cfg=fileCfg[fgIdx[fgView]];
    SendMessageNPP(NPPM_SETMENUITEMCHECK, cmdID, cfg.globTabs=!cfg.globTabs);
    if(cfg.enabled) { cfg.isDirty=true; cfg.ComputeView(); }
  }
  void OnToggleRemember(int cmdID)
  {
    SendMessageNPP(NPPM_SETMENUITEMCHECK, cmdID, rememberEnabledFiles=!rememberEnabledFiles);
  }
  void OnConvEt2Spaces()
  {
    if(fgView==-1||fgIdx[fgView]==-1) return;
    ETFile& cfg=fileCfg[fgIdx[fgView]];
    if(!cfg.enabled) return;
// Temporarily disable elastic tabstops because replacing tabs with spaces causes Scintilla to send notifications of all the changes.
    cfg.enabled = false;
    cfg.ComputeView();
    cfg.ReplaceTabs();
    cfg.enabled = true;
  }
  void OnConvSpaces2Et()
  {
    if(fgView==-1||fgIdx[fgView]==-1) return;
    ETFile& cfg=fileCfg[fgIdx[fgView]];
    if(!cfg.enabled) return;
// Temporarily disable elastic tabstops because replacing spaces with tabs causes Scintilla to send notifications of all the changes.
    cfg.enabled = false;
    cfg.ReplaceSpaces();
    cfg.ComputeView();
    cfg.enabled = true;
  }
  void OnEditSettings()
  {
    if(IniIsOpened())
    { if(::MessageBox(nppData._nppHandle, _T("The config file is already open\nOverwrite the current editted settings ?"), _T("Warning"), MB_OKCANCEL|MB_ICONWARNING)==IDCANCEL) return; }
    SaveIni();
    SendMessageNPP(NPPM_DOOPEN, 0, (LPARAM)iniFilePath);
  }
  void ShowHelp()
  {
    HRSRC hRsrc=::FindResource(hModule, MAKEINTRESOURCE(IDR_TEXT1), _T("Text"));
    HGLOBAL hGlob=::LoadResource(hModule, hRsrc);
    void* pTxt=::LockResource(hGlob);
    DWORD TxtSz=::SizeofResource(hModule, hRsrc);
    if(!pTxt||TxtSz==0) return;
    TCHAR filePath[MAX_PATH]={};
    const TCHAR fileName[]=_T("ElasticTabstops.txt");
    DWORD sz=::GetTempPath(MAX_PATH, filePath);
    if(sz>=MAX_PATH-_tcslen(fileName)||sz==0) return;
    _tcscat(filePath, fileName);
    HANDLE hf=::CreateFile(filePath, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL/*FILE_ATTRIBUTE_TEMPORARY|FILE_FLAG_DELETE_ON_CLOSE*/, 0);
    if(hf==INVALID_HANDLE_VALUE) return;
    DWORD nbWritten=0;
    ::WriteFile(hf, pTxt, TxtSz, &nbWritten, 0);
    ::CloseHandle(hf);
    SendMessageNPP(NPPM_DOOPEN, 0, (LPARAM)filePath);
    ::DeleteFile(filePath);
  }
  void OnReset()
  {
    if(::MessageBox(nppData._nppHandle, _T("Are you sure to reset default settings\nand clean individual file settings ?"), _T("Warning"), MB_YESNO)==IDNO) return;
    Reset();
    ::DeleteFile(iniFilePath);
    SaveIni();
  }

  static const TCHAR INI_PATH_SUFFIX[];
  static TCHAR iniFilePath[MAX_PATH];
  static IniFile iniFile;
  static const TCHAR DEFAULT_EXTENSION[];
  static const TCHAR INI_SECTION_NAME[];
  static const TCHAR ENABLED_NAME[];
  static const TCHAR SELECTION_ONLY_NAME[];
  static const TCHAR GLOBAL_TABS_NAME[];
  static const TCHAR MIN_PADDING_NAME[];
  static const TCHAR KEEP_LEADING_TABS_NAME[];
  static const TCHAR EXTENSIONS_NAME[];
  static const TCHAR REMEMBER_ENABLED_FILES_NAME[];
};
// Global data
__declspec(selectany) const TCHAR ConfigManager::INI_PATH_SUFFIX[] = _T("\\ElasticTabstops.ini");
__declspec(selectany) TCHAR ConfigManager::iniFilePath[MAX_PATH]={0};  // init in GetIniFilePath from setInfo
__declspec(selectany) IniFile ConfigManager::iniFile(iniFilePath);
__declspec(selectany) const TCHAR ConfigManager::DEFAULT_EXTENSION[] = _T("!*"); // default: no file
__declspec(selectany) const TCHAR ConfigManager::INI_SECTION_NAME[] = _T("Default settings");
__declspec(selectany) const TCHAR ConfigManager::ENABLED_NAME[] =_T("enable");
__declspec(selectany) const TCHAR ConfigManager::SELECTION_ONLY_NAME[] =_T("sel_only");
__declspec(selectany) const TCHAR ConfigManager::GLOBAL_TABS_NAME[] =_T("glob_tabs");
__declspec(selectany) const TCHAR ConfigManager::MIN_PADDING_NAME[] =_T("min_padding");
__declspec(selectany) const TCHAR ConfigManager::KEEP_LEADING_TABS_NAME[] =_T("keep_leading_tabs");
__declspec(selectany) const TCHAR ConfigManager::EXTENSIONS_NAME[] =_T("extensions");
__declspec(selectany) const TCHAR ConfigManager::REMEMBER_ENABLED_FILES_NAME[] =_T("remember_enabled_files");
__declspec(selectany) ConfigManager elTabs;


#endif //ELASTIC_TABSTOPS_H


