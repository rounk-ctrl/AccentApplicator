// AccentApplicator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "AccentApplicator.h"
#include "AccentColorHelper.h"

#pragma region Pixel Color

inline int PixClr(int val)
{
    return val & 0xFFFFFF;
}

inline int PixR(BYTE* pPixel)
{
    return PixClr(pPixel[2]);
}
inline int PixG(BYTE* pPixel)
{
    return PixClr(pPixel[1]);
}
inline int PixB(BYTE* pPixel)
{
    return PixClr(pPixel[0]);
}
inline int PixA(BYTE* pPixel)
{
    return PixClr(pPixel[3]);
}

#pragma endregion

// PURPOSE: Changes pixels of a BYTE to specified COLORREF.
// 
// pPixel - the pointer to the BYTE* which has the bitmap.
// color - COLORREF containing the color you want the bitmap to have.
//
void AccentColorize(BYTE* pPixel, COLORREF color)
{
	pPixel[2] = GetRValue(color);
	pPixel[1] = GetGValue(color);
	pPixel[0] = GetBValue(color);
}

int RecolorizeBitmap(HBITMAP hbm)
{
    BITMAP bm;
    GetObject(hbm, sizeof(bm), &bm);

    if (!hbm || bm.bmBitsPixel != 32)
    {
        return FALSE;
    }

    BYTE* pBits = new BYTE[bm.bmWidth * bm.bmHeight * 4];
    GetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);

    for (int y = 0; y < bm.bmHeight; y++)
    {
        BYTE* pPixel = (BYTE*)pBits + bm.bmWidth * 4 * y;

        for (int x = 0; x < bm.bmWidth; x++)
        {
            int r = PixR(pPixel); // [2]
            int g = PixG(pPixel); // [1]
            int b = PixB(pPixel); // [0]
            int a = PixA(pPixel); // [3]

            if ((r == 0 && g == 120 && b == 215) || (r == 0 && g == 84 && b == 153)|| /*Main Blue Color for Buttons, Comboboxes, etc*/
				(r == 35 && g == 130 && b == 217)||
				(r == 25 && g == 96 && b == 159) ||
				(r == 36 && g == 131 && b == 218)||
				(r == 27 && g == 96 && b == 160) ||
				(r == 51 && g == 109 && b == 167)||
				(r == 6 && g == 123 && b == 216)||
				(r == 5 && g == 123 && b == 216)||
				(r == 43 && g == 143 && b == 222)||
				(r == 41 && g == 142 && b == 221)||
				(r == 0 && g == 122 && b == 217))
            {
				AccentColorize(pPixel, accent);
            }
            else if (
				(r == 83 && g == 150 && b == 223) ||
				(r == 119 && g == 169 && b == 228)||
				(r == 64 && g == 118 && b == 173) ||
				(r == 93 && g == 138 && b == 185) ||
				(r == 84 && g == 151 && b == 223) ||
				(r == 65 && g == 119 && b == 173) ||
				(r == 51 && g == 147 && b == 223) ||
				(r == 66 && g == 142 && b == 221))
            {
				AccentColorize(pPixel, accentLight1);
            }
            else if (
				(r == 204 && g == 228 && b == 247)|| /*Hovered Button*/
				(r == 134 && g == 178 && b == 230)||
				(r == 106 && g == 148 && b == 191)||
				(r == 150 && g == 182 && b == 215)||
				(r == 178 && g == 206 && b == 231)||
				(r == 196 && g == 221 && b == 242)||
				(r == 140 && g == 174 && b == 209)||
				(r == 186 && g == 213 && b == 236)||
				(r == 146 && g == 179 && b == 213)||
				(r == 176 && g == 205 && b == 230))
            {
				AccentColorize(pPixel, accentLight2);
            }
            else if (
				(r == 229 && g == 241 && b == 251) ||											/*Hovered Button*/
				(r == 216 && g == 234 && b == 249) ||											/*Tab*/
				(r == 0 && g == 56 && b == 102)	   || (r == 0 && g == 28 && b == 51)     ||		/*Toolbar Item / Item Corner*/
				(r == 0 && g == 27 && b == 50)     || (r == 0 && g == 14 && b == 26)     ||		/*Explorer Item / Inactive Explorer Item Hover*/
				(r == 217 && g == 235 && b == 249) || (r == 188 && g == 220 && b == 244) ||		/*Items View Header*/
				(r == 188 && g == 211 && b == 240) ||
				(r == 223 && g == 233 && b == 248) ||
				(r == 176 && g == 203 && b == 238) ||
				(r == 184 && g == 208 && b == 240)||
				(r == 170 && g == 210 && b == 242)||
				(r == 168 && g == 209 && b == 241)||
				(r == 171 && g == 211 && b == 242)||
				(r == 169 && g == 209 && b == 242)||
				(r == 164 && g == 207 && b == 241)||
				(r == 165 && g == 207 && b == 241))
            {
				AccentColorize(pPixel, accentLight3);
            }
			else if ((r == 0 && g == 60 && b == 107) || (r == 0 && g == 60 && b == 108))
			{
				pPixel[2] = GetRValue(accentDark2);
				pPixel[1] = GetGValue(accentDark2);
				pPixel[0] = GetBValue(accentDark2);
			}
			// spin
			else if (r == 86 && g == 157 && b == 229)
			{
				AccentColorize(pPixel, accentLight1);
			}
            else if (
				(r == 225 && g == 239 && b == 252)||
				(r == 227 && g == 240 && b == 252)||
				(r == 228 && g == 241 && b == 252)||
				(r == 230 && g == 241 && b == 252)||
				(r == 231 && g == 242 && b == 252)||
				(r == 232 && g == 242 && b == 252)||
				(r == 234 && g == 243 && b == 252)||
				(r == 235 && g == 244 && b == 252)||
				(r == 224 && g == 238 && b == 252)||
				(r == 223 && g == 238 && b == 252)||
				(r == 222 && g == 237 && b == 252)||
				(r == 221 && g == 237 && b == 252))
            {
				AccentColorize(pPixel, accentLight3);
            }
            else if (
				(r == 126 && g == 180 && b == 234)||
				(r == 218 && g == 235 && b == 252)||
				(r == 217 && g == 235 && b == 252)||
				(r == 215 && g == 234 && b == 252)||
				(r == 214 && g == 233 && b == 252)||
				(r == 212 && g == 232 && b == 252)||
				(r == 210 && g == 231 && b == 252)||
				(r == 208 && g == 230 && b == 252)||
				(r == 206 && g == 229 && b == 252)||
				(r == 204 && g == 228 && b == 252)||
				(r == 202 && g == 227 && b == 252)||
				(r == 200 && g == 226 && b == 252)||
				(r == 198 && g == 225 && b == 252)||
				(r == 197 && g == 225 && b == 252))
            {
				AccentColorize(pPixel, accentLight2);
            }


			// accent auto
			if (r == GetRValue(oldAccent) && 
				g == GetGValue(oldAccent) && 
				b == GetBValue(oldAccent))
			{
				AccentColorize(pPixel, accent);
			}
			else if (
				r == GetRValue(oldAccentLight1) && 
				g == GetGValue(oldAccentLight1) && 
				b == GetBValue(oldAccentLight1))
			{
				AccentColorize(pPixel, accentLight1);
			}
			else if (
				r == GetRValue(oldAccentLight2) && 
				g == GetGValue(oldAccentLight2) && 
				b == GetBValue(oldAccentLight2))
			{
				AccentColorize(pPixel, accentLight2);
			}
			else if (
				r == GetRValue(oldAccentLight3) &&
				g == GetGValue(oldAccentLight3) && 
				b == GetBValue(oldAccentLight3))
			{
				AccentColorize(pPixel, accentLight3);
			}
			else if (
				r == GetRValue(oldAccentDark1) && 
				g == GetGValue(oldAccentDark1) &&
				b == GetBValue(oldAccentDark1))
			{
				AccentColorize(pPixel, accentDark1);
			}
			else if (
				r == GetRValue(oldAccentDark2) &&
				g == GetGValue(oldAccentDark2) &&
				b == GetBValue(oldAccentDark2))
			{
				AccentColorize(pPixel, accentDark2);
			}
			else if (
				r == GetRValue(oldAccentDark3) &&
				g == GetGValue(oldAccentDark3) &&
				b == GetBValue(oldAccentDark3))
			{
				AccentColorize(pPixel, accentDark3);
			}

            //pPixel[3] = 1;
            pPixel += 4;
        }
    }
    SetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);
    delete[] pBits;
    return TRUE;
}

int ModifyStyle(LPCWSTR pszClassList, int iPartId, int iStateId, int iPropId)
{
    HBITMAP hBitmap;

    HTHEME hTheme = OpenThemeData(GetForegroundWindow(), pszClassList);
    GetThemeBitmap(hTheme, iPartId, iStateId, iPropId, GBF_DIRECT, &hBitmap);
    CloseThemeData(hTheme);

    return RecolorizeBitmap(hBitmap);
}

void ModifyStyles()
{
    int i;
    ModifyStyle(VSCLASS_BUTTON, BP_RADIOBUTTON, 0, 3);
    ModifyStyle(VSCLASS_BUTTON, BP_CHECKBOX, 0, 3);
	ModifyStyle(VSCLASS_BUTTON, BP_PUSHBUTTON, 0, TMT_DIBDATA);
    for (i = CP_DROPDOWNBUTTON; i <= CP_DROPDOWNBUTTONLEFT; i++)
    {
        ModifyStyle(VSCLASS_COMBOBOX, i, 0, TMT_DIBDATA);
    }
    for (i = EP_EDITBORDER_NOSCROLL; i <= EP_EDITBORDER_HVSCROLL; i++)
    {
        ModifyStyle(VSCLASS_EDIT, i, 0, TMT_DIBDATA);
    }
    for (i = TABP_TABITEM; i <= TABP_AEROWIZARDBODY; i++)
    {
        ModifyStyle(VSCLASS_TAB, i, 0, TMT_DIBDATA);
    }
    for (i = TKP_THUMB; i <= TKP_THUMBRIGHT; i++)
    {
		ModifyStyle(VSCLASS_TRACKBAR, i, 0, TMT_DIBDATA);
		ModifyStyle(VSCLASS_TRACKBAR, i, 0, 3);
    }
    ModifyStyle(VSCLASS_HEADERSTYLE, HP_HEADERITEM, 0, 2);
    for (i = LBCP_BORDER_HSCROLL; i <= LBCP_ITEM; i++)
    {
        ModifyStyle(VSCLASS_LISTBOX, i, 0, TMT_DIBDATA);
    }
    for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
    {
        ModifyStyle(VSCLASS_TOOLBAR, i, 0, TMT_DIBDATA);
    }
    for (i = SPNP_UP; i <= SPNP_DOWNHORZ; i++)
    {
        ModifyStyle(VSCLASS_SPIN, i, 0, TMT_DIBDATA);
    }
    ModifyStyle(L"BreadcrumbBar", 1, 0, TMT_DIBDATA);
    for (i = 2; i <= 6; i++)
    {
        ModifyStyle(L"Explorer::TreeView", 1, i, TMT_DIBDATA);
    }
    for (i = 2; i <= 6; i++)
    {
        ModifyStyle(L"Explorer::ListView", 1, i, TMT_DIBDATA);
    }
    ModifyStyle(L"PreviewPane", 1, 1, TMT_DIBDATA); // Windows Vista/7 Explorer Bottom Details Panel

    ModifyStyle(L"CommandModule", 1, 0, TMT_DIBDATA); // Windows 7 Explorer Command Bar
    for (i = 3; i <= 5; i++)
    {
        ModifyStyle(L"CommandModule", i, 0, TMT_DIBDATA);
    }
    ModifyStyle(L"ItemsView::Header", 1, 0, TMT_DIBDATA); // Explorer File Groups Header
    for (i = 1; i <= 2; i++)
    {
        ModifyStyle(L"ItemsView", 3, i, TMT_DIBDATA);
    }
    for (i = 1; i <= 16; i++)
    {
        ModifyStyle(L"ItemsView::ListView", 6, i, TMT_DIBDATA); // Explorer File Selection
    }

    for (i = 1; i <= 4; i++)
    {
        ModifyStyle(L"BB::Toolbar", i, 0, TMT_DIBDATA); // Explorer Breadcrumbs Highlight color
    }
}

const int size = 5;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
	hHandle = CreateMutex(NULL, TRUE, L"ACCENTAPPLICATOR");
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		// Program already running somewhere
		return(1); // Exit program
	}

	UpdateAccentColors();
	SaveCurrentAccentColors();
	ModifyStyles();

	int aElements[size] =
	{
		COLOR_ACTIVECAPTION,
		COLOR_GRADIENTACTIVECAPTION,
		COLOR_HIGHLIGHT,
		COLOR_HOTLIGHT,
		COLOR_MENUHILIGHT
	};
	DWORD aOldColors[size];
	DWORD aNewColors[size];

	for (int i = 0; i < size; i++)
	{
		aOldColors[i] = GetSysColor(aElements[i]);
		aNewColors[i] = RGB(GetRValue(accent), GetGValue(accent), GetBValue(accent));
	}

	SetSysColors(size, aElements, aNewColors);

	// Window initialization
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ASDF, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	MSG msg;
	BOOL bRet;

	// Main message loop:
	while ((bRet = GetMessage(&msg, nullptr, 0, 0)) != 0)
	{
		if (bRet == -1) {  }
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	ReleaseMutex(hHandle); // Explicitly release mutex
	CloseHandle(hHandle); // close handle before terminating
	return (int)msg.wParam;
}
BOOL TrayIcon(HWND hWnd, HINSTANCE hInst)
{
	hMainIcon = LoadIcon(hInst, (LPCTSTR)MAKEINTRESOURCE(IDI_ASDF));
	nidApp.cbSize = sizeof(NOTIFYICONDATA);
	nidApp.hWnd = (HWND)hWnd;
	nidApp.uID = IDI_ASDF;
	nidApp.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nidApp.hIcon = hMainIcon;
	nidApp.uCallbackMessage = WM_USER_SHELLICON;
	nidApp.uVersion = NOTIFYICON_VERSION_4;
	LoadString(hInst, IDS_APP_TITLE, nidApp.szTip, MAX_LOADSTRING);
	Shell_NotifyIcon(NIM_ADD, &nidApp);
	return TRUE;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASDF));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ASDF));

	return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 840, 470, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		return FALSE;
	}
	TrayIcon(hWnd, hInst);
	return TRUE;
}
void ShowContextMenu(HWND hwnd, POINT pt)
{
	HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
	if (hMenu)
	{
		HMENU hSubMenu = GetSubMenu(hMenu, 0);
		if (hSubMenu)
		{
			SetForegroundWindow(hwnd);
		}

		// respect menu drop alignment
		UINT uFlags = TPM_RIGHTBUTTON;
		if (GetSystemMetrics(SM_MENUDROPALIGNMENT) != 0)
			uFlags |= TPM_RIGHTALIGN;
		else
			uFlags |= TPM_LEFTALIGN;

		// Use TPM_RETURNCMD flag let TrackPopupMenuEx function return the menu item identifier of the user's selection in the return value.
		uFlags |= TPM_RETURNCMD;
		if (hSubMenu != 0)
			menuItemId = TrackPopupMenuEx(hSubMenu, uFlags, pt.x, pt.y, hwnd, NULL);
		else
			MessageBox(hwnd, L"Error getting menu.", L"Error", MB_ICONSTOP);

		// Toggle the menu item state.
		if (ID_MENU_EXIT == menuItemId)
		{
			Shell_NotifyIcon(NIM_DELETE, &nidApp);
			PostQuitMessage(0);
		}
		DestroyMenu(hMenu);
	}
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static UINT s_uTaskbarRestart;
	switch (message)
	{
	case WM_CREATE:
	{
		s_uTaskbarRestart = RegisterWindowMessage(TEXT("TaskbarCreated"));
	}
	case WM_USER_SHELLICON:
		// systray msg callback 
		switch (LOWORD(lParam))
		{
		case WM_RBUTTONDOWN:
			GetCursorPos(&ok);
			ShowContextMenu(hWnd, ok);
		}
	break;
	case WM_WININICHANGE:
	{
		UpdateAccentColors();
		if (accent == oldAccent)
		{
			break;
		}
		else
		{
			ModifyStyles();
			SaveCurrentAccentColors();
			int aElements[size] =
			{
				COLOR_ACTIVECAPTION,
				COLOR_GRADIENTACTIVECAPTION,
				COLOR_HIGHLIGHT,
				COLOR_HOTLIGHT,
				COLOR_MENUHILIGHT
			};
			DWORD aNewColors[size];

			for (int i = 0; i < size; i++)
			{
				aNewColors[i] = RGB(GetRValue(accent), GetGValue(accent), GetBValue(accent));
			}

			SetSysColors(size, aElements, aNewColors);
			break;
		}
	}
	default:
		if (message == s_uTaskbarRestart) {
			TrayIcon(hWnd, hInst);
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
