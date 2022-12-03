// This file is part of {{ cookiecutter.plugin_name }}.
//
// Copyright (C){% now 'utc', '%Y' %} {{ cookiecutter.full_name }} <{{ cookiecutter.email }}>
// Copyright (C)2022 Marius Vasiliu <Polytech Paris Saclay>
//
// {{ cookiecutter.plugin_name }} is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#pragma once

#include <string>
#include <windows.h>
#include "Scintilla.h"

class ScintillaEditor
{
public:
  typedef int Colour;
  typedef int KeyModifier;
  struct Cell {
    unsigned char ch;
    unsigned char style;
  };
  static const unsigned DIRECT_SZ;
protected:
  struct Direct { SciFnDirect function; sptr_t pointer; };
  static const unsigned SCI_UNUSED=0;
  static Direct direct[];

	static inline void trim(std::string &s) { while (s.length() > 0 && s.back() == '\0') s.pop_back(); }

public:
  unsigned idxView;  // index of Scintilla editor view
	ScintillaEditor(unsigned _idxView=0):idxView(_idxView) {}
  template<typename T = uptr_t, typename U = sptr_t> inline sptr_t Call(unsigned int message, T wParam = 0, U lParam = 0) const
  {
		sptr_t retVal = direct[idxView].function(direct[idxView].pointer, message, (uptr_t)wParam, (sptr_t)lParam);
		return retVal;
	}
  static inline void SetDirect(HWND scintilla, unsigned idx)
  {
    if(idx>=DIRECT_SZ) return;
		direct[idx].function = (SciFnDirect)SendMessage(scintilla, SCI_GETDIRECTFUNCTION, 0, 0);
		direct[idx].pointer = SendMessage(scintilla, SCI_GETDIRECTPOINTER, 0, 0);
  }
  static inline void SetDirectPS(HWND primary, HWND second) { SetDirect(primary, 0); SetDirect(second, 1); }

	/* Start of section initially generated automatically from Scintilla.iface */
  /* Any used method was manually modified & tested by M.V. then prefixed by the following comment: */
  /* 2GB+ compatible, used by ElasticTabstops */
  /* Unused methods are in its original state (may be not 2GB+ compatible) -> to be validated or commented or deleted */

	void AddText(int length, const char* text) const {
		Call(SCI_ADDTEXT, length, text);
	}

	void AddText(const std::string& text) const {
		Call(SCI_ADDTEXT, text.length(), text.c_str());
	}

	void AddStyledText(int length, const Cell* c) const {
		Call(SCI_ADDSTYLEDTEXT, length, c);
	}

	void InsertText(int pos, const char* text) const {
		Call(SCI_INSERTTEXT, pos, text);
	}

	void InsertText(int pos, const std::string& text) const {
		Call(SCI_INSERTTEXT, pos, text.c_str());
	}

	void ChangeInsertion(int length, const char* text) const {
		Call(SCI_CHANGEINSERTION, length, text);
	}

	void ChangeInsertion(const std::string& text) const {
		Call(SCI_CHANGEINSERTION, text.length(), text.c_str());
	}

	void ClearAll() const {
		Call(SCI_CLEARALL, SCI_UNUSED, SCI_UNUSED);
	}

	void DeleteRange(int start, int lengthDelete) const {
		Call(SCI_DELETERANGE, start, lengthDelete);
	}

	void ClearDocumentStyle() const {
		Call(SCI_CLEARDOCUMENTSTYLE, SCI_UNUSED, SCI_UNUSED);
	}

	int GetLength() const {
		sptr_t res = Call(SCI_GETLENGTH, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
	int GetCharAt(Sci_Position pos) const {
		sptr_t res = Call(SCI_GETCHARAT, pos, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetCurrentPos() const {
		sptr_t res = Call(SCI_GETCURRENTPOS, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetAnchor() const {
		sptr_t res = Call(SCI_GETANCHOR, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  int GetStyleAt(Sci_Position pos) const {
		sptr_t res = Call(SCI_GETSTYLEAT, pos, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void Redo() const {
		Call(SCI_REDO, SCI_UNUSED, SCI_UNUSED);
	}

	void SetUndoCollection(bool collectUndo) const {
		Call(SCI_SETUNDOCOLLECTION, collectUndo, SCI_UNUSED);
	}

	void SelectAll() const {
		Call(SCI_SELECTALL, SCI_UNUSED, SCI_UNUSED);
	}

	void SetSavePoint() const {
		Call(SCI_SETSAVEPOINT, SCI_UNUSED, SCI_UNUSED);
	}

	int GetStyledText(Sci_TextRangeFull* tr) const {
		sptr_t res = Call(SCI_FORMATRANGEFULL/*SCI_GETSTYLEDTEXT*/, SCI_UNUSED, tr);
		return static_cast<int>(res);
	}

	bool CanRedo() const {
		sptr_t res = Call(SCI_CANREDO, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	int MarkerLineFromHandle(int markerHandle) const {
		sptr_t res = Call(SCI_MARKERLINEFROMHANDLE, markerHandle, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void MarkerDeleteHandle(int markerHandle) const {
		Call(SCI_MARKERDELETEHANDLE, markerHandle, SCI_UNUSED);
	}

	bool GetUndoCollection() const {
		sptr_t res = Call(SCI_GETUNDOCOLLECTION, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	int GetViewWS() const {
		sptr_t res = Call(SCI_GETVIEWWS, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetViewWS(int viewWS) const {
		Call(SCI_SETVIEWWS, viewWS, SCI_UNUSED);
	}

	int GetTabDrawMode() const {
		sptr_t res = Call(SCI_GETTABDRAWMODE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetTabDrawMode(int tabDrawMode) const {
		Call(SCI_SETTABDRAWMODE, tabDrawMode, SCI_UNUSED);
	}

	int PositionFromPoint(int x, int y) const {
		sptr_t res = Call(SCI_POSITIONFROMPOINT, x, y);
		return static_cast<int>(res);
	}

	int PositionFromPointClose(int x, int y) const {
		sptr_t res = Call(SCI_POSITIONFROMPOINTCLOSE, x, y);
		return static_cast<int>(res);
	}

	void GotoLine(int line) const {
		Call(SCI_GOTOLINE, line, SCI_UNUSED);
	}

	void GotoPos(int caret) const {
		Call(SCI_GOTOPOS, caret, SCI_UNUSED);
	}

	void SetAnchor(int anchor) const {
		Call(SCI_SETANCHOR, anchor, SCI_UNUSED);
	}

	int GetCurLine(int length, char* text) const {
		sptr_t res = Call(SCI_GETCURLINE, length, text);
		return static_cast<int>(res);
	}

	std::string GetCurLine() const {
		auto size = Call(SCI_GETCURLINE, SCI_UNUSED, NULL);
		std::string text(size + 1, '\0');
		Call(SCI_GETCURLINE, text.length(), &text[0]);
		trim(text);
		return text;
	}

	int GetEndStyled() const {
		sptr_t res = Call(SCI_GETENDSTYLED, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void ConvertEOLs(int eolMode) const {
		Call(SCI_CONVERTEOLS, eolMode, SCI_UNUSED);
	}

	int GetEOLMode() const {
		sptr_t res = Call(SCI_GETEOLMODE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetEOLMode(int eolMode) const {
		Call(SCI_SETEOLMODE, eolMode, SCI_UNUSED);
	}

	void StartStyling(int start, int unused) const {
		Call(SCI_STARTSTYLING, start, unused);
	}

	void SetStyling(int length, int style) const {
		Call(SCI_SETSTYLING, length, style);
	}

	bool GetBufferedDraw() const {
		sptr_t res = Call(SCI_GETBUFFEREDDRAW, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetBufferedDraw(bool buffered) const {
		Call(SCI_SETBUFFEREDDRAW, buffered, SCI_UNUSED);
	}

	void SetTabWidth(int tabWidth) const {
		Call(SCI_SETTABWIDTH, tabWidth, SCI_UNUSED);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  int GetTabWidth() const {
		sptr_t res = Call(SCI_GETTABWIDTH, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  void ClearTabStops(Sci_Position line) const {
		Call(SCI_CLEARTABSTOPS, line, SCI_UNUSED);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  void AddTabStop(Sci_Position line, int x) const {
		Call(SCI_ADDTABSTOP, line, x);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  int GetNextTabStop(Sci_Position line, int x) const {
		sptr_t res = Call(SCI_GETNEXTTABSTOP, line, x);
		return static_cast<int>(res);
	}

	void SetCodePage(int codePage) const {
		Call(SCI_SETCODEPAGE, codePage, SCI_UNUSED);
	}

	int GetIMEInteraction() const {
		sptr_t res = Call(SCI_GETIMEINTERACTION, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetIMEInteraction(int imeInteraction) const {
		Call(SCI_SETIMEINTERACTION, imeInteraction, SCI_UNUSED);
	}

	void MarkerDefine(int markerNumber, int markerSymbol) const {
		Call(SCI_MARKERDEFINE, markerNumber, markerSymbol);
	}

	void MarkerSetFore(int markerNumber, Colour fore) const {
		Call(SCI_MARKERSETFORE, markerNumber, fore);
	}

	void MarkerSetBack(int markerNumber, Colour back) const {
		Call(SCI_MARKERSETBACK, markerNumber, back);
	}

	void MarkerSetBackSelected(int markerNumber, Colour back) const {
		Call(SCI_MARKERSETBACKSELECTED, markerNumber, back);
	}

	void MarkerEnableHighlight(bool enabled) const {
		Call(SCI_MARKERENABLEHIGHLIGHT, enabled, SCI_UNUSED);
	}
  /* Used by ElasticTabstops only in Debug */
	int MarkerAdd(Sci_Position line, int markerNumber) const {
		sptr_t res = Call(SCI_MARKERADD, line, markerNumber);
		return static_cast<int>(res);
	}
  /* Used by ElasticTabstops only in Debug */
  void MarkerDelete(Sci_Position line, int markerNumber) const {
		Call(SCI_MARKERDELETE, line, markerNumber);
	}
  /* Used by ElasticTabstops only in Debug */
  void MarkerDeleteAll(int markerNumber) const {
		Call(SCI_MARKERDELETEALL, markerNumber, SCI_UNUSED);
	}

	int MarkerGet(int line) const {
		sptr_t res = Call(SCI_MARKERGET, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int MarkerNext(int lineStart, int markerMask) const {
		sptr_t res = Call(SCI_MARKERNEXT, lineStart, markerMask);
		return static_cast<int>(res);
	}

	int MarkerPrevious(int lineStart, int markerMask) const {
		sptr_t res = Call(SCI_MARKERPREVIOUS, lineStart, markerMask);
		return static_cast<int>(res);
	}

	void MarkerDefinePixmap(int markerNumber, const char* pixmap) const {
		Call(SCI_MARKERDEFINEPIXMAP, markerNumber, pixmap);
	}

	void MarkerDefinePixmap(int markerNumber, const std::string& pixmap) const {
		Call(SCI_MARKERDEFINEPIXMAP, markerNumber, pixmap.c_str());
	}

	void MarkerAddSet(int line, int markerSet) const {
		Call(SCI_MARKERADDSET, line, markerSet);
	}

	void MarkerSetAlpha(int markerNumber, int alpha) const {
		Call(SCI_MARKERSETALPHA, markerNumber, alpha);
	}

	void SetMarginTypeN(int margin, int marginType) const {
		Call(SCI_SETMARGINTYPEN, margin, marginType);
	}

	int GetMarginTypeN(int margin) const {
		sptr_t res = Call(SCI_GETMARGINTYPEN, margin, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetMarginWidthN(int margin, int pixelWidth) const {
		Call(SCI_SETMARGINWIDTHN, margin, pixelWidth);
	}

	int GetMarginWidthN(int margin) const {
		sptr_t res = Call(SCI_GETMARGINWIDTHN, margin, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetMarginMaskN(int margin, int mask) const {
		Call(SCI_SETMARGINMASKN, margin, mask);
	}

	int GetMarginMaskN(int margin) const {
		sptr_t res = Call(SCI_GETMARGINMASKN, margin, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetMarginSensitiveN(int margin, bool sensitive) const {
		Call(SCI_SETMARGINSENSITIVEN, margin, sensitive);
	}

	bool GetMarginSensitiveN(int margin) const {
		sptr_t res = Call(SCI_GETMARGINSENSITIVEN, margin, SCI_UNUSED);
		return res != 0;
	}

	void SetMarginCursorN(int margin, int cursor) const {
		Call(SCI_SETMARGINCURSORN, margin, cursor);
	}

	int GetMarginCursorN(int margin) const {
		sptr_t res = Call(SCI_GETMARGINCURSORN, margin, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetMarginBackN(int margin, Colour back) const {
		Call(SCI_SETMARGINBACKN, margin, back);
	}

	Colour GetMarginBackN(int margin) const {
		sptr_t res = Call(SCI_GETMARGINBACKN, margin, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	void SetMargins(int margins) const {
		Call(SCI_SETMARGINS, margins, SCI_UNUSED);
	}

	int GetMargins() const {
		sptr_t res = Call(SCI_GETMARGINS, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void StyleClearAll() const {
		Call(SCI_STYLECLEARALL, SCI_UNUSED, SCI_UNUSED);
	}

	void StyleSetFore(int style, Colour fore) const {
		Call(SCI_STYLESETFORE, style, fore);
	}

	void StyleSetBack(int style, Colour back) const {
		Call(SCI_STYLESETBACK, style, back);
	}

	void StyleSetBold(int style, bool bold) const {
		Call(SCI_STYLESETBOLD, style, bold);
	}

	void StyleSetItalic(int style, bool italic) const {
		Call(SCI_STYLESETITALIC, style, italic);
	}

	void StyleSetSize(int style, int sizePoints) const {
		Call(SCI_STYLESETSIZE, style, sizePoints);
	}

	void StyleSetFont(int style, const char* fontName) const {
		Call(SCI_STYLESETFONT, style, fontName);
	}

	void StyleSetFont(int style, const std::string& fontName) const {
		Call(SCI_STYLESETFONT, style, fontName.c_str());
	}

	void StyleSetEOLFilled(int style, bool eolFilled) const {
		Call(SCI_STYLESETEOLFILLED, style, eolFilled);
	}

	void StyleResetDefault() const {
		Call(SCI_STYLERESETDEFAULT, SCI_UNUSED, SCI_UNUSED);
	}

	void StyleSetUnderline(int style, bool underline) const {
		Call(SCI_STYLESETUNDERLINE, style, underline);
	}

	Colour StyleGetFore(int style) const {
		sptr_t res = Call(SCI_STYLEGETFORE, style, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	Colour StyleGetBack(int style) const {
		sptr_t res = Call(SCI_STYLEGETBACK, style, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	bool StyleGetBold(int style) const {
		sptr_t res = Call(SCI_STYLEGETBOLD, style, SCI_UNUSED);
		return res != 0;
	}

	bool StyleGetItalic(int style) const {
		sptr_t res = Call(SCI_STYLEGETITALIC, style, SCI_UNUSED);
		return res != 0;
	}

	int StyleGetSize(int style) const {
		sptr_t res = Call(SCI_STYLEGETSIZE, style, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int StyleGetFont(int style, char* fontName) const {
		sptr_t res = Call(SCI_STYLEGETFONT, style, fontName);
		return static_cast<int>(res);
	}

	std::string StyleGetFont(int style) const {
		auto size = Call(SCI_STYLEGETFONT, style, NULL);
		std::string fontName(size + 1, '\0');
		Call(SCI_STYLEGETFONT, style, &fontName[0]);
		trim(fontName);
		return fontName;
	}

	bool StyleGetEOLFilled(int style) const {
		sptr_t res = Call(SCI_STYLEGETEOLFILLED, style, SCI_UNUSED);
		return res != 0;
	}

	bool StyleGetUnderline(int style) const {
		sptr_t res = Call(SCI_STYLEGETUNDERLINE, style, SCI_UNUSED);
		return res != 0;
	}

	int StyleGetCase(int style) const {
		sptr_t res = Call(SCI_STYLEGETCASE, style, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int StyleGetCharacterSet(int style) const {
		sptr_t res = Call(SCI_STYLEGETCHARACTERSET, style, SCI_UNUSED);
		return static_cast<int>(res);
	}

	bool StyleGetVisible(int style) const {
		sptr_t res = Call(SCI_STYLEGETVISIBLE, style, SCI_UNUSED);
		return res != 0;
	}

	bool StyleGetChangeable(int style) const {
		sptr_t res = Call(SCI_STYLEGETCHANGEABLE, style, SCI_UNUSED);
		return res != 0;
	}

	bool StyleGetHotSpot(int style) const {
		sptr_t res = Call(SCI_STYLEGETHOTSPOT, style, SCI_UNUSED);
		return res != 0;
	}

	void StyleSetCase(int style, int caseVisible) const {
		Call(SCI_STYLESETCASE, style, caseVisible);
	}

	void StyleSetSizeFractional(int style, int sizeHundredthPoints) const {
		Call(SCI_STYLESETSIZEFRACTIONAL, style, sizeHundredthPoints);
	}

	int StyleGetSizeFractional(int style) const {
		sptr_t res = Call(SCI_STYLEGETSIZEFRACTIONAL, style, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void StyleSetWeight(int style, int weight) const {
		Call(SCI_STYLESETWEIGHT, style, weight);
	}

	int StyleGetWeight(int style) const {
		sptr_t res = Call(SCI_STYLEGETWEIGHT, style, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void StyleSetCharacterSet(int style, int characterSet) const {
		Call(SCI_STYLESETCHARACTERSET, style, characterSet);
	}

	void StyleSetHotSpot(int style, bool hotspot) const {
		Call(SCI_STYLESETHOTSPOT, style, hotspot);
	}

	void SetSelFore(bool useSetting, Colour fore) const {
		Call(SCI_SETSELFORE, useSetting, fore);
	}

	void SetSelBack(bool useSetting, Colour back) const {
		Call(SCI_SETSELBACK, useSetting, back);
	}

	int GetSelAlpha() const {
		sptr_t res = Call(SCI_GETSELALPHA, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetSelAlpha(int alpha) const {
		Call(SCI_SETSELALPHA, alpha, SCI_UNUSED);
	}

	bool GetSelEOLFilled() const {
		sptr_t res = Call(SCI_GETSELEOLFILLED, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetSelEOLFilled(bool filled) const {
		Call(SCI_SETSELEOLFILLED, filled, SCI_UNUSED);
	}

	void SetCaretFore(Colour fore) const {
		Call(SCI_SETCARETFORE, fore, SCI_UNUSED);
	}

	void AssignCmdKey(KeyModifier keyDefinition, int sciCommand) const {
		Call(SCI_ASSIGNCMDKEY, keyDefinition, sciCommand);
	}

	void ClearCmdKey(KeyModifier keyDefinition) const {
		Call(SCI_CLEARCMDKEY, keyDefinition, SCI_UNUSED);
	}

	void ClearAllCmdKeys() const {
		Call(SCI_CLEARALLCMDKEYS, SCI_UNUSED, SCI_UNUSED);
	}

	void SetStylingEx(int length, const char* styles) const {
		Call(SCI_SETSTYLINGEX, length, styles);
	}

	void SetStylingEx(const std::string& styles) const {
		Call(SCI_SETSTYLINGEX, styles.length(), styles.c_str());
	}

	void StyleSetVisible(int style, bool visible) const {
		Call(SCI_STYLESETVISIBLE, style, visible);
	}

	int GetCaretPeriod() const {
		sptr_t res = Call(SCI_GETCARETPERIOD, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetCaretPeriod(int periodMilliseconds) const {
		Call(SCI_SETCARETPERIOD, periodMilliseconds, SCI_UNUSED);
	}

	void SetWordChars(const char* characters) const {
		Call(SCI_SETWORDCHARS, SCI_UNUSED, characters);
	}

	void SetWordChars(const std::string& characters) const {
		Call(SCI_SETWORDCHARS, SCI_UNUSED, characters.c_str());
	}

	int GetWordChars(char* characters) const {
		sptr_t res = Call(SCI_GETWORDCHARS, SCI_UNUSED, characters);
		return static_cast<int>(res);
	}

	std::string GetWordChars() const {
		auto size = Call(SCI_GETWORDCHARS, SCI_UNUSED, NULL);
		std::string characters(size + 1, '\0');
		Call(SCI_GETWORDCHARS, SCI_UNUSED, &characters[0]);
		trim(characters);
		return characters;
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  void BeginUndoAction() const {
		Call(SCI_BEGINUNDOACTION, SCI_UNUSED, SCI_UNUSED);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  void EndUndoAction() const {
		Call(SCI_ENDUNDOACTION, SCI_UNUSED, SCI_UNUSED);
	}

	void IndicSetStyle(int indicator, int indicatorStyle) const {
		Call(SCI_INDICSETSTYLE, indicator, indicatorStyle);
	}

	int IndicGetStyle(int indicator) const {
		sptr_t res = Call(SCI_INDICGETSTYLE, indicator, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void IndicSetFore(int indicator, Colour fore) const {
		Call(SCI_INDICSETFORE, indicator, fore);
	}

	Colour IndicGetFore(int indicator) const {
		sptr_t res = Call(SCI_INDICGETFORE, indicator, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	void IndicSetUnder(int indicator, bool under) const {
		Call(SCI_INDICSETUNDER, indicator, under);
	}

	bool IndicGetUnder(int indicator) const {
		sptr_t res = Call(SCI_INDICGETUNDER, indicator, SCI_UNUSED);
		return res != 0;
	}

	void IndicSetHoverStyle(int indicator, int indicatorStyle) const {
		Call(SCI_INDICSETHOVERSTYLE, indicator, indicatorStyle);
	}

	int IndicGetHoverStyle(int indicator) const {
		sptr_t res = Call(SCI_INDICGETHOVERSTYLE, indicator, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void IndicSetHoverFore(int indicator, Colour fore) const {
		Call(SCI_INDICSETHOVERFORE, indicator, fore);
	}

	Colour IndicGetHoverFore(int indicator) const {
		sptr_t res = Call(SCI_INDICGETHOVERFORE, indicator, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	void IndicSetFlags(int indicator, int flags) const {
		Call(SCI_INDICSETFLAGS, indicator, flags);
	}

	int IndicGetFlags(int indicator) const {
		sptr_t res = Call(SCI_INDICGETFLAGS, indicator, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetWhitespaceFore(bool useSetting, Colour fore) const {
		Call(SCI_SETWHITESPACEFORE, useSetting, fore);
	}

	void SetWhitespaceBack(bool useSetting, Colour back) const {
		Call(SCI_SETWHITESPACEBACK, useSetting, back);
	}

	void SetWhitespaceSize(int size) const {
		Call(SCI_SETWHITESPACESIZE, size, SCI_UNUSED);
	}

	int GetWhitespaceSize() const {
		sptr_t res = Call(SCI_GETWHITESPACESIZE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetLineState(int line, int state) const {
		Call(SCI_SETLINESTATE, line, state);
	}

	int GetLineState(int line) const {
		sptr_t res = Call(SCI_GETLINESTATE, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetMaxLineState() const {
		sptr_t res = Call(SCI_GETMAXLINESTATE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	bool GetCaretLineVisible() const {
		sptr_t res = Call(SCI_GETCARETLINEVISIBLE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetCaretLineVisible(bool show) const {
		Call(SCI_SETCARETLINEVISIBLE, show, SCI_UNUSED);
	}

	Colour GetCaretLineBack() const {
		sptr_t res = Call(SCI_GETCARETLINEBACK, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	void SetCaretLineBack(Colour back) const {
		Call(SCI_SETCARETLINEBACK, back, SCI_UNUSED);
	}

	int GetCaretLineFrame() const {
		sptr_t res = Call(SCI_GETCARETLINEFRAME, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetCaretLineFrame(int width) const {
		Call(SCI_SETCARETLINEFRAME, width, SCI_UNUSED);
	}

	void StyleSetChangeable(int style, bool changeable) const {
		Call(SCI_STYLESETCHANGEABLE, style, changeable);
	}

	void AutoCShow(int lengthEntered, const char* itemList) const {
		Call(SCI_AUTOCSHOW, lengthEntered, itemList);
	}

	void AutoCShow(int lengthEntered, const std::string& itemList) const {
		Call(SCI_AUTOCSHOW, lengthEntered, itemList.c_str());
	}

	void AutoCCancel() const {
		Call(SCI_AUTOCCANCEL, SCI_UNUSED, SCI_UNUSED);
	}

	bool AutoCActive() const {
		sptr_t res = Call(SCI_AUTOCACTIVE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	int AutoCPosStart() const {
		sptr_t res = Call(SCI_AUTOCPOSSTART, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AutoCComplete() const {
		Call(SCI_AUTOCCOMPLETE, SCI_UNUSED, SCI_UNUSED);
	}

	void AutoCStops(const char* characterSet) const {
		Call(SCI_AUTOCSTOPS, SCI_UNUSED, characterSet);
	}

	void AutoCStops(const std::string& characterSet) const {
		Call(SCI_AUTOCSTOPS, SCI_UNUSED, characterSet.c_str());
	}

	void AutoCSetSeparator(int separatorCharacter) const {
		Call(SCI_AUTOCSETSEPARATOR, separatorCharacter, SCI_UNUSED);
	}

	int AutoCGetSeparator() const {
		sptr_t res = Call(SCI_AUTOCGETSEPARATOR, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AutoCSelect(const char* select) const {
		Call(SCI_AUTOCSELECT, SCI_UNUSED, select);
	}

	void AutoCSelect(const std::string& select) const {
		Call(SCI_AUTOCSELECT, SCI_UNUSED, select.c_str());
	}

	void AutoCSetCancelAtStart(bool cancel) const {
		Call(SCI_AUTOCSETCANCELATSTART, cancel, SCI_UNUSED);
	}

	bool AutoCGetCancelAtStart() const {
		sptr_t res = Call(SCI_AUTOCGETCANCELATSTART, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void AutoCSetFillUps(const char* characterSet) const {
		Call(SCI_AUTOCSETFILLUPS, SCI_UNUSED, characterSet);
	}

	void AutoCSetFillUps(const std::string& characterSet) const {
		Call(SCI_AUTOCSETFILLUPS, SCI_UNUSED, characterSet.c_str());
	}

	void AutoCSetChooseSingle(bool chooseSingle) const {
		Call(SCI_AUTOCSETCHOOSESINGLE, chooseSingle, SCI_UNUSED);
	}

	bool AutoCGetChooseSingle() const {
		sptr_t res = Call(SCI_AUTOCGETCHOOSESINGLE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void AutoCSetIgnoreCase(bool ignoreCase) const {
		Call(SCI_AUTOCSETIGNORECASE, ignoreCase, SCI_UNUSED);
	}

	bool AutoCGetIgnoreCase() const {
		sptr_t res = Call(SCI_AUTOCGETIGNORECASE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void UserListShow(int listType, const char* itemList) const {
		Call(SCI_USERLISTSHOW, listType, itemList);
	}

	void UserListShow(int listType, const std::string& itemList) const {
		Call(SCI_USERLISTSHOW, listType, itemList.c_str());
	}

	void AutoCSetAutoHide(bool autoHide) const {
		Call(SCI_AUTOCSETAUTOHIDE, autoHide, SCI_UNUSED);
	}

	bool AutoCGetAutoHide() const {
		sptr_t res = Call(SCI_AUTOCGETAUTOHIDE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void AutoCSetDropRestOfWord(bool dropRestOfWord) const {
		Call(SCI_AUTOCSETDROPRESTOFWORD, dropRestOfWord, SCI_UNUSED);
	}

	bool AutoCGetDropRestOfWord() const {
		sptr_t res = Call(SCI_AUTOCGETDROPRESTOFWORD, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void RegisterImage(int type, const char* xpmData) const {
		Call(SCI_REGISTERIMAGE, type, xpmData);
	}

	void RegisterImage(int type, const std::string& xpmData) const {
		Call(SCI_REGISTERIMAGE, type, xpmData.c_str());
	}

	void ClearRegisteredImages() const {
		Call(SCI_CLEARREGISTEREDIMAGES, SCI_UNUSED, SCI_UNUSED);
	}

	int AutoCGetTypeSeparator() const {
		sptr_t res = Call(SCI_AUTOCGETTYPESEPARATOR, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AutoCSetTypeSeparator(int separatorCharacter) const {
		Call(SCI_AUTOCSETTYPESEPARATOR, separatorCharacter, SCI_UNUSED);
	}

	void AutoCSetMaxWidth(int characterCount) const {
		Call(SCI_AUTOCSETMAXWIDTH, characterCount, SCI_UNUSED);
	}

	int AutoCGetMaxWidth() const {
		sptr_t res = Call(SCI_AUTOCGETMAXWIDTH, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AutoCSetMaxHeight(int rowCount) const {
		Call(SCI_AUTOCSETMAXHEIGHT, rowCount, SCI_UNUSED);
	}

	int AutoCGetMaxHeight() const {
		sptr_t res = Call(SCI_AUTOCGETMAXHEIGHT, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetIndent(int indentSize) const {
		Call(SCI_SETINDENT, indentSize, SCI_UNUSED);
	}

	int GetIndent() const {
		sptr_t res = Call(SCI_GETINDENT, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetUseTabs(bool useTabs) const {
		Call(SCI_SETUSETABS, useTabs, SCI_UNUSED);
	}

	bool GetUseTabs() const {
		sptr_t res = Call(SCI_GETUSETABS, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetLineIndentation(int line, int indentation) const {
		Call(SCI_SETLINEINDENTATION, line, indentation);
	}

	int GetLineIndentation(int line) const {
		sptr_t res = Call(SCI_GETLINEINDENTATION, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetLineIndentPosition(int line) const {
		sptr_t res = Call(SCI_GETLINEINDENTPOSITION, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetColumn(int pos) const {
		sptr_t res = Call(SCI_GETCOLUMN, pos, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int CountCharacters(int start, int end) const {
		sptr_t res = Call(SCI_COUNTCHARACTERS, start, end);
		return static_cast<int>(res);
	}

	int CountCodeUnits(int start, int end) const {
		sptr_t res = Call(SCI_COUNTCODEUNITS, start, end);
		return static_cast<int>(res);
	}

	void SetHScrollBar(bool visible) const {
		Call(SCI_SETHSCROLLBAR, visible, SCI_UNUSED);
	}

	bool GetHScrollBar() const {
		sptr_t res = Call(SCI_GETHSCROLLBAR, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetIndentationGuides(int indentView) const {
		Call(SCI_SETINDENTATIONGUIDES, indentView, SCI_UNUSED);
	}

	int GetIndentationGuides() const {
		sptr_t res = Call(SCI_GETINDENTATIONGUIDES, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetHighlightGuide(int column) const {
		Call(SCI_SETHIGHLIGHTGUIDE, column, SCI_UNUSED);
	}

	int GetHighlightGuide() const {
		sptr_t res = Call(SCI_GETHIGHLIGHTGUIDE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position GetLineEndPosition(Sci_Position line) const {
		sptr_t res = Call(SCI_GETLINEENDPOSITION, line, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}

	int GetCodePage() const {
		sptr_t res = Call(SCI_GETCODEPAGE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	Colour GetCaretFore() const {
		sptr_t res = Call(SCI_GETCARETFORE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	bool GetReadOnly() const {
		sptr_t res = Call(SCI_GETREADONLY, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetCurrentPos(int caret) const {
		Call(SCI_SETCURRENTPOS, caret, SCI_UNUSED);
	}

	void SetSelectionStart(int anchor) const {
		Call(SCI_SETSELECTIONSTART, anchor, SCI_UNUSED);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position GetSelectionStart() const {
		sptr_t res = Call(SCI_GETSELECTIONSTART, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}

	void SetSelectionEnd(int caret) const {
		Call(SCI_SETSELECTIONEND, caret, SCI_UNUSED);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position GetSelectionEnd() const {
		sptr_t res = Call(SCI_GETSELECTIONEND, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}

	void SetEmptySelection(int caret) const {
		Call(SCI_SETEMPTYSELECTION, caret, SCI_UNUSED);
	}

	void SetPrintMagnification(int magnification) const {
		Call(SCI_SETPRINTMAGNIFICATION, magnification, SCI_UNUSED);
	}

	int GetPrintMagnification() const {
		sptr_t res = Call(SCI_GETPRINTMAGNIFICATION, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetPrintColourMode(int mode) const {
		Call(SCI_SETPRINTCOLOURMODE, mode, SCI_UNUSED);
	}

	int GetPrintColourMode() const {
		sptr_t res = Call(SCI_GETPRINTCOLOURMODE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position FindText(int searchFlags, Sci_TextToFindFull* ft) const {
		sptr_t res = Call(SCI_FINDTEXTFULL, searchFlags, ft);
		return static_cast<Sci_Position>(res);
	}

	int FormatRange(bool draw, Sci_RangeToFormatFull* fr) const {
		sptr_t res = Call(SCI_FORMATRANGEFULL, draw, fr);
		return static_cast<int>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position GetFirstVisibleLine() const {
		sptr_t res = Call(SCI_GETFIRSTVISIBLELINE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}

	int GetLine(int line, char* text) const {
		sptr_t res = Call(SCI_GETLINE, line, text);
		return static_cast<int>(res);
	}

	std::string GetLine(int line) const {
		auto size = Call(SCI_GETLINE, line, NULL);
		std::string text(size + 1, '\0');
		Call(SCI_GETLINE, line, &text[0]);
		trim(text);
		return text;
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position GetLineCount() const {
		sptr_t res = Call(SCI_GETLINECOUNT, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}

	void SetMarginLeft(int pixelWidth) const {
		Call(SCI_SETMARGINLEFT, SCI_UNUSED, pixelWidth);
	}

	int GetMarginLeft() const {
		sptr_t res = Call(SCI_GETMARGINLEFT, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetMarginRight(int pixelWidth) const {
		Call(SCI_SETMARGINRIGHT, SCI_UNUSED, pixelWidth);
	}

	int GetMarginRight() const {
		sptr_t res = Call(SCI_GETMARGINRIGHT, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	bool GetModify() const {
		sptr_t res = Call(SCI_GETMODIFY, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetSel(int anchor, int caret) const {
		Call(SCI_SETSEL, anchor, caret);
	}

	int GetSelText(char* text) const {
		sptr_t res = Call(SCI_GETSELTEXT, SCI_UNUSED, text);
		return static_cast<int>(res);
	}

	std::string GetSelText() const {
		auto size = Call(SCI_GETSELTEXT, SCI_UNUSED, NULL);
		std::string text(size + 1, '\0');
		Call(SCI_GETSELTEXT, SCI_UNUSED, &text[0]);
		trim(text);
		return text;
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  int GetTextRange(Sci_TextRangeFull* tr) const {
		sptr_t res = Call(SCI_GETTEXTRANGEFULL, SCI_UNUSED, tr);
		return static_cast<int>(res);
	}

	void HideSelection(bool hide) const {
		Call(SCI_HIDESELECTION, hide, SCI_UNUSED);
	}

	int PointXFromPosition(int pos) const {
		sptr_t res = Call(SCI_POINTXFROMPOSITION, SCI_UNUSED, pos);
		return static_cast<int>(res);
	}

	int PointYFromPosition(int pos) const {
		sptr_t res = Call(SCI_POINTYFROMPOSITION, SCI_UNUSED, pos);
		return static_cast<int>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position LineFromPosition(Sci_Position pos) const {
		sptr_t res = Call(SCI_LINEFROMPOSITION, pos, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position PositionFromLine(Sci_Position line) const {
		sptr_t res = Call(SCI_POSITIONFROMLINE, line, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}

	void LineScroll(int columns, int lines) const {
		Call(SCI_LINESCROLL, columns, lines);
	}

	void ScrollCaret() const {
		Call(SCI_SCROLLCARET, SCI_UNUSED, SCI_UNUSED);
	}

	void ScrollRange(int secondary, int primary) const {
		Call(SCI_SCROLLRANGE, secondary, primary);
	}

	void ReplaceSel(const char* text) const {
		Call(SCI_REPLACESEL, SCI_UNUSED, text);
	}

	void ReplaceSel(const std::string& text) const {
		Call(SCI_REPLACESEL, SCI_UNUSED, text.c_str());
	}

	void SetReadOnly(bool readOnly) const {
		Call(SCI_SETREADONLY, readOnly, SCI_UNUSED);
	}

	void Null() const {
		Call(SCI_NULL, SCI_UNUSED, SCI_UNUSED);
	}

	bool CanPaste() const {
		sptr_t res = Call(SCI_CANPASTE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	bool CanUndo() const {
		sptr_t res = Call(SCI_CANUNDO, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void EmptyUndoBuffer() const {
		Call(SCI_EMPTYUNDOBUFFER, SCI_UNUSED, SCI_UNUSED);
	}

	void Undo() const {
		Call(SCI_UNDO, SCI_UNUSED, SCI_UNUSED);
	}

	void Cut() const {
		Call(SCI_CUT, SCI_UNUSED, SCI_UNUSED);
	}

	void Copy() const {
		Call(SCI_COPY, SCI_UNUSED, SCI_UNUSED);
	}

	void Paste() const {
		Call(SCI_PASTE, SCI_UNUSED, SCI_UNUSED);
	}

	void Clear() const {
		Call(SCI_CLEAR, SCI_UNUSED, SCI_UNUSED);
	}

	void SetText(const char* text) const {
		Call(SCI_SETTEXT, SCI_UNUSED, text);
	}

	void SetText(const std::string& text) const {
		Call(SCI_SETTEXT, SCI_UNUSED, text.c_str());
	}

	int GetText(int length, char* text) const {
		sptr_t res = Call(SCI_GETTEXT, length, text);
		return static_cast<int>(res);
	}

	std::string GetText() const {
		auto size = Call(SCI_GETTEXT, SCI_UNUSED, NULL);
		std::string text(size + 1, '\0');
		Call(SCI_GETTEXT, text.length(), &text[0]);
		trim(text);
		return text;
	}

	int GetTextLength() const {
		sptr_t res = Call(SCI_GETTEXTLENGTH, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	sptr_t GetDirectFunction() const {
		return Call(SCI_GETDIRECTFUNCTION, SCI_UNUSED, SCI_UNUSED);
	}

	sptr_t GetDirectPointer() const {
		return Call(SCI_GETDIRECTPOINTER, SCI_UNUSED, SCI_UNUSED);
	}

	void SetOvertype(bool overType) const {
		Call(SCI_SETOVERTYPE, overType, SCI_UNUSED);
	}

	bool GetOvertype() const {
		sptr_t res = Call(SCI_GETOVERTYPE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetCaretWidth(int pixelWidth) const {
		Call(SCI_SETCARETWIDTH, pixelWidth, SCI_UNUSED);
	}

	int GetCaretWidth() const {
		sptr_t res = Call(SCI_GETCARETWIDTH, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  void SetTargetStart(Sci_Position start) const {
		Call(SCI_SETTARGETSTART, start, SCI_UNUSED);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position GetTargetStart() const {
		sptr_t res = Call(SCI_GETTARGETSTART, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  void SetTargetEnd(Sci_Position end) const {
		Call(SCI_SETTARGETEND, end, SCI_UNUSED);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position GetTargetEnd() const {
		sptr_t res = Call(SCI_GETTARGETEND, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  void SetTargetRange(Sci_Position start, Sci_Position end) const {
		Call(SCI_SETTARGETRANGE, start, end);
	}

	int GetTargetText(char* text) const {
		sptr_t res = Call(SCI_GETTARGETTEXT, SCI_UNUSED, text);
		return static_cast<int>(res);
	}

	std::string GetTargetText() const {
		auto size = Call(SCI_GETTARGETTEXT, SCI_UNUSED, NULL);
		std::string text(size + 1, '\0');
		Call(SCI_GETTARGETTEXT, SCI_UNUSED, &text[0]);
		trim(text);
		return text;
	}

	void TargetFromSelection() const {
		Call(SCI_TARGETFROMSELECTION, SCI_UNUSED, SCI_UNUSED);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  void TargetWholeDocument() const {
		Call(SCI_TARGETWHOLEDOCUMENT, SCI_UNUSED, SCI_UNUSED);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position ReplaceTarget(Sci_Position length, const char* text) const {
		sptr_t res = Call(SCI_REPLACETARGET, length, text);
		return static_cast<Sci_Position>(res);
	}

  Sci_Position ReplaceTarget(const std::string& text) const {
		sptr_t res = Call(SCI_REPLACETARGET, text.length(), text.c_str());
		return static_cast<Sci_Position>(res);
	}

  Sci_Position ReplaceTargetRE(int length, const char* text) const {
		sptr_t res = Call(SCI_REPLACETARGETRE, length, text);
		return static_cast<Sci_Position>(res);
	}

  Sci_Position ReplaceTargetRE(const std::string& text) const {
		sptr_t res = Call(SCI_REPLACETARGETRE, text.length(), text.c_str());
		return static_cast<Sci_Position>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position SearchInTarget(Sci_Position length, const char* text) const {
		sptr_t res = Call(SCI_SEARCHINTARGET, length, text);
		return static_cast<Sci_Position>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position SearchInTarget(const std::string& text) const {
		sptr_t res = Call(SCI_SEARCHINTARGET, text.length(), text.c_str());
		return static_cast<Sci_Position>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  void SetSearchFlags(int searchFlags) const {
		Call(SCI_SETSEARCHFLAGS, searchFlags, SCI_UNUSED);
	}

	int GetSearchFlags() const {
		sptr_t res = Call(SCI_GETSEARCHFLAGS, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void CallTipShow(int pos, const char* definition) const {
		Call(SCI_CALLTIPSHOW, pos, definition);
	}

	void CallTipShow(int pos, const std::string& definition) const {
		Call(SCI_CALLTIPSHOW, pos, definition.c_str());
	}

	void CallTipCancel() const {
		Call(SCI_CALLTIPCANCEL, SCI_UNUSED, SCI_UNUSED);
	}

	bool CallTipActive() const {
		sptr_t res = Call(SCI_CALLTIPACTIVE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	int CallTipPosStart() const {
		sptr_t res = Call(SCI_CALLTIPPOSSTART, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void CallTipSetPosStart(int posStart) const {
		Call(SCI_CALLTIPSETPOSSTART, posStart, SCI_UNUSED);
	}

	void CallTipSetHlt(int highlightStart, int highlightEnd) const {
		Call(SCI_CALLTIPSETHLT, highlightStart, highlightEnd);
	}

	void CallTipSetBack(Colour back) const {
		Call(SCI_CALLTIPSETBACK, back, SCI_UNUSED);
	}

	void CallTipSetFore(Colour fore) const {
		Call(SCI_CALLTIPSETFORE, fore, SCI_UNUSED);
	}

	void CallTipSetForeHlt(Colour fore) const {
		Call(SCI_CALLTIPSETFOREHLT, fore, SCI_UNUSED);
	}

	void CallTipUseStyle(int tabSize) const {
		Call(SCI_CALLTIPUSESTYLE, tabSize, SCI_UNUSED);
	}

	void CallTipSetPosition(bool above) const {
		Call(SCI_CALLTIPSETPOSITION, above, SCI_UNUSED);
	}

	int VisibleFromDocLine(int docLine) const {
		sptr_t res = Call(SCI_VISIBLEFROMDOCLINE, docLine, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int DocLineFromVisible(int displayLine) const {
		sptr_t res = Call(SCI_DOCLINEFROMVISIBLE, displayLine, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int WrapCount(int docLine) const {
		sptr_t res = Call(SCI_WRAPCOUNT, docLine, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetFoldLevel(int line, int level) const {
		Call(SCI_SETFOLDLEVEL, line, level);
	}

	int GetFoldLevel(int line) const {
		sptr_t res = Call(SCI_GETFOLDLEVEL, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetLastChild(int line, int level) const {
		sptr_t res = Call(SCI_GETLASTCHILD, line, level);
		return static_cast<int>(res);
	}

	int GetFoldParent(int line) const {
		sptr_t res = Call(SCI_GETFOLDPARENT, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void ShowLines(int lineStart, int lineEnd) const {
		Call(SCI_SHOWLINES, lineStart, lineEnd);
	}

	void HideLines(int lineStart, int lineEnd) const {
		Call(SCI_HIDELINES, lineStart, lineEnd);
	}

	bool GetLineVisible(int line) const {
		sptr_t res = Call(SCI_GETLINEVISIBLE, line, SCI_UNUSED);
		return res != 0;
	}

	bool GetAllLinesVisible() const {
		sptr_t res = Call(SCI_GETALLLINESVISIBLE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetFoldExpanded(int line, bool expanded) const {
		Call(SCI_SETFOLDEXPANDED, line, expanded);
	}

	bool GetFoldExpanded(int line) const {
		sptr_t res = Call(SCI_GETFOLDEXPANDED, line, SCI_UNUSED);
		return res != 0;
	}

	void ToggleFold(int line) const {
		Call(SCI_TOGGLEFOLD, line, SCI_UNUSED);
	}

	void ToggleFoldShowText(int line, const char* text) const {
		Call(SCI_TOGGLEFOLDSHOWTEXT, line, text);
	}

	void ToggleFoldShowText(int line, const std::string& text) const {
		Call(SCI_TOGGLEFOLDSHOWTEXT, line, text.c_str());
	}

	void FoldDisplayTextSetStyle(int style) const {
		Call(SCI_FOLDDISPLAYTEXTSETSTYLE, style, SCI_UNUSED);
	}

	void FoldLine(int line, int action) const {
		Call(SCI_FOLDLINE, line, action);
	}

	void FoldChildren(int line, int action) const {
		Call(SCI_FOLDCHILDREN, line, action);
	}

	void ExpandChildren(int line, int level) const {
		Call(SCI_EXPANDCHILDREN, line, level);
	}

	void FoldAll(int action) const {
		Call(SCI_FOLDALL, action, SCI_UNUSED);
	}

	void EnsureVisible(int line) const {
		Call(SCI_ENSUREVISIBLE, line, SCI_UNUSED);
	}

	void SetAutomaticFold(int automaticFold) const {
		Call(SCI_SETAUTOMATICFOLD, automaticFold, SCI_UNUSED);
	}

	int GetAutomaticFold() const {
		sptr_t res = Call(SCI_GETAUTOMATICFOLD, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetFoldFlags(int flags) const {
		Call(SCI_SETFOLDFLAGS, flags, SCI_UNUSED);
	}

	void EnsureVisibleEnforcePolicy(int line) const {
		Call(SCI_ENSUREVISIBLEENFORCEPOLICY, line, SCI_UNUSED);
	}

	void SetTabIndents(bool tabIndents) const {
		Call(SCI_SETTABINDENTS, tabIndents, SCI_UNUSED);
	}

	bool GetTabIndents() const {
		sptr_t res = Call(SCI_GETTABINDENTS, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetBackSpaceUnIndents(bool bsUnIndents) const {
		Call(SCI_SETBACKSPACEUNINDENTS, bsUnIndents, SCI_UNUSED);
	}

	bool GetBackSpaceUnIndents() const {
		sptr_t res = Call(SCI_GETBACKSPACEUNINDENTS, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetMouseDwellTime(int periodMilliseconds) const {
		Call(SCI_SETMOUSEDWELLTIME, periodMilliseconds, SCI_UNUSED);
	}

	int GetMouseDwellTime() const {
		sptr_t res = Call(SCI_GETMOUSEDWELLTIME, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int WordStartPosition(int pos, bool onlyWordCharacters) const {
		sptr_t res = Call(SCI_WORDSTARTPOSITION, pos, onlyWordCharacters);
		return static_cast<int>(res);
	}

	int WordEndPosition(int pos, bool onlyWordCharacters) const {
		sptr_t res = Call(SCI_WORDENDPOSITION, pos, onlyWordCharacters);
		return static_cast<int>(res);
	}

	bool IsRangeWord(int start, int end) const {
		sptr_t res = Call(SCI_ISRANGEWORD, start, end);
		return res != 0;
	}

	void SetIdleStyling(int idleStyling) const {
		Call(SCI_SETIDLESTYLING, idleStyling, SCI_UNUSED);
	}

	int GetIdleStyling() const {
		sptr_t res = Call(SCI_GETIDLESTYLING, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetWrapMode(int wrapMode) const {
		Call(SCI_SETWRAPMODE, wrapMode, SCI_UNUSED);
	}

	int GetWrapMode() const {
		sptr_t res = Call(SCI_GETWRAPMODE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetWrapVisualFlags(int wrapVisualFlags) const {
		Call(SCI_SETWRAPVISUALFLAGS, wrapVisualFlags, SCI_UNUSED);
	}

	int GetWrapVisualFlags() const {
		sptr_t res = Call(SCI_GETWRAPVISUALFLAGS, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetWrapVisualFlagsLocation(int wrapVisualFlagsLocation) const {
		Call(SCI_SETWRAPVISUALFLAGSLOCATION, wrapVisualFlagsLocation, SCI_UNUSED);
	}

	int GetWrapVisualFlagsLocation() const {
		sptr_t res = Call(SCI_GETWRAPVISUALFLAGSLOCATION, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetWrapStartIndent(int indent) const {
		Call(SCI_SETWRAPSTARTINDENT, indent, SCI_UNUSED);
	}

	int GetWrapStartIndent() const {
		sptr_t res = Call(SCI_GETWRAPSTARTINDENT, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetWrapIndentMode(int wrapIndentMode) const {
		Call(SCI_SETWRAPINDENTMODE, wrapIndentMode, SCI_UNUSED);
	}

	int GetWrapIndentMode() const {
		sptr_t res = Call(SCI_GETWRAPINDENTMODE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetLayoutCache(int cacheMode) const {
		Call(SCI_SETLAYOUTCACHE, cacheMode, SCI_UNUSED);
	}

	int GetLayoutCache() const {
		sptr_t res = Call(SCI_GETLAYOUTCACHE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetScrollWidth(int pixelWidth) const {
		Call(SCI_SETSCROLLWIDTH, pixelWidth, SCI_UNUSED);
	}

	int GetScrollWidth() const {
		sptr_t res = Call(SCI_GETSCROLLWIDTH, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetScrollWidthTracking(bool tracking) const {
		Call(SCI_SETSCROLLWIDTHTRACKING, tracking, SCI_UNUSED);
	}

	bool GetScrollWidthTracking() const {
		sptr_t res = Call(SCI_GETSCROLLWIDTHTRACKING, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  int TextWidth(int style, const char* text) const {
		sptr_t res = Call(SCI_TEXTWIDTH, style, text);
		return static_cast<int>(res);
	}

	int TextWidth(int style, const std::string& text) const {
		sptr_t res = Call(SCI_TEXTWIDTH, style, text.c_str());
		return static_cast<int>(res);
	}

	void SetEndAtLastLine(bool endAtLastLine) const {
		Call(SCI_SETENDATLASTLINE, endAtLastLine, SCI_UNUSED);
	}

	bool GetEndAtLastLine() const {
		sptr_t res = Call(SCI_GETENDATLASTLINE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	int TextHeight(int line) const {
		sptr_t res = Call(SCI_TEXTHEIGHT, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetVScrollBar(bool visible) const {
		Call(SCI_SETVSCROLLBAR, visible, SCI_UNUSED);
	}

	bool GetVScrollBar() const {
		sptr_t res = Call(SCI_GETVSCROLLBAR, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void AppendText(int length, const char* text) const {
		Call(SCI_APPENDTEXT, length, text);
	}

	void AppendText(const std::string& text) const {
		Call(SCI_APPENDTEXT, text.length(), text.c_str());
	}

	int GetPhasesDraw() const {
		sptr_t res = Call(SCI_GETPHASESDRAW, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetPhasesDraw(int phases) const {
		Call(SCI_SETPHASESDRAW, phases, SCI_UNUSED);
	}

	void SetFontQuality(int fontQuality) const {
		Call(SCI_SETFONTQUALITY, fontQuality, SCI_UNUSED);
	}

	int GetFontQuality() const {
		sptr_t res = Call(SCI_GETFONTQUALITY, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetFirstVisibleLine(int displayLine) const {
		Call(SCI_SETFIRSTVISIBLELINE, displayLine, SCI_UNUSED);
	}

	void SetMultiPaste(int multiPaste) const {
		Call(SCI_SETMULTIPASTE, multiPaste, SCI_UNUSED);
	}

	int GetMultiPaste() const {
		sptr_t res = Call(SCI_GETMULTIPASTE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetTag(int tagNumber, char* tagValue) const {
		sptr_t res = Call(SCI_GETTAG, tagNumber, tagValue);
		return static_cast<int>(res);
	}

	std::string GetTag(int tagNumber) const {
		auto size = Call(SCI_GETTAG, tagNumber, NULL);
		std::string tagValue(size + 1, '\0');
		Call(SCI_GETTAG, tagNumber, &tagValue[0]);
		trim(tagValue);
		return tagValue;
	}

	void LinesJoin() const {
		Call(SCI_LINESJOIN, SCI_UNUSED, SCI_UNUSED);
	}

	void LinesSplit(int pixelWidth) const {
		Call(SCI_LINESSPLIT, pixelWidth, SCI_UNUSED);
	}

	void SetFoldMarginColour(bool useSetting, Colour back) const {
		Call(SCI_SETFOLDMARGINCOLOUR, useSetting, back);
	}

	void SetFoldMarginHiColour(bool useSetting, Colour fore) const {
		Call(SCI_SETFOLDMARGINHICOLOUR, useSetting, fore);
	}

	void SetAccessibility(int accessibility) const {
		Call(SCI_SETACCESSIBILITY, accessibility, SCI_UNUSED);
	}

	int GetAccessibility() const {
		sptr_t res = Call(SCI_GETACCESSIBILITY, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void LineDown() const {
		Call(SCI_LINEDOWN, SCI_UNUSED, SCI_UNUSED);
	}

	void LineDownExtend() const {
		Call(SCI_LINEDOWNEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void LineUp() const {
		Call(SCI_LINEUP, SCI_UNUSED, SCI_UNUSED);
	}

	void LineUpExtend() const {
		Call(SCI_LINEUPEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void CharLeft() const {
		Call(SCI_CHARLEFT, SCI_UNUSED, SCI_UNUSED);
	}

	void CharLeftExtend() const {
		Call(SCI_CHARLEFTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void CharRight() const {
		Call(SCI_CHARRIGHT, SCI_UNUSED, SCI_UNUSED);
	}

	void CharRightExtend() const {
		Call(SCI_CHARRIGHTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void WordLeft() const {
		Call(SCI_WORDLEFT, SCI_UNUSED, SCI_UNUSED);
	}

	void WordLeftExtend() const {
		Call(SCI_WORDLEFTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void WordRight() const {
		Call(SCI_WORDRIGHT, SCI_UNUSED, SCI_UNUSED);
	}

	void WordRightExtend() const {
		Call(SCI_WORDRIGHTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void Home() const {
		Call(SCI_HOME, SCI_UNUSED, SCI_UNUSED);
	}

	void HomeExtend() const {
		Call(SCI_HOMEEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void LineEnd() const {
		Call(SCI_LINEEND, SCI_UNUSED, SCI_UNUSED);
	}

	void LineEndExtend() const {
		Call(SCI_LINEENDEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void DocumentStart() const {
		Call(SCI_DOCUMENTSTART, SCI_UNUSED, SCI_UNUSED);
	}

	void DocumentStartExtend() const {
		Call(SCI_DOCUMENTSTARTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void DocumentEnd() const {
		Call(SCI_DOCUMENTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void DocumentEndExtend() const {
		Call(SCI_DOCUMENTENDEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void PageUp() const {
		Call(SCI_PAGEUP, SCI_UNUSED, SCI_UNUSED);
	}

	void PageUpExtend() const {
		Call(SCI_PAGEUPEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void PageDown() const {
		Call(SCI_PAGEDOWN, SCI_UNUSED, SCI_UNUSED);
	}

	void PageDownExtend() const {
		Call(SCI_PAGEDOWNEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void EditToggleOvertype() const {
		Call(SCI_EDITTOGGLEOVERTYPE, SCI_UNUSED, SCI_UNUSED);
	}

	void Cancel() const {
		Call(SCI_CANCEL, SCI_UNUSED, SCI_UNUSED);
	}

	void DeleteBack() const {
		Call(SCI_DELETEBACK, SCI_UNUSED, SCI_UNUSED);
	}

	void Tab() const {
		Call(SCI_TAB, SCI_UNUSED, SCI_UNUSED);
	}

	void BackTab() const {
		Call(SCI_BACKTAB, SCI_UNUSED, SCI_UNUSED);
	}

	void NewLine() const {
		Call(SCI_NEWLINE, SCI_UNUSED, SCI_UNUSED);
	}

	void FormFeed() const {
		Call(SCI_FORMFEED, SCI_UNUSED, SCI_UNUSED);
	}

	void VCHome() const {
		Call(SCI_VCHOME, SCI_UNUSED, SCI_UNUSED);
	}

	void VCHomeExtend() const {
		Call(SCI_VCHOMEEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void ZoomIn() const {
		Call(SCI_ZOOMIN, SCI_UNUSED, SCI_UNUSED);
	}

	void ZoomOut() const {
		Call(SCI_ZOOMOUT, SCI_UNUSED, SCI_UNUSED);
	}

	void DelWordLeft() const {
		Call(SCI_DELWORDLEFT, SCI_UNUSED, SCI_UNUSED);
	}

	void DelWordRight() const {
		Call(SCI_DELWORDRIGHT, SCI_UNUSED, SCI_UNUSED);
	}

	void DelWordRightEnd() const {
		Call(SCI_DELWORDRIGHTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void LineCut() const {
		Call(SCI_LINECUT, SCI_UNUSED, SCI_UNUSED);
	}

	void LineDelete() const {
		Call(SCI_LINEDELETE, SCI_UNUSED, SCI_UNUSED);
	}

	void LineTranspose() const {
		Call(SCI_LINETRANSPOSE, SCI_UNUSED, SCI_UNUSED);
	}

	void LineReverse() const {
		Call(SCI_LINEREVERSE, SCI_UNUSED, SCI_UNUSED);
	}

	void LineDuplicate() const {
		Call(SCI_LINEDUPLICATE, SCI_UNUSED, SCI_UNUSED);
	}

	void LowerCase() const {
		Call(SCI_LOWERCASE, SCI_UNUSED, SCI_UNUSED);
	}

	void UpperCase() const {
		Call(SCI_UPPERCASE, SCI_UNUSED, SCI_UNUSED);
	}

	void LineScrollDown() const {
		Call(SCI_LINESCROLLDOWN, SCI_UNUSED, SCI_UNUSED);
	}

	void LineScrollUp() const {
		Call(SCI_LINESCROLLUP, SCI_UNUSED, SCI_UNUSED);
	}

	void DeleteBackNotLine() const {
		Call(SCI_DELETEBACKNOTLINE, SCI_UNUSED, SCI_UNUSED);
	}

	void HomeDisplay() const {
		Call(SCI_HOMEDISPLAY, SCI_UNUSED, SCI_UNUSED);
	}

	void HomeDisplayExtend() const {
		Call(SCI_HOMEDISPLAYEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void LineEndDisplay() const {
		Call(SCI_LINEENDDISPLAY, SCI_UNUSED, SCI_UNUSED);
	}

	void LineEndDisplayExtend() const {
		Call(SCI_LINEENDDISPLAYEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void HomeWrap() const {
		Call(SCI_HOMEWRAP, SCI_UNUSED, SCI_UNUSED);
	}

	void HomeWrapExtend() const {
		Call(SCI_HOMEWRAPEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void LineEndWrap() const {
		Call(SCI_LINEENDWRAP, SCI_UNUSED, SCI_UNUSED);
	}

	void LineEndWrapExtend() const {
		Call(SCI_LINEENDWRAPEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void VCHomeWrap() const {
		Call(SCI_VCHOMEWRAP, SCI_UNUSED, SCI_UNUSED);
	}

	void VCHomeWrapExtend() const {
		Call(SCI_VCHOMEWRAPEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void LineCopy() const {
		Call(SCI_LINECOPY, SCI_UNUSED, SCI_UNUSED);
	}

	void MoveCaretInsideView() const {
		Call(SCI_MOVECARETINSIDEVIEW, SCI_UNUSED, SCI_UNUSED);
	}

	int LineLength(int line) const {
		sptr_t res = Call(SCI_LINELENGTH, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void BraceHighlight(int posA, int posB) const {
		Call(SCI_BRACEHIGHLIGHT, posA, posB);
	}

	void BraceHighlightIndicator(bool useSetting, int indicator) const {
		Call(SCI_BRACEHIGHLIGHTINDICATOR, useSetting, indicator);
	}

	void BraceBadLight(int pos) const {
		Call(SCI_BRACEBADLIGHT, pos, SCI_UNUSED);
	}

	void BraceBadLightIndicator(bool useSetting, int indicator) const {
		Call(SCI_BRACEBADLIGHTINDICATOR, useSetting, indicator);
	}

	int BraceMatch(int pos, int maxReStyle) const {
		sptr_t res = Call(SCI_BRACEMATCH, pos, maxReStyle);
		return static_cast<int>(res);
	}

	bool GetViewEOL() const {
		sptr_t res = Call(SCI_GETVIEWEOL, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetViewEOL(bool visible) const {
		Call(SCI_SETVIEWEOL, visible, SCI_UNUSED);
	}

	sptr_t GetDocPointer() const {
		return Call(SCI_GETDOCPOINTER, SCI_UNUSED, SCI_UNUSED);
	}

	void SetDocPointer(sptr_t doc) const {
		Call(SCI_SETDOCPOINTER, SCI_UNUSED, doc);
	}

	void SetModEventMask(int eventMask) const {
		Call(SCI_SETMODEVENTMASK, eventMask, SCI_UNUSED);
	}

	int GetEdgeColumn() const {
		sptr_t res = Call(SCI_GETEDGECOLUMN, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetEdgeColumn(int column) const {
		Call(SCI_SETEDGECOLUMN, column, SCI_UNUSED);
	}

	int GetEdgeMode() const {
		sptr_t res = Call(SCI_GETEDGEMODE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetEdgeMode(int edgeMode) const {
		Call(SCI_SETEDGEMODE, edgeMode, SCI_UNUSED);
	}

	Colour GetEdgeColour() const {
		sptr_t res = Call(SCI_GETEDGECOLOUR, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	void SetEdgeColour(Colour edgeColour) const {
		Call(SCI_SETEDGECOLOUR, edgeColour, SCI_UNUSED);
	}

	void MultiEdgeAddLine(int column, Colour edgeColour) const {
		Call(SCI_MULTIEDGEADDLINE, column, edgeColour);
	}

	void MultiEdgeClearAll() const {
		Call(SCI_MULTIEDGECLEARALL, SCI_UNUSED, SCI_UNUSED);
	}

	void SearchAnchor() const {
		Call(SCI_SEARCHANCHOR, SCI_UNUSED, SCI_UNUSED);
	}

	int SearchNext(int searchFlags, const char* text) const {
		sptr_t res = Call(SCI_SEARCHNEXT, searchFlags, text);
		return static_cast<int>(res);
	}

	int SearchNext(int searchFlags, const std::string& text) const {
		sptr_t res = Call(SCI_SEARCHNEXT, searchFlags, text.c_str());
		return static_cast<int>(res);
	}

	int SearchPrev(int searchFlags, const char* text) const {
		sptr_t res = Call(SCI_SEARCHPREV, searchFlags, text);
		return static_cast<int>(res);
	}

	int SearchPrev(int searchFlags, const std::string& text) const {
		sptr_t res = Call(SCI_SEARCHPREV, searchFlags, text.c_str());
		return static_cast<int>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position LinesOnScreen() const {
		sptr_t res = Call(SCI_LINESONSCREEN, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}

	void UsePopUp(int popUpMode) const {
		Call(SCI_USEPOPUP, popUpMode, SCI_UNUSED);
	}

	bool SelectionIsRectangle() const {
		sptr_t res = Call(SCI_SELECTIONISRECTANGLE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetZoom(int zoomInPoints) const {
		Call(SCI_SETZOOM, zoomInPoints, SCI_UNUSED);
	}

	int GetZoom() const {
		sptr_t res = Call(SCI_GETZOOM, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	sptr_t CreateDocument(int bytes, int documentOptions) const {
		return Call(SCI_CREATEDOCUMENT, bytes, documentOptions);
	}

	void AddRefDocument(sptr_t doc) const {
		Call(SCI_ADDREFDOCUMENT, SCI_UNUSED, doc);
	}

	void ReleaseDocument(sptr_t doc) const {
		Call(SCI_RELEASEDOCUMENT, SCI_UNUSED, doc);
	}

	int GetDocumentOptions() const {
		sptr_t res = Call(SCI_GETDOCUMENTOPTIONS, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetModEventMask() const {
		sptr_t res = Call(SCI_GETMODEVENTMASK, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetCommandEvents(bool commandEvents) const {
		Call(SCI_SETCOMMANDEVENTS, commandEvents, SCI_UNUSED);
	}

	bool GetCommandEvents() const {
		sptr_t res = Call(SCI_GETCOMMANDEVENTS, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetFocus(bool focus) const {
		Call(SCI_SETFOCUS, focus, SCI_UNUSED);
	}

	bool GetFocus() const {
		sptr_t res = Call(SCI_GETFOCUS, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetStatus(int status) const {
		Call(SCI_SETSTATUS, status, SCI_UNUSED);
	}

	int GetStatus() const {
		sptr_t res = Call(SCI_GETSTATUS, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetMouseDownCaptures(bool captures) const {
		Call(SCI_SETMOUSEDOWNCAPTURES, captures, SCI_UNUSED);
	}

	bool GetMouseDownCaptures() const {
		sptr_t res = Call(SCI_GETMOUSEDOWNCAPTURES, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetMouseWheelCaptures(bool captures) const {
		Call(SCI_SETMOUSEWHEELCAPTURES, captures, SCI_UNUSED);
	}

	bool GetMouseWheelCaptures() const {
		sptr_t res = Call(SCI_GETMOUSEWHEELCAPTURES, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetCursor(int cursorType) const {
		Call(SCI_SETCURSOR, cursorType, SCI_UNUSED);
	}

	int GetCursor() const {
		sptr_t res = Call(SCI_GETCURSOR, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetControlCharSymbol(int symbol) const {
		Call(SCI_SETCONTROLCHARSYMBOL, symbol, SCI_UNUSED);
	}

	int GetControlCharSymbol() const {
		sptr_t res = Call(SCI_GETCONTROLCHARSYMBOL, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void WordPartLeft() const {
		Call(SCI_WORDPARTLEFT, SCI_UNUSED, SCI_UNUSED);
	}

	void WordPartLeftExtend() const {
		Call(SCI_WORDPARTLEFTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void WordPartRight() const {
		Call(SCI_WORDPARTRIGHT, SCI_UNUSED, SCI_UNUSED);
	}

	void WordPartRightExtend() const {
		Call(SCI_WORDPARTRIGHTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void SetVisiblePolicy(int visiblePolicy, int visibleSlop) const {
		Call(SCI_SETVISIBLEPOLICY, visiblePolicy, visibleSlop);
	}

	void DelLineLeft() const {
		Call(SCI_DELLINELEFT, SCI_UNUSED, SCI_UNUSED);
	}

	void DelLineRight() const {
		Call(SCI_DELLINERIGHT, SCI_UNUSED, SCI_UNUSED);
	}

	void SetXOffset(int xOffset) const {
		Call(SCI_SETXOFFSET, xOffset, SCI_UNUSED);
	}

	int GetXOffset() const {
		sptr_t res = Call(SCI_GETXOFFSET, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void ChooseCaretX() const {
		Call(SCI_CHOOSECARETX, SCI_UNUSED, SCI_UNUSED);
	}

	void GrabFocus() const {
		Call(SCI_GRABFOCUS, SCI_UNUSED, SCI_UNUSED);
	}

	void SetXCaretPolicy(int caretPolicy, int caretSlop) const {
		Call(SCI_SETXCARETPOLICY, caretPolicy, caretSlop);
	}

	void SetYCaretPolicy(int caretPolicy, int caretSlop) const {
		Call(SCI_SETYCARETPOLICY, caretPolicy, caretSlop);
	}

	void SetPrintWrapMode(int wrapMode) const {
		Call(SCI_SETPRINTWRAPMODE, wrapMode, SCI_UNUSED);
	}

	int GetPrintWrapMode() const {
		sptr_t res = Call(SCI_GETPRINTWRAPMODE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetHotspotActiveFore(bool useSetting, Colour fore) const {
		Call(SCI_SETHOTSPOTACTIVEFORE, useSetting, fore);
	}

	Colour GetHotspotActiveFore() const {
		sptr_t res = Call(SCI_GETHOTSPOTACTIVEFORE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	void SetHotspotActiveBack(bool useSetting, Colour back) const {
		Call(SCI_SETHOTSPOTACTIVEBACK, useSetting, back);
	}

	Colour GetHotspotActiveBack() const {
		sptr_t res = Call(SCI_GETHOTSPOTACTIVEBACK, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	void SetHotspotActiveUnderline(bool underline) const {
		Call(SCI_SETHOTSPOTACTIVEUNDERLINE, underline, SCI_UNUSED);
	}

	bool GetHotspotActiveUnderline() const {
		sptr_t res = Call(SCI_GETHOTSPOTACTIVEUNDERLINE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetHotspotSingleLine(bool singleLine) const {
		Call(SCI_SETHOTSPOTSINGLELINE, singleLine, SCI_UNUSED);
	}

	bool GetHotspotSingleLine() const {
		sptr_t res = Call(SCI_GETHOTSPOTSINGLELINE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void ParaDown() const {
		Call(SCI_PARADOWN, SCI_UNUSED, SCI_UNUSED);
	}

	void ParaDownExtend() const {
		Call(SCI_PARADOWNEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void ParaUp() const {
		Call(SCI_PARAUP, SCI_UNUSED, SCI_UNUSED);
	}

	void ParaUpExtend() const {
		Call(SCI_PARAUPEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	int PositionBefore(int pos) const {
		sptr_t res = Call(SCI_POSITIONBEFORE, pos, SCI_UNUSED);
		return static_cast<int>(res);
	}
  /* 2GB+ compatible, used by ElasticTabstops */
  Sci_Position PositionAfter(Sci_Position pos) const {
		sptr_t res = Call(SCI_POSITIONAFTER, pos, SCI_UNUSED);
		return static_cast<Sci_Position>(res);
	}

	int PositionRelative(int pos, int relative) const {
		sptr_t res = Call(SCI_POSITIONRELATIVE, pos, relative);
		return static_cast<int>(res);
	}

	int PositionRelativeCodeUnits(int pos, int relative) const {
		sptr_t res = Call(SCI_POSITIONRELATIVECODEUNITS, pos, relative);
		return static_cast<int>(res);
	}

	void CopyRange(int start, int end) const {
		Call(SCI_COPYRANGE, start, end);
	}

	void CopyText(int length, const char* text) const {
		Call(SCI_COPYTEXT, length, text);
	}

	void CopyText(const std::string& text) const {
		Call(SCI_COPYTEXT, text.length(), text.c_str());
	}

	void SetSelectionMode(int selectionMode) const {
		Call(SCI_SETSELECTIONMODE, selectionMode, SCI_UNUSED);
	}

	int GetSelectionMode() const {
		sptr_t res = Call(SCI_GETSELECTIONMODE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	bool GetMoveExtendsSelection() const {
		sptr_t res = Call(SCI_GETMOVEEXTENDSSELECTION, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	int GetLineSelStartPosition(int line) const {
		sptr_t res = Call(SCI_GETLINESELSTARTPOSITION, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetLineSelEndPosition(int line) const {
		sptr_t res = Call(SCI_GETLINESELENDPOSITION, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void LineDownRectExtend() const {
		Call(SCI_LINEDOWNRECTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void LineUpRectExtend() const {
		Call(SCI_LINEUPRECTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void CharLeftRectExtend() const {
		Call(SCI_CHARLEFTRECTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void CharRightRectExtend() const {
		Call(SCI_CHARRIGHTRECTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void HomeRectExtend() const {
		Call(SCI_HOMERECTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void VCHomeRectExtend() const {
		Call(SCI_VCHOMERECTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void LineEndRectExtend() const {
		Call(SCI_LINEENDRECTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void PageUpRectExtend() const {
		Call(SCI_PAGEUPRECTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void PageDownRectExtend() const {
		Call(SCI_PAGEDOWNRECTEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void StutteredPageUp() const {
		Call(SCI_STUTTEREDPAGEUP, SCI_UNUSED, SCI_UNUSED);
	}

	void StutteredPageUpExtend() const {
		Call(SCI_STUTTEREDPAGEUPEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void StutteredPageDown() const {
		Call(SCI_STUTTEREDPAGEDOWN, SCI_UNUSED, SCI_UNUSED);
	}

	void StutteredPageDownExtend() const {
		Call(SCI_STUTTEREDPAGEDOWNEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void WordLeftEnd() const {
		Call(SCI_WORDLEFTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void WordLeftEndExtend() const {
		Call(SCI_WORDLEFTENDEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void WordRightEnd() const {
		Call(SCI_WORDRIGHTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void WordRightEndExtend() const {
		Call(SCI_WORDRIGHTENDEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	void SetWhitespaceChars(const char* characters) const {
		Call(SCI_SETWHITESPACECHARS, SCI_UNUSED, characters);
	}

	void SetWhitespaceChars(const std::string& characters) const {
		Call(SCI_SETWHITESPACECHARS, SCI_UNUSED, characters.c_str());
	}

	int GetWhitespaceChars(char* characters) const {
		sptr_t res = Call(SCI_GETWHITESPACECHARS, SCI_UNUSED, characters);
		return static_cast<int>(res);
	}

	std::string GetWhitespaceChars() const {
		auto size = Call(SCI_GETWHITESPACECHARS, SCI_UNUSED, NULL);
		std::string characters(size + 1, '\0');
		Call(SCI_GETWHITESPACECHARS, SCI_UNUSED, &characters[0]);
		trim(characters);
		return characters;
	}

	void SetPunctuationChars(const char* characters) const {
		Call(SCI_SETPUNCTUATIONCHARS, SCI_UNUSED, characters);
	}

	void SetPunctuationChars(const std::string& characters) const {
		Call(SCI_SETPUNCTUATIONCHARS, SCI_UNUSED, characters.c_str());
	}

	int GetPunctuationChars(char* characters) const {
		sptr_t res = Call(SCI_GETPUNCTUATIONCHARS, SCI_UNUSED, characters);
		return static_cast<int>(res);
	}

	std::string GetPunctuationChars() const {
		auto size = Call(SCI_GETPUNCTUATIONCHARS, SCI_UNUSED, NULL);
		std::string characters(size + 1, '\0');
		Call(SCI_GETPUNCTUATIONCHARS, SCI_UNUSED, &characters[0]);
		trim(characters);
		return characters;
	}

	void SetCharsDefault() const {
		Call(SCI_SETCHARSDEFAULT, SCI_UNUSED, SCI_UNUSED);
	}

	int AutoCGetCurrent() const {
		sptr_t res = Call(SCI_AUTOCGETCURRENT, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int AutoCGetCurrentText(char* text) const {
		sptr_t res = Call(SCI_AUTOCGETCURRENTTEXT, SCI_UNUSED, text);
		return static_cast<int>(res);
	}

	std::string AutoCGetCurrentText() const {
		auto size = Call(SCI_AUTOCGETCURRENTTEXT, SCI_UNUSED, NULL);
		std::string text(size + 1, '\0');
		Call(SCI_AUTOCGETCURRENTTEXT, SCI_UNUSED, &text[0]);
		trim(text);
		return text;
	}

	void AutoCSetCaseInsensitiveBehaviour(int behaviour) const {
		Call(SCI_AUTOCSETCASEINSENSITIVEBEHAVIOUR, behaviour, SCI_UNUSED);
	}

	int AutoCGetCaseInsensitiveBehaviour() const {
		sptr_t res = Call(SCI_AUTOCGETCASEINSENSITIVEBEHAVIOUR, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AutoCSetMulti(int multi) const {
		Call(SCI_AUTOCSETMULTI, multi, SCI_UNUSED);
	}

	int AutoCGetMulti() const {
		sptr_t res = Call(SCI_AUTOCGETMULTI, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AutoCSetOrder(int order) const {
		Call(SCI_AUTOCSETORDER, order, SCI_UNUSED);
	}

	int AutoCGetOrder() const {
		sptr_t res = Call(SCI_AUTOCGETORDER, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void Allocate(int bytes) const {
		Call(SCI_ALLOCATE, bytes, SCI_UNUSED);
	}

	int TargetAsUTF8(char* s) const {
		sptr_t res = Call(SCI_TARGETASUTF8, SCI_UNUSED, s);
		return static_cast<int>(res);
	}

	std::string TargetAsUTF8() const {
		auto size = Call(SCI_TARGETASUTF8, SCI_UNUSED, NULL);
		std::string s(size + 1, '\0');
		Call(SCI_TARGETASUTF8, SCI_UNUSED, &s[0]);
		trim(s);
		return s;
	}

	void SetLengthForEncode(int bytes) const {
		Call(SCI_SETLENGTHFORENCODE, bytes, SCI_UNUSED);
	}

	int EncodedFromUTF8(const char* utf8, char* encoded) const {
		sptr_t res = Call(SCI_ENCODEDFROMUTF8, utf8, encoded);
		return static_cast<int>(res);
	}

	std::string EncodedFromUTF8(const std::string& utf8) const {
		auto size = Call(SCI_ENCODEDFROMUTF8, utf8.c_str(), NULL);
		std::string encoded(size + 1, '\0');
		Call(SCI_ENCODEDFROMUTF8, utf8.c_str(), &encoded[0]);
		trim(encoded);
		return encoded;
	}

	int FindColumn(int line, int column) const {
		sptr_t res = Call(SCI_FINDCOLUMN, line, column);
		return static_cast<int>(res);
	}

	int GetCaretSticky() const {
		sptr_t res = Call(SCI_GETCARETSTICKY, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetCaretSticky(int useCaretStickyBehaviour) const {
		Call(SCI_SETCARETSTICKY, useCaretStickyBehaviour, SCI_UNUSED);
	}

	void ToggleCaretSticky() const {
		Call(SCI_TOGGLECARETSTICKY, SCI_UNUSED, SCI_UNUSED);
	}

	void SetPasteConvertEndings(bool convert) const {
		Call(SCI_SETPASTECONVERTENDINGS, convert, SCI_UNUSED);
	}

	bool GetPasteConvertEndings() const {
		sptr_t res = Call(SCI_GETPASTECONVERTENDINGS, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SelectionDuplicate() const {
		Call(SCI_SELECTIONDUPLICATE, SCI_UNUSED, SCI_UNUSED);
	}

	void SetCaretLineBackAlpha(int alpha) const {
		Call(SCI_SETCARETLINEBACKALPHA, alpha, SCI_UNUSED);
	}

	int GetCaretLineBackAlpha() const {
		sptr_t res = Call(SCI_GETCARETLINEBACKALPHA, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetCaretStyle(int caretStyle) const {
		Call(SCI_SETCARETSTYLE, caretStyle, SCI_UNUSED);
	}

	int GetCaretStyle() const {
		sptr_t res = Call(SCI_GETCARETSTYLE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}
  /* Used by ElasticTabstops only in Debug */
  void SetIndicatorCurrent(int indicator) const {
		Call(SCI_SETINDICATORCURRENT, indicator, SCI_UNUSED);
	}

	int GetIndicatorCurrent() const {
		sptr_t res = Call(SCI_GETINDICATORCURRENT, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetIndicatorValue(int value) const {
		Call(SCI_SETINDICATORVALUE, value, SCI_UNUSED);
	}

	int GetIndicatorValue() const {
		sptr_t res = Call(SCI_GETINDICATORVALUE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}
  /* Used by ElasticTabstops only in Debug */
  void IndicatorFillRange(Sci_Position start, Sci_Position lengthFill) const {
		Call(SCI_INDICATORFILLRANGE, start, lengthFill);
	}
  /* Used by ElasticTabstops only in Debug */
  void IndicatorClearRange(Sci_Position start, Sci_Position lengthClear) const {
		Call(SCI_INDICATORCLEARRANGE, start, lengthClear);
	}

	int IndicatorAllOnFor(int pos) const {
		sptr_t res = Call(SCI_INDICATORALLONFOR, pos, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int IndicatorValueAt(int indicator, int pos) const {
		sptr_t res = Call(SCI_INDICATORVALUEAT, indicator, pos);
		return static_cast<int>(res);
	}

	int IndicatorStart(int indicator, int pos) const {
		sptr_t res = Call(SCI_INDICATORSTART, indicator, pos);
		return static_cast<int>(res);
	}

	int IndicatorEnd(int indicator, int pos) const {
		sptr_t res = Call(SCI_INDICATOREND, indicator, pos);
		return static_cast<int>(res);
	}

	void SetPositionCache(int size) const {
		Call(SCI_SETPOSITIONCACHE, size, SCI_UNUSED);
	}

	int GetPositionCache() const {
		sptr_t res = Call(SCI_GETPOSITIONCACHE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void CopyAllowLine() const {
		Call(SCI_COPYALLOWLINE, SCI_UNUSED, SCI_UNUSED);
	}

	const char* GetCharacterPointer() const {
		sptr_t res = Call(SCI_GETCHARACTERPOINTER, SCI_UNUSED, SCI_UNUSED);
		return reinterpret_cast<const char*>(res);
	}

	const char* GetRangePointer(int start, int lengthRange) const {
		sptr_t res = Call(SCI_GETRANGEPOINTER, start, lengthRange);
		return reinterpret_cast<const char*>(res);
	}

	int GetGapPosition() const {
		sptr_t res = Call(SCI_GETGAPPOSITION, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void IndicSetAlpha(int indicator, int alpha) const {
		Call(SCI_INDICSETALPHA, indicator, alpha);
	}

	int IndicGetAlpha(int indicator) const {
		sptr_t res = Call(SCI_INDICGETALPHA, indicator, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void IndicSetOutlineAlpha(int indicator, int alpha) const {
		Call(SCI_INDICSETOUTLINEALPHA, indicator, alpha);
	}

	int IndicGetOutlineAlpha(int indicator) const {
		sptr_t res = Call(SCI_INDICGETOUTLINEALPHA, indicator, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetExtraAscent(int extraAscent) const {
		Call(SCI_SETEXTRAASCENT, extraAscent, SCI_UNUSED);
	}

	int GetExtraAscent() const {
		sptr_t res = Call(SCI_GETEXTRAASCENT, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetExtraDescent(int extraDescent) const {
		Call(SCI_SETEXTRADESCENT, extraDescent, SCI_UNUSED);
	}

	int GetExtraDescent() const {
		sptr_t res = Call(SCI_GETEXTRADESCENT, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int MarkerSymbolDefined(int markerNumber) const {
		sptr_t res = Call(SCI_MARKERSYMBOLDEFINED, markerNumber, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void MarginSetText(int line, const char* text) const {
		Call(SCI_MARGINSETTEXT, line, text);
	}

	void MarginSetText(int line, const std::string& text) const {
		Call(SCI_MARGINSETTEXT, line, text.c_str());
	}

	int MarginGetText(int line, char* text) const {
		sptr_t res = Call(SCI_MARGINGETTEXT, line, text);
		return static_cast<int>(res);
	}

	std::string MarginGetText(int line) const {
		auto size = Call(SCI_MARGINGETTEXT, line, NULL);
		std::string text(size + 1, '\0');
		Call(SCI_MARGINGETTEXT, line, &text[0]);
		trim(text);
		return text;
	}

	void MarginSetStyle(int line, int style) const {
		Call(SCI_MARGINSETSTYLE, line, style);
	}

	int MarginGetStyle(int line) const {
		sptr_t res = Call(SCI_MARGINGETSTYLE, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void MarginSetStyles(int line, const char* styles) const {
		Call(SCI_MARGINSETSTYLES, line, styles);
	}

	void MarginSetStyles(int line, const std::string& styles) const {
		Call(SCI_MARGINSETSTYLES, line, styles.c_str());
	}

	int MarginGetStyles(int line, char* styles) const {
		sptr_t res = Call(SCI_MARGINGETSTYLES, line, styles);
		return static_cast<int>(res);
	}

	std::string MarginGetStyles(int line) const {
		auto size = Call(SCI_MARGINGETSTYLES, line, NULL);
		std::string styles(size + 1, '\0');
		Call(SCI_MARGINGETSTYLES, line, &styles[0]);
		trim(styles);
		return styles;
	}

	void MarginTextClearAll() const {
		Call(SCI_MARGINTEXTCLEARALL, SCI_UNUSED, SCI_UNUSED);
	}

	void MarginSetStyleOffset(int style) const {
		Call(SCI_MARGINSETSTYLEOFFSET, style, SCI_UNUSED);
	}

	int MarginGetStyleOffset() const {
		sptr_t res = Call(SCI_MARGINGETSTYLEOFFSET, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetMarginOptions(int marginOptions) const {
		Call(SCI_SETMARGINOPTIONS, marginOptions, SCI_UNUSED);
	}

	int GetMarginOptions() const {
		sptr_t res = Call(SCI_GETMARGINOPTIONS, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AnnotationSetText(int line, const char* text) const {
		Call(SCI_ANNOTATIONSETTEXT, line, text);
	}

	void AnnotationSetText(int line, const std::string& text) const {
		Call(SCI_ANNOTATIONSETTEXT, line, text.c_str());
	}

	int AnnotationGetText(int line, char* text) const {
		sptr_t res = Call(SCI_ANNOTATIONGETTEXT, line, text);
		return static_cast<int>(res);
	}

	std::string AnnotationGetText(int line) const {
		auto size = Call(SCI_ANNOTATIONGETTEXT, line, NULL);
		std::string text(size + 1, '\0');
		Call(SCI_ANNOTATIONGETTEXT, line, &text[0]);
		trim(text);
		return text;
	}

	void AnnotationSetStyle(int line, int style) const {
		Call(SCI_ANNOTATIONSETSTYLE, line, style);
	}

	int AnnotationGetStyle(int line) const {
		sptr_t res = Call(SCI_ANNOTATIONGETSTYLE, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AnnotationSetStyles(int line, const char* styles) const {
		Call(SCI_ANNOTATIONSETSTYLES, line, styles);
	}

	void AnnotationSetStyles(int line, const std::string& styles) const {
		Call(SCI_ANNOTATIONSETSTYLES, line, styles.c_str());
	}

	int AnnotationGetStyles(int line, char* styles) const {
		sptr_t res = Call(SCI_ANNOTATIONGETSTYLES, line, styles);
		return static_cast<int>(res);
	}

	std::string AnnotationGetStyles(int line) const {
		auto size = Call(SCI_ANNOTATIONGETSTYLES, line, NULL);
		std::string styles(size + 1, '\0');
		Call(SCI_ANNOTATIONGETSTYLES, line, &styles[0]);
		trim(styles);
		return styles;
	}

	int AnnotationGetLines(int line) const {
		sptr_t res = Call(SCI_ANNOTATIONGETLINES, line, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AnnotationClearAll() const {
		Call(SCI_ANNOTATIONCLEARALL, SCI_UNUSED, SCI_UNUSED);
	}

	void AnnotationSetVisible(int visible) const {
		Call(SCI_ANNOTATIONSETVISIBLE, visible, SCI_UNUSED);
	}

	int AnnotationGetVisible() const {
		sptr_t res = Call(SCI_ANNOTATIONGETVISIBLE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AnnotationSetStyleOffset(int style) const {
		Call(SCI_ANNOTATIONSETSTYLEOFFSET, style, SCI_UNUSED);
	}

	int AnnotationGetStyleOffset() const {
		sptr_t res = Call(SCI_ANNOTATIONGETSTYLEOFFSET, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void ReleaseAllExtendedStyles() const {
		Call(SCI_RELEASEALLEXTENDEDSTYLES, SCI_UNUSED, SCI_UNUSED);
	}

	int AllocateExtendedStyles(int numberStyles) const {
		sptr_t res = Call(SCI_ALLOCATEEXTENDEDSTYLES, numberStyles, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AddUndoAction(int token, int flags) const {
		Call(SCI_ADDUNDOACTION, token, flags);
	}

	int CharPositionFromPoint(int x, int y) const {
		sptr_t res = Call(SCI_CHARPOSITIONFROMPOINT, x, y);
		return static_cast<int>(res);
	}

	int CharPositionFromPointClose(int x, int y) const {
		sptr_t res = Call(SCI_CHARPOSITIONFROMPOINTCLOSE, x, y);
		return static_cast<int>(res);
	}

	void SetMouseSelectionRectangularSwitch(bool mouseSelectionRectangularSwitch) const {
		Call(SCI_SETMOUSESELECTIONRECTANGULARSWITCH, mouseSelectionRectangularSwitch, SCI_UNUSED);
	}

	bool GetMouseSelectionRectangularSwitch() const {
		sptr_t res = Call(SCI_GETMOUSESELECTIONRECTANGULARSWITCH, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetMultipleSelection(bool multipleSelection) const {
		Call(SCI_SETMULTIPLESELECTION, multipleSelection, SCI_UNUSED);
	}

	bool GetMultipleSelection() const {
		sptr_t res = Call(SCI_GETMULTIPLESELECTION, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetAdditionalSelectionTyping(bool additionalSelectionTyping) const {
		Call(SCI_SETADDITIONALSELECTIONTYPING, additionalSelectionTyping, SCI_UNUSED);
	}

	bool GetAdditionalSelectionTyping() const {
		sptr_t res = Call(SCI_GETADDITIONALSELECTIONTYPING, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetAdditionalCaretsBlink(bool additionalCaretsBlink) const {
		Call(SCI_SETADDITIONALCARETSBLINK, additionalCaretsBlink, SCI_UNUSED);
	}

	bool GetAdditionalCaretsBlink() const {
		sptr_t res = Call(SCI_GETADDITIONALCARETSBLINK, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetAdditionalCaretsVisible(bool additionalCaretsVisible) const {
		Call(SCI_SETADDITIONALCARETSVISIBLE, additionalCaretsVisible, SCI_UNUSED);
	}

	bool GetAdditionalCaretsVisible() const {
		sptr_t res = Call(SCI_GETADDITIONALCARETSVISIBLE, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	int GetSelections() const {
		sptr_t res = Call(SCI_GETSELECTIONS, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	bool GetSelectionEmpty() const {
		sptr_t res = Call(SCI_GETSELECTIONEMPTY, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void ClearSelections() const {
		Call(SCI_CLEARSELECTIONS, SCI_UNUSED, SCI_UNUSED);
	}

	void SetSelection(int caret, int anchor) const {
		Call(SCI_SETSELECTION, caret, anchor);
	}

	void AddSelection(int caret, int anchor) const {
		Call(SCI_ADDSELECTION, caret, anchor);
	}

	void DropSelectionN(int selection) const {
		Call(SCI_DROPSELECTIONN, selection, SCI_UNUSED);
	}

	void SetMainSelection(int selection) const {
		Call(SCI_SETMAINSELECTION, selection, SCI_UNUSED);
	}

	int GetMainSelection() const {
		sptr_t res = Call(SCI_GETMAINSELECTION, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetSelectionNCaret(int selection, int caret) const {
		Call(SCI_SETSELECTIONNCARET, selection, caret);
	}

	int GetSelectionNCaret(int selection) const {
		sptr_t res = Call(SCI_GETSELECTIONNCARET, selection, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetSelectionNAnchor(int selection, int anchor) const {
		Call(SCI_SETSELECTIONNANCHOR, selection, anchor);
	}

	int GetSelectionNAnchor(int selection) const {
		sptr_t res = Call(SCI_GETSELECTIONNANCHOR, selection, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetSelectionNCaretVirtualSpace(int selection, int space) const {
		Call(SCI_SETSELECTIONNCARETVIRTUALSPACE, selection, space);
	}

	int GetSelectionNCaretVirtualSpace(int selection) const {
		sptr_t res = Call(SCI_GETSELECTIONNCARETVIRTUALSPACE, selection, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetSelectionNAnchorVirtualSpace(int selection, int space) const {
		Call(SCI_SETSELECTIONNANCHORVIRTUALSPACE, selection, space);
	}

	int GetSelectionNAnchorVirtualSpace(int selection) const {
		sptr_t res = Call(SCI_GETSELECTIONNANCHORVIRTUALSPACE, selection, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetSelectionNStart(int selection, int anchor) const {
		Call(SCI_SETSELECTIONNSTART, selection, anchor);
	}

	int GetSelectionNStart(int selection) const {
		sptr_t res = Call(SCI_GETSELECTIONNSTART, selection, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetSelectionNEnd(int selection, int caret) const {
		Call(SCI_SETSELECTIONNEND, selection, caret);
	}

	int GetSelectionNEnd(int selection) const {
		sptr_t res = Call(SCI_GETSELECTIONNEND, selection, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetRectangularSelectionCaret(int caret) const {
		Call(SCI_SETRECTANGULARSELECTIONCARET, caret, SCI_UNUSED);
	}

	int GetRectangularSelectionCaret() const {
		sptr_t res = Call(SCI_GETRECTANGULARSELECTIONCARET, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetRectangularSelectionAnchor(int anchor) const {
		Call(SCI_SETRECTANGULARSELECTIONANCHOR, anchor, SCI_UNUSED);
	}

	int GetRectangularSelectionAnchor() const {
		sptr_t res = Call(SCI_GETRECTANGULARSELECTIONANCHOR, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetRectangularSelectionCaretVirtualSpace(int space) const {
		Call(SCI_SETRECTANGULARSELECTIONCARETVIRTUALSPACE, space, SCI_UNUSED);
	}

	int GetRectangularSelectionCaretVirtualSpace() const {
		sptr_t res = Call(SCI_GETRECTANGULARSELECTIONCARETVIRTUALSPACE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetRectangularSelectionAnchorVirtualSpace(int space) const {
		Call(SCI_SETRECTANGULARSELECTIONANCHORVIRTUALSPACE, space, SCI_UNUSED);
	}

	int GetRectangularSelectionAnchorVirtualSpace() const {
		sptr_t res = Call(SCI_GETRECTANGULARSELECTIONANCHORVIRTUALSPACE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetVirtualSpaceOptions(int virtualSpaceOptions) const {
		Call(SCI_SETVIRTUALSPACEOPTIONS, virtualSpaceOptions, SCI_UNUSED);
	}

	int GetVirtualSpaceOptions() const {
		sptr_t res = Call(SCI_GETVIRTUALSPACEOPTIONS, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetRectangularSelectionModifier(int modifier) const {
		Call(SCI_SETRECTANGULARSELECTIONMODIFIER, modifier, SCI_UNUSED);
	}

	int GetRectangularSelectionModifier() const {
		sptr_t res = Call(SCI_GETRECTANGULARSELECTIONMODIFIER, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetAdditionalSelFore(Colour fore) const {
		Call(SCI_SETADDITIONALSELFORE, fore, SCI_UNUSED);
	}

	void SetAdditionalSelBack(Colour back) const {
		Call(SCI_SETADDITIONALSELBACK, back, SCI_UNUSED);
	}

	void SetAdditionalSelAlpha(int alpha) const {
		Call(SCI_SETADDITIONALSELALPHA, alpha, SCI_UNUSED);
	}

	int GetAdditionalSelAlpha() const {
		sptr_t res = Call(SCI_GETADDITIONALSELALPHA, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetAdditionalCaretFore(Colour fore) const {
		Call(SCI_SETADDITIONALCARETFORE, fore, SCI_UNUSED);
	}

	Colour GetAdditionalCaretFore() const {
		sptr_t res = Call(SCI_GETADDITIONALCARETFORE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<Colour>(res);
	}

	void RotateSelection() const {
		Call(SCI_ROTATESELECTION, SCI_UNUSED, SCI_UNUSED);
	}

	void SwapMainAnchorCaret() const {
		Call(SCI_SWAPMAINANCHORCARET, SCI_UNUSED, SCI_UNUSED);
	}

	void MultipleSelectAddNext() const {
		Call(SCI_MULTIPLESELECTADDNEXT, SCI_UNUSED, SCI_UNUSED);
	}

	void MultipleSelectAddEach() const {
		Call(SCI_MULTIPLESELECTADDEACH, SCI_UNUSED, SCI_UNUSED);
	}

	int ChangeLexerState(int start, int end) const {
		sptr_t res = Call(SCI_CHANGELEXERSTATE, start, end);
		return static_cast<int>(res);
	}

	int ContractedFoldNext(int lineStart) const {
		sptr_t res = Call(SCI_CONTRACTEDFOLDNEXT, lineStart, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void VerticalCentreCaret() const {
		Call(SCI_VERTICALCENTRECARET, SCI_UNUSED, SCI_UNUSED);
	}

	void MoveSelectedLinesUp() const {
		Call(SCI_MOVESELECTEDLINESUP, SCI_UNUSED, SCI_UNUSED);
	}

	void MoveSelectedLinesDown() const {
		Call(SCI_MOVESELECTEDLINESDOWN, SCI_UNUSED, SCI_UNUSED);
	}

	void SetIdentifier(int identifier) const {
		Call(SCI_SETIDENTIFIER, identifier, SCI_UNUSED);
	}

	int GetIdentifier() const {
		sptr_t res = Call(SCI_GETIDENTIFIER, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void RGBAImageSetWidth(int width) const {
		Call(SCI_RGBAIMAGESETWIDTH, width, SCI_UNUSED);
	}

	void RGBAImageSetHeight(int height) const {
		Call(SCI_RGBAIMAGESETHEIGHT, height, SCI_UNUSED);
	}

	void RGBAImageSetScale(int scalePercent) const {
		Call(SCI_RGBAIMAGESETSCALE, scalePercent, SCI_UNUSED);
	}

	void MarkerDefineRGBAImage(int markerNumber, const char* pixels) const {
		Call(SCI_MARKERDEFINERGBAIMAGE, markerNumber, pixels);
	}

	void MarkerDefineRGBAImage(int markerNumber, const std::string& pixels) const {
		Call(SCI_MARKERDEFINERGBAIMAGE, markerNumber, pixels.c_str());
	}

	void RegisterRGBAImage(int type, const char* pixels) const {
		Call(SCI_REGISTERRGBAIMAGE, type, pixels);
	}

	void RegisterRGBAImage(int type, const std::string& pixels) const {
		Call(SCI_REGISTERRGBAIMAGE, type, pixels.c_str());
	}

	void ScrollToStart() const {
		Call(SCI_SCROLLTOSTART, SCI_UNUSED, SCI_UNUSED);
	}

	void ScrollToEnd() const {
		Call(SCI_SCROLLTOEND, SCI_UNUSED, SCI_UNUSED);
	}

	void SetTechnology(int technology) const {
		Call(SCI_SETTECHNOLOGY, technology, SCI_UNUSED);
	}

	int GetTechnology() const {
		sptr_t res = Call(SCI_GETTECHNOLOGY, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int CreateLoader(int bytes, int documentOptions) const {
		sptr_t res = Call(SCI_CREATELOADER, bytes, documentOptions);
		return static_cast<int>(res);
	}

	void FindIndicatorShow(int start, int end) const {
		Call(SCI_FINDINDICATORSHOW, start, end);
	}

	void FindIndicatorFlash(int start, int end) const {
		Call(SCI_FINDINDICATORFLASH, start, end);
	}

	void FindIndicatorHide() const {
		Call(SCI_FINDINDICATORHIDE, SCI_UNUSED, SCI_UNUSED);
	}

	void VCHomeDisplay() const {
		Call(SCI_VCHOMEDISPLAY, SCI_UNUSED, SCI_UNUSED);
	}

	void VCHomeDisplayExtend() const {
		Call(SCI_VCHOMEDISPLAYEXTEND, SCI_UNUSED, SCI_UNUSED);
	}

	bool GetCaretLineVisibleAlways() const {
		sptr_t res = Call(SCI_GETCARETLINEVISIBLEALWAYS, SCI_UNUSED, SCI_UNUSED);
		return res != 0;
	}

	void SetCaretLineVisibleAlways(bool alwaysVisible) const {
		Call(SCI_SETCARETLINEVISIBLEALWAYS, alwaysVisible, SCI_UNUSED);
	}

	void SetLineEndTypesAllowed(int lineEndBitSet) const {
		Call(SCI_SETLINEENDTYPESALLOWED, lineEndBitSet, SCI_UNUSED);
	}

	int GetLineEndTypesAllowed() const {
		sptr_t res = Call(SCI_GETLINEENDTYPESALLOWED, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetLineEndTypesActive() const {
		sptr_t res = Call(SCI_GETLINEENDTYPESACTIVE, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetRepresentation(const char* encodedCharacter, const char* representation) const {
		Call(SCI_SETREPRESENTATION, encodedCharacter, representation);
	}

	void SetRepresentation(const std::string& encodedCharacter, const std::string& representation) const {
		Call(SCI_SETREPRESENTATION, encodedCharacter.c_str(), representation.c_str());
	}

	int GetRepresentation(const char* encodedCharacter, char* representation) const {
		sptr_t res = Call(SCI_GETREPRESENTATION, encodedCharacter, representation);
		return static_cast<int>(res);
	}

	std::string GetRepresentation(const std::string& encodedCharacter) const {
		auto size = Call(SCI_GETREPRESENTATION, encodedCharacter.c_str(), NULL);
		std::string representation(size + 1, '\0');
		Call(SCI_GETREPRESENTATION, encodedCharacter.c_str(), &representation[0]);
		trim(representation);
		return representation;
	}

	void ClearRepresentation(const char* encodedCharacter) const {
		Call(SCI_CLEARREPRESENTATION, encodedCharacter, SCI_UNUSED);
	}

	void ClearRepresentation(const std::string& encodedCharacter) const {
		Call(SCI_CLEARREPRESENTATION, encodedCharacter.c_str(), SCI_UNUSED);
	}

	void StartRecord() const {
		Call(SCI_STARTRECORD, SCI_UNUSED, SCI_UNUSED);
	}

	void StopRecord() const {
		Call(SCI_STOPRECORD, SCI_UNUSED, SCI_UNUSED);
	}

	//void SetLexer(int lexer) const {
	//	Call(SCI_SETLEXER, lexer, SCI_UNUSED);
	//}

	int GetLexer() const {
		sptr_t res = Call(SCI_GETLEXER, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void Colourise(int start, int end) const {
		Call(SCI_COLOURISE, start, end);
	}

	void SetProperty(const char* key, const char* value) const {
		Call(SCI_SETPROPERTY, key, value);
	}

	void SetProperty(const std::string& key, const std::string& value) const {
		Call(SCI_SETPROPERTY, key.c_str(), value.c_str());
	}

	void SetKeyWords(int keyWordSet, const char* keyWords) const {
		Call(SCI_SETKEYWORDS, keyWordSet, keyWords);
	}

	void SetKeyWords(int keyWordSet, const std::string& keyWords) const {
		Call(SCI_SETKEYWORDS, keyWordSet, keyWords.c_str());
	}
  /*
	void SetLexerLanguage(const char* language) const {
		Call(SCI_SETLEXERLANGUAGE, SCI_UNUSED, language);
	}

	void SetLexerLanguage(const std::string& language) const {
		Call(SCI_SETLEXERLANGUAGE, SCI_UNUSED, language.c_str());
	}

	void LoadLexerLibrary(const char* path) const {
		Call(SCI_LOADLEXERLIBRARY, SCI_UNUSED, path);
	}

	void LoadLexerLibrary(const std::string& path) const {
		Call(SCI_LOADLEXERLIBRARY, SCI_UNUSED, path.c_str());
	}*/

	int GetProperty(const char* key, char* value) const {
		sptr_t res = Call(SCI_GETPROPERTY, key, value);
		return static_cast<int>(res);
	}

	std::string GetProperty(const std::string& key) const {
		auto size = Call(SCI_GETPROPERTY, key.c_str(), NULL);
		std::string value(size + 1, '\0');
		Call(SCI_GETPROPERTY, key.c_str(), &value[0]);
		trim(value);
		return value;
	}

	int GetPropertyExpanded(const char* key, char* value) const {
		sptr_t res = Call(SCI_GETPROPERTYEXPANDED, key, value);
		return static_cast<int>(res);
	}

	std::string GetPropertyExpanded(const std::string& key) const {
		auto size = Call(SCI_GETPROPERTYEXPANDED, key.c_str(), NULL);
		std::string value(size + 1, '\0');
		Call(SCI_GETPROPERTYEXPANDED, key.c_str(), &value[0]);
		trim(value);
		return value;
	}

	int GetPropertyInt(const char* key, int defaultValue) const {
		sptr_t res = Call(SCI_GETPROPERTYINT, key, defaultValue);
		return static_cast<int>(res);
	}

	int GetPropertyInt(const std::string& key, int defaultValue) const {
		sptr_t res = Call(SCI_GETPROPERTYINT, key.c_str(), defaultValue);
		return static_cast<int>(res);
	}

	int GetLexerLanguage(char* language) const {
		sptr_t res = Call(SCI_GETLEXERLANGUAGE, SCI_UNUSED, language);
		return static_cast<int>(res);
	}

	std::string GetLexerLanguage() const {
		auto size = Call(SCI_GETLEXERLANGUAGE, SCI_UNUSED, NULL);
		std::string language(size + 1, '\0');
		Call(SCI_GETLEXERLANGUAGE, SCI_UNUSED, &language[0]);
		trim(language);
		return language;
	}

	int PrivateLexerCall(int operation, sptr_t pointer) const {
		sptr_t res = Call(SCI_PRIVATELEXERCALL, operation, pointer);
		return static_cast<int>(res);
	}

	int PropertyNames(char* names) const {
		sptr_t res = Call(SCI_PROPERTYNAMES, SCI_UNUSED, names);
		return static_cast<int>(res);
	}

	std::string PropertyNames() const {
		auto size = Call(SCI_PROPERTYNAMES, SCI_UNUSED, NULL);
		std::string names(size + 1, '\0');
		Call(SCI_PROPERTYNAMES, SCI_UNUSED, &names[0]);
		trim(names);
		return names;
	}

	int PropertyType(const char* name) const {
		sptr_t res = Call(SCI_PROPERTYTYPE, name, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int PropertyType(const std::string& name) const {
		sptr_t res = Call(SCI_PROPERTYTYPE, name.c_str(), SCI_UNUSED);
		return static_cast<int>(res);
	}

	int DescribeProperty(const char* name, char* description) const {
		sptr_t res = Call(SCI_DESCRIBEPROPERTY, name, description);
		return static_cast<int>(res);
	}

	std::string DescribeProperty(const std::string& name) const {
		auto size = Call(SCI_DESCRIBEPROPERTY, name.c_str(), NULL);
		std::string description(size + 1, '\0');
		Call(SCI_DESCRIBEPROPERTY, name.c_str(), &description[0]);
		trim(description);
		return description;
	}

	int DescribeKeyWordSets(char* descriptions) const {
		sptr_t res = Call(SCI_DESCRIBEKEYWORDSETS, SCI_UNUSED, descriptions);
		return static_cast<int>(res);
	}

	std::string DescribeKeyWordSets() const {
		auto size = Call(SCI_DESCRIBEKEYWORDSETS, SCI_UNUSED, NULL);
		std::string descriptions(size + 1, '\0');
		Call(SCI_DESCRIBEKEYWORDSETS, SCI_UNUSED, &descriptions[0]);
		trim(descriptions);
		return descriptions;
	}

	int GetLineEndTypesSupported() const {
		sptr_t res = Call(SCI_GETLINEENDTYPESSUPPORTED, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int AllocateSubStyles(int styleBase, int numberStyles) const {
		sptr_t res = Call(SCI_ALLOCATESUBSTYLES, styleBase, numberStyles);
		return static_cast<int>(res);
	}

	int GetSubStylesStart(int styleBase) const {
		sptr_t res = Call(SCI_GETSUBSTYLESSTART, styleBase, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetSubStylesLength(int styleBase) const {
		sptr_t res = Call(SCI_GETSUBSTYLESLENGTH, styleBase, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetStyleFromSubStyle(int subStyle) const {
		sptr_t res = Call(SCI_GETSTYLEFROMSUBSTYLE, subStyle, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetPrimaryStyleFromStyle(int style) const {
		sptr_t res = Call(SCI_GETPRIMARYSTYLEFROMSTYLE, style, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void FreeSubStyles() const {
		Call(SCI_FREESUBSTYLES, SCI_UNUSED, SCI_UNUSED);
	}

	void SetIdentifiers(int style, const char* identifiers) const {
		Call(SCI_SETIDENTIFIERS, style, identifiers);
	}

	void SetIdentifiers(int style, const std::string& identifiers) const {
		Call(SCI_SETIDENTIFIERS, style, identifiers.c_str());
	}

	int DistanceToSecondaryStyles() const {
		sptr_t res = Call(SCI_DISTANCETOSECONDARYSTYLES, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int GetSubStyleBases(char* styles) const {
		sptr_t res = Call(SCI_GETSUBSTYLEBASES, SCI_UNUSED, styles);
		return static_cast<int>(res);
	}

	std::string GetSubStyleBases() const {
		auto size = Call(SCI_GETSUBSTYLEBASES, SCI_UNUSED, NULL);
		std::string styles(size + 1, '\0');
		Call(SCI_GETSUBSTYLEBASES, SCI_UNUSED, &styles[0]);
		trim(styles);
		return styles;
	}

	int GetNamedStyles() const {
		sptr_t res = Call(SCI_GETNAMEDSTYLES, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	int NameOfStyle(int style, char* name) const {
		sptr_t res = Call(SCI_NAMEOFSTYLE, style, name);
		return static_cast<int>(res);
	}

	std::string NameOfStyle(int style) const {
		auto size = Call(SCI_NAMEOFSTYLE, style, NULL);
		std::string name(size + 1, '\0');
		Call(SCI_NAMEOFSTYLE, style, &name[0]);
		trim(name);
		return name;
	}

	int TagsOfStyle(int style, char* tags) const {
		sptr_t res = Call(SCI_TAGSOFSTYLE, style, tags);
		return static_cast<int>(res);
	}

	std::string TagsOfStyle(int style) const {
		auto size = Call(SCI_TAGSOFSTYLE, style, NULL);
		std::string tags(size + 1, '\0');
		Call(SCI_TAGSOFSTYLE, style, &tags[0]);
		trim(tags);
		return tags;
	}

	int DescriptionOfStyle(int style, char* description) const {
		sptr_t res = Call(SCI_DESCRIPTIONOFSTYLE, style, description);
		return static_cast<int>(res);
	}

	std::string DescriptionOfStyle(int style) const {
		auto size = Call(SCI_DESCRIPTIONOFSTYLE, style, NULL);
		std::string description(size + 1, '\0');
		Call(SCI_DESCRIPTIONOFSTYLE, style, &description[0]);
		trim(description);
		return description;
	}

	int GetBidirectional() const {
		sptr_t res = Call(SCI_GETBIDIRECTIONAL, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void SetBidirectional(int bidirectional) const {
		Call(SCI_SETBIDIRECTIONAL, bidirectional, SCI_UNUSED);
	}

	int GetLineCharacterIndex() const {
		sptr_t res = Call(SCI_GETLINECHARACTERINDEX, SCI_UNUSED, SCI_UNUSED);
		return static_cast<int>(res);
	}

	void AllocateLineCharacterIndex(int lineCharacterIndex) const {
		Call(SCI_ALLOCATELINECHARACTERINDEX, lineCharacterIndex, SCI_UNUSED);
	}

	void ReleaseLineCharacterIndex(int lineCharacterIndex) const {
		Call(SCI_RELEASELINECHARACTERINDEX, lineCharacterIndex, SCI_UNUSED);
	}

	int LineFromIndexPosition(int pos, int lineCharacterIndex) const {
		sptr_t res = Call(SCI_LINEFROMINDEXPOSITION, pos, lineCharacterIndex);
		return static_cast<int>(res);
	}

	int IndexPositionFromLine(int line, int lineCharacterIndex) const {
		sptr_t res = Call(SCI_INDEXPOSITIONFROMLINE, line, lineCharacterIndex);
		return static_cast<int>(res);
	}

	/* --Autogenerated -- end of section automatically generated from Scintilla.iface */
};

__declspec(selectany) ScintillaEditor::Direct ScintillaEditor::direct[]={{0,0},{0,0}};
__declspec(selectany) const unsigned ScintillaEditor::DIRECT_SZ=sizeof(direct)/sizeof(direct[0]);
static_assert(ScintillaEditor::DIRECT_SZ==2, "NPP has only 2 Scintilla views");
