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

#include "ElasticTabstops.h"
#include "AboutDialog.h"

//#define USE_CONSOLE
#ifdef USE_CONSOLE
#include <stdio.h>
// this class allow you to use printf/cout in any Windows GUI application
class CConsole
{
public:
#pragma warning( push )
#pragma warning( disable : 4996)
  // attach to the parent console if any (as command line launching) or create a new one
  CConsole() { if(!::AttachConsole(ATTACH_PARENT_PROCESS)) ::AllocConsole(); freopen("CONOUT$", "wb", stdout); }
  ~CConsole() { fclose(stdout); ::FreeConsole(); }
#pragma warning( pop )
};
// this global object can be erased by linker optimizations in Release version so better use this class
// as an acestor of any unique object of your application like CWinApp object in a MFC application
__declspec(selectany) CConsole globConsole;
#endif //USE_CONSOLE

// TODO: synchronize "Convert Tabstops to Spaces" enable state in any condition: initial New file, tab switching, file closing, config ini file saving
// TODO: synchronize files/menus states after a "Reset settings"
// TODO: synchronize files/menus states after a FctToggleEnabled()
// ONLY SOLUTION: share all significant variables as attributes of the future ElasticTabstops class & global object

void FctToggleEnabled()  { elTabs.OnToggleEnabled(funcItem[IdxToggleEnabled]._cmdID); }
void FctToggleSelOnly()  { elTabs.OnToggleSelOnly(funcItem[IdxToggleSelOnly]._cmdID); }
void FctToggleGlobTabs() { elTabs.OnToggleGlobTabs(funcItem[IdxToggleGlobTabs]._cmdID); }
void FctConvEt2Spaces()  { elTabs.OnConvEt2Spaces(); }
void FctConvSpaces2Et()  { elTabs.OnConvSpaces2Et(); }
void FctToggleRemember() { elTabs.OnToggleRemember(funcItem[IdxToggleRemember]._cmdID); }

void FctEditSettings()   { elTabs.OnEditSettings(); }
void FctResetSettings()  { elTabs.OnReset(); }
void FctShowHelp()       { elTabs.ShowHelp(); }
void FctShowAbout()      { ShowAboutDialog(NppPlugin::hModule, MAKEINTRESOURCE(IDD_ABOUTDLG), NppPlugin::nppData._nppHandle); }

extern "C" __declspec(dllexport) void setInfo(NppData notepadPlusData)
{
  //printf(__FUNCDNAME__": %p %p %p\n", NppPlugin._nppHandle, NppPlugin._scintillaMainHandle, NppPlugin._scintillaSecondHandle);
  NppPlugin::nppData = notepadPlusData;
  NppPlugin::SetDirect();
  elTabs.GetIniFilePath();
  elTabs.LoadIni();
}

extern "C" __declspec(dllexport) const TCHAR* getName()
{
  //printf(__FUNCDNAME__"\n");
  return NppPlugin::NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) FuncItem* getFuncsArray(int *nbF)
{
  //printf(__FUNCDNAME__"\n");
  *nbF = NB_FUNCS;
  return funcItem;
}

#ifdef USE_CONSOLE
struct S1 { unsigned int type; const char* name; };
#define COD(n,c) if(code==c) return {n,#c};
S1 CodeName(unsigned int code)
{
  COD(1,NPPN_CANCELSHUTDOWN)
  COD(1,NPPN_DARKMODECHANGED)
  COD(1,NPPN_BEFORESHUTDOWN)
  COD(1,NPPN_SHUTDOWN)
  COD(1,NPPN_READY)
  COD(1,NPPN_TBMODIFICATION)

  COD(2,NPPN_FILEBEFORECLOSE)
  COD(2,NPPN_FILEOPENED)
  COD(2,NPPN_FILECLOSED)
  COD(2,NPPN_FILEBEFOREOPEN)
  COD(2,NPPN_FILEBEFORESAVE)
  COD(2,NPPN_FILESAVED)
  COD(2,NPPN_BUFFERACTIVATED)
  COD(2,NPPN_LANGCHANGED)
  COD(2,NPPN_WORDSTYLESUPDATED)
  COD(2,NPPN_FILEBEFORELOAD)
  COD(2,NPPN_FILELOADFAILED)
  COD(2,NPPN_FILEBEFORERENAME)
  COD(2,NPPN_FILERENAMECANCEL)
  COD(2,NPPN_FILERENAMED)
  COD(2,NPPN_FILEBEFOREDELETE)
  COD(2,NPPN_FILEDELETED)
  COD(2,NPPN_FILEDELETEFAILED)

  COD(3,NPPN_CMDLINEPLUGINMSG)

  COD(4,NPPN_SHORTCUTREMAPPED)
  COD(5,NPPN_READONLYCHANGED)
  COD(6,NPPN_DOCORDERCHANGED)
  COD(7,NPPN_SNAPSHOTDIRTYFILELOADED)

  COD(8,SCN_PAINTED)
  COD(8,SCN_UPDATEUI)
  COD(8,SCN_MODIFIED)
  COD(8,SCN_FOCUSIN)
  COD(8,SCN_FOCUSOUT)
  COD(8,SCN_ZOOM)

  static char buf[128];
  sprintf(buf, "%u", code);
  return {0,buf};
}

void ShowNotifMsg(SCNotification *notify, bool showUnk=false)
{
  static Sci_NotifyHeader last_nmhdr={nullptr,0,0};
  if(memcmp(&last_nmhdr,&notify->nmhdr,sizeof(Sci_NotifyHeader))==0) return;
  S1 s1=CodeName(notify->nmhdr.code);
  switch(s1.type)
  {
  case 0: if(showUnk) {printf("Notify: 0x%08X\n", notify->nmhdr.code); break;} return;
  case 1: printf("Notify: %-24s %s\n", s1.name, NppPlugin::IsWho((HWND)notify->nmhdr.hwndFrom)); break;
  case 2: printf("Notify: %-24s %s BufID:%08IX\n", s1.name, NppPlugin::IsWho((HWND)notify->nmhdr.hwndFrom), notify->nmhdr.idFrom); break;
  case 3: printf("Notify: %-24s %s plugMsg:%08IX\n", s1.name, NppPlugin::IsWho((HWND)notify->nmhdr.hwndFrom), notify->nmhdr.idFrom); break;
  case 4: printf("Notify: %-24s CmdID:%08IX\n", s1.name, notify->nmhdr.idFrom); break;
  case 5: printf("Notify: %-24s BufID:%08p\n", s1.name, notify->nmhdr.hwndFrom); break;
  case 6: printf("Notify: %-24s BufID:%08IX NewIdx:%p\n", s1.name, notify->nmhdr.idFrom, notify->nmhdr.hwndFrom); break;
  case 7: printf("Notify: %-24s BufID:%08IX\n", s1.name, notify->nmhdr.idFrom); break;
  case 8: printf("Notify: %-24s %s BufID:%08IX\n", s1.name, NppPlugin::IsWho((HWND)notify->nmhdr.hwndFrom), notify->nmhdr.idFrom); break;
  }
  last_nmhdr=notify->nmhdr;
}
#endif

// BUG: open test1.txt, ctrl-A, ctrl-C, ctrl-V 1st time OK, 2nd time ERROR (bad TABS computing) BUT moving inside the file just one line back from the current top line  will recompute the rigth view !!!
// BUG issue is due of OnModify and unique-edit optimization: so it's a bad idea, current version disable this optimization
extern "C" __declspec(dllexport) void beNotified(SCNotification *notify)
{
	//static int numEdits = 0; // if equal to 1 then ed keeps the unique edit data (from SCN_MODIFIED -> SCN_UPDATEUI)
  //static EditData ed;      // keep the unique modification to optimize drawing update
  //static bool isFileEnabled = true;     // is the current forground file enabled ?
  //static TCHAR fg_fname[MAX_PATH] ={0}; // current forground file name
  //static Sci_Position startLine=0, endLine=0;

	// Somehow we are getting (many) notifications from other scintilla handles at times
	if(!NppPlugin::IsInNppData((HWND)notify->nmhdr.hwndFrom)) return;
#ifdef USE_CONSOLE
  ShowNotifMsg(notify);
#endif
  switch (notify->nmhdr.code)
  {
#if 1
    case NPPN_BUFFERACTIVATED:   elTabs.OnNppBufferActivated(notify); return;
    case NPPN_WORDSTYLESUPDATED: elTabs.OnNppWordStyleUpdated(notify); return;
    case SCN_MODIFIED:           elTabs.OnScnModified(notify); return;
    case SCN_UPDATEUI:           elTabs.OnScnUpdateUI(notify); return;
    case SCN_ZOOM:               elTabs.OnScnZoom(notify); return;
    case SCN_PAINTED:            elTabs.OnScnModified(notify); return;
    case NPPN_SHUTDOWN:          elTabs.SaveIni(); return;
    case NPPN_FILESAVED:         elTabs.OnFileSaved(notify); return;
    case NPPN_FILECLOSED:        elTabs.OnFileClosed(notify); return;
    case NPPN_FILEBEFORECLOSE:   elTabs.OnFileBeforeClosed(notify); return;
      
#else
#if 0
    // use periodic SCN_PAINTED to scan any modification of current selection
    case SCN_PAINTED:
    {
      Sci_Position _startLine=elTabs.LineFromPosition(elTabs.GetSelectionStart());
      Sci_Position _endLine=elTabs.LineFromPosition(elTabs.GetSelectionEnd());
      if(_startLine!=startLine||_endLine!=endLine)
      {
        startLine=_startLine; endLine=_endLine;
        printf("New lines: : %Iu .. %Iu\n", startLine, endLine);
      }
      return;
    }
#endif
    case NPPN_WORDSTYLESUPDATED:
      NppPlugin::IsSecView();
      if(!elTabs.enabled||!isFileEnabled) return;
      elTabs.doRecompute=true; elTabs.ComputeView(true);
      elTabs.doRecompute=false; elTabs.ComputeView(false);
      return;
    case SCN_FOCUSIN:
      return;
    // the states of all menu items are reset to 0 (MF_ENABLED) before SCN_UPDATEUI
		case SCN_UPDATEUI:
    {
      //UINT state=GetMenuState(GetMenu(nppData._nppHandle), funcItem[IdxConvEt2Spaces]._cmdID, MF_BYCOMMAND);
      //printf("SCN_UPDATEUI: Menu state: %08X\n", state);
      EnableMenuItem(GetMenu(NppPlugin::nppData._nppHandle), funcItem[IdxConvEt2Spaces]._cmdID, ((isFileEnabled&&elTabs.enabled) ? MF_ENABLED : MF_GRAYED));
      if(!elTabs.enabled || !isFileEnabled) return;
      //if(notify->updated & SC_UPDATE_V_SCROLL||numEdits>0) {}
      elTabs.SwitchToScintilla();
      elTabs.ComputeView();
      return;
    }
		case SCN_MODIFIED:
    {
			if (!elTabs.enabled || !isFileEnabled) return;
			// Make sure we only look at inserts and deletes
			bool isInsert = (notify->modificationType & SC_MOD_INSERTTEXT) != 0;
			bool isDelete = (notify->modificationType & SC_MOD_DELETETEXT) != 0;
			if(isInsert || isDelete)
      {
        elTabs.doRecompute=true;
			}
      return;
		}
		case SCN_ZOOM:
    {
			if (!elTabs.enabled || !isFileEnabled) return;
			// Redo the current view since the tab sizes have changed
      elTabs.doRecompute=true;
      elTabs.ComputeView();
			return;
		}
		case NPPN_READY:
			CheckMenuItem(GetMenu(NppPlugin::nppData._nppHandle), funcItem[IdxToggleEnabled]._cmdID, elTabs.enabled ? MF_CHECKED : MF_UNCHECKED);
			//ElasticTabstopsOnReady(NppPlugin::nppData._scintillaMainHandle);
			//ElasticTabstopsOnReady(NppPlugin::nppData._scintillaSecondHandle);
      //EnableMenuItem(GetMenu(NppPlugin::nppData._nppHandle), funcItem[IdxConvEt2Spaces]._cmdID, ((isFileEnabled&&elTabs.enabled) ? MF_ENABLED : MF_GRAYED));
      //elTabs.SwitchToScintilla();
			//if(elTabs.enabled) elTabs.ComputeCurrentView();
			return;
		case NPPN_SHUTDOWN:
      elTabs.Save();
			return;
    //case NPPN_FILECLOSED:
    //{
    //  UINT state=GetMenuState(GetMenu(nppData._nppHandle), funcItem[2]._cmdID, MF_BYCOMMAND);
    //  printf("NPPN_FILECLOSED Menu state: %08X\n", state);
    //  return;
    //}
    // When a file is closed and another is automatically put to foreground this notification sequence takes place:
    // NPPN_FILEBEFORECLOSE(oldBufID) -> NPPN_BUFFERACTIVATED(newBufID) -> NPPN_FILECLOSED(oldBufID) -> SCN_UPDATEUI
    // To update the menu state fonction of the new forground file, one can try to do it in the NPPN_BUFFERACTIVATED notification
    // but it is useless because NPP will reset the states of all menu items to 0 (MF_ENABLED) before SCN_UPDATEUI notification
    case NPPN_BUFFERACTIVATED:
    {
      Configuration::SendMessageNPP(NPPM_GETFULLPATHFROMBUFFERID, notify->nmhdr.idFrom, (LPARAM)fg_fname);
      isFileEnabled = elTabs.shouldProcessFile(fg_fname); //shouldProcessCurrentFile uses sometimes the bad file, so don't use it !!!
      //printf("Forground file: \"%S\" %s\n", fg_fname, (isFileEnabled?"TRUE":"FALSE"));
      // BUG: when closing an enabled file and then an existing non-enabled file comes to forground the menu will be/still active while
      // the next line EnableMenuItem is executed !!! No logical explanation, maybe NPP modify again the menu when precedent file is closed ?!?
      // After many tests: the states of all menu items are reset to 0 (MF_ENABLED) before SCN_UPDATEUI so the plugin need to update menustate in SCN_UPDATEUI notify
      //EnableMenuItem(GetMenu(nppData._nppHandle), funcItem[2]._cmdID, ((isFileEnabled&&config.enabled) ? MF_ENABLED : MF_GRAYED));
      //UINT state=GetMenuState(GetMenu(nppData._nppHandle), funcItem[2]._cmdID, MF_BYCOMMAND);
      //printf("NPPN_BUFFERACTIVATED Menu state: %08X\n", state);
      if(!elTabs.enabled || !isFileEnabled) return;
      elTabs.SwitchToScintilla();
      elTabs.doRecompute=true;
      //elTabs.ComputeCurrentView();
      //numEdits = 0;
      return;
    }
		case NPPN_FILESAVED:
    {
      if(!elTabs.IsIniFilePath(fg_fname)) return;
      elTabs.Load();
      // Immediately apply the new config to UI and the config file itself
      CheckMenuItem(GetMenu(NppPlugin::nppData._nppHandle), funcItem[IdxToggleEnabled]._cmdID, (elTabs.enabled ? MF_CHECKED : MF_UNCHECKED));
      isFileEnabled = elTabs.shouldProcessFile(fg_fname);
      EnableMenuItem(GetMenu(NppPlugin::nppData._nppHandle), funcItem[IdxConvEt2Spaces]._cmdID, ((isFileEnabled&&elTabs.enabled) ? MF_ENABLED : MF_GRAYED));
      //elTabs.SwitchToScintilla();
      elTabs.doRecompute=true;
      elTabs.ComputeView();
      return;
		}
#endif
    default: return;
	}
	return;
}

extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam) { return TRUE; }

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode() { return TRUE; }
#endif //UNICODE

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  reasonForCall, LPVOID lpReserved)
{
  switch(reasonForCall)
  {
  case DLL_PROCESS_ATTACH:
#ifdef USE_CONSOLE
    { static CConsole Cons; }
#endif
    NppPlugin::hModule=(HMODULE)hModule;
    break;
  case DLL_PROCESS_DETACH:
    break;
  case DLL_THREAD_ATTACH:
    break;
  case DLL_THREAD_DETACH:
    break;
  }
  return TRUE;
}
