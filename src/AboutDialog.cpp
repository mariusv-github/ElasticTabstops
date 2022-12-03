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

#include "Version.h"
#include "ElasticTabstops.h"
#include "Hyperlinks.h"

#ifdef _WIN64
#define BITNESS _T("(64 bit)")
#else
#define BITNESS _T("(32 bit)")
#endif

#ifdef UNICODE
#define CODETYPE _T("Unicode")
#else
#define CODETYPE _T("ANSI")
#endif //UNICODE


INT_PTR CALLBACK abtDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		case WM_INITDIALOG:
    {
      ConvertStaticToHyperlink(hwndDlg, IDC_GITHUB);
      ConvertStaticToHyperlink(hwndDlg, IDC_README);
      SetDlgItemText(hwndDlg, IDC_GROUPETXT, _T("Elastic Tabstops v") VERSION_TEXT _T(" ") VERSION_STAGE _T(" ") BITNESS _T(" ") CODETYPE);
      SetDlgItemText(hwndDlg, IDC_VERSION, _T("Version ") VERSION_TEXT _T(" from ") __DATE__ _T(", Scintilla 2GB+ compatible"));
      return true;
    }
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDOK:
					DestroyWindow(hwndDlg);
					return true;
				case IDC_GITHUB:
					ShellExecute(hwndDlg, TEXT("open"), TEXT("https://github.com/mariusv-github/ElasticTabstops/"), NULL, NULL, SW_SHOWNORMAL);
					return true;
			}
		case WM_DESTROY:
			DestroyWindow(hwndDlg);
			return true;
		}
	return false;
}

void ShowAboutDialog(HINSTANCE hInstance, LPCTSTR lpTemplateName, HWND hWndParent)
{
	HWND hSelf = CreateDialogParam(hInstance, lpTemplateName, hWndParent, abtDlgProc, NULL);
	// Go to center
	RECT rc;
	GetClientRect(hWndParent, &rc);
	POINT center;
	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;
	center.x = rc.left + w / 2;
	center.y = rc.top + h / 2;
	ClientToScreen(hWndParent, &center);

	RECT dlgRect;
	GetClientRect(hSelf, &dlgRect);
	int x = center.x - (dlgRect.right - dlgRect.left) / 2;
	int y = center.y - (dlgRect.bottom - dlgRect.top) / 2;

	SetWindowPos(hSelf, HWND_TOP, x, y, (dlgRect.right - dlgRect.left), (dlgRect.bottom - dlgRect.top), SWP_SHOWWINDOW);
  ::CloseHandle(hSelf);
}
