// AccentApplicator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "AccentApplicator.h"
#include "AccentColorHelper.h"

#define MAX_LOADSTRING 100
#define WM_USER_SHELLICON WM_USER + 1

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HICON hMainIcon;
NOTIFYICONDATA nidApp;
UINT menuItemId;
POINT ok;

// Forward declarations of functions:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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

            if ((r == 0 && g == 120 && b == 215) || (r == 0 && g == 84 && b == 153))
            {
                // Main Blue Color for Buttons, Comboboxes, etc.
                pPixel[2] = GetRValue(accent);
                pPixel[1] = GetGValue(accent);
                pPixel[0] = GetBValue(accent);
            }
            else if (r == 229 && g == 241 && b == 251)
            {
                // Hovered Button (DARK BLUE)
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 204 && g == 228 && b == 247)
            {
                // Hovered Button (DARK BLUE)
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 216 && g == 234 && b == 249)
            {
                // Tab (LIGHT BLUE)
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if ((r == 0 && g == 56 && b == 102) || (r == 0 && g == 28 && b == 51))
            {
                // Toolbar Item / Item Corner (VERY LIGHT BLUE)
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if ((r == 0 && g == 27 && b == 50) || (r == 0 && g == 14 && b == 26))
            {
                // Explorer Item / Inactive Explorer Item Hover (VERY LIGHT BLUE)
				pPixel[2] = GetRValue(accentLight3);
				pPixel[1] = GetGValue(accentLight3);
				pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 217 && g == 235 && b == 249)
            {
                // Items View Header
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 188 && g == 220 && b == 244)
            {
                // Items View Header
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 35 && g == 130 && b == 217)
            {
                pPixel[2] = GetRValue(accent);
                pPixel[1] = GetGValue(accent);
                pPixel[0] = GetBValue(accent);
            }
            else if (r == 83 && g == 150 && b == 223)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 119 && g == 169 && b == 228)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 134 && g == 178 && b == 230)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 188 && g == 211 && b == 240)
            {
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 223 && g == 233 && b == 248)
            {
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 25 && g == 96 && b == 159)
            {
                pPixel[2] = GetRValue(accent);
                pPixel[1] = GetGValue(accent);
                pPixel[0] = GetBValue(accent);
            }
            else if (r == 36 && g == 131 && b == 218)
            {
                pPixel[2] = GetRValue(accent);
                pPixel[1] = GetGValue(accent);
                pPixel[0] = GetBValue(accent);
            }
            else if (r == 64 && g == 118 && b == 173)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 93 && g == 138 && b == 185)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 106 && g == 148 && b == 191)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 150 && g == 182 && b == 215)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 178 && g == 206 && b == 231)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 196 && g == 221 && b == 242)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 84 && g == 151 && b == 223)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 176 && g == 203 && b == 238)
            {
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 27 && g == 96 && b == 160)
            {
                pPixel[2] = GetRValue(accent);
                pPixel[1] = GetGValue(accent);
                pPixel[0] = GetBValue(accent);
            }
            else if (r == 65 && g == 119 && b == 173)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 140 && g == 174 && b == 209)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 51 && g == 147 && b == 223)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 66 && g == 142 && b == 221)
            {
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if (r == 51 && g == 109 && b == 167)
            {
                pPixel[2] = GetRValue(accent);
                pPixel[1] = GetGValue(accent);
                pPixel[0] = GetBValue(accent);
            }
            else if (r == 184 && g == 208 && b == 240)
            {
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 186 && g == 213 && b == 236)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 146 && g == 179 && b == 213)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if (r == 176 && g == 205 && b == 230)
            {
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }

			// accent auto
			if (r == GetRValue(oldAccent) && g == GetGValue(oldAccent) && b == GetBValue(oldAccent))
			{
				pPixel[2] = GetRValue(accent);
				pPixel[1] = GetGValue(accent);
				pPixel[0] = GetBValue(accent);
			}
			if (r == GetRValue(oldAccentLight1) && g == GetGValue(oldAccentLight1) && b == GetBValue(oldAccentLight1))
			{
				pPixel[2] = GetRValue(accentLight1);
				pPixel[1] = GetGValue(accentLight1);
				pPixel[0] = GetBValue(accentLight1);
			}
			if (r == GetRValue(oldAccentLight2) && g == GetGValue(oldAccentLight2) && b == GetBValue(oldAccentLight2))
			{
				pPixel[2] = GetRValue(accentLight2);
				pPixel[1] = GetGValue(accentLight2);
				pPixel[0] = GetBValue(accentLight2);
			}
			if (r == GetRValue(oldAccentLight3) && g == GetGValue(oldAccentLight3) && b == GetBValue(oldAccentLight3))
			{
				pPixel[2] = GetRValue(accentLight3);
				pPixel[1] = GetGValue(accentLight3);
				pPixel[0] = GetBValue(accentLight3);
			}
			if (r == GetRValue(oldAccentDark1) && g == GetGValue(oldAccentDark1) && b == GetBValue(oldAccentDark1))
			{
				pPixel[2] = GetRValue(accentDark1);
				pPixel[1] = GetGValue(accentDark1);
				pPixel[0] = GetBValue(accentDark1);
			}
			if (r == GetRValue(oldAccentDark2) && g == GetGValue(oldAccentDark2) && b == GetBValue(oldAccentDark2))
			{
				pPixel[2] = GetRValue(accentDark2);
				pPixel[1] = GetGValue(accentDark2);
				pPixel[0] = GetBValue(accentDark2);
			}
			if (r == GetRValue(oldAccentDark3) && g == GetGValue(oldAccentDark3) && b == GetBValue(oldAccentDark3))
			{
				pPixel[2] = GetRValue(accentDark3);
				pPixel[1] = GetGValue(accentDark3);
				pPixel[0] = GetBValue(accentDark3);
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
    int i,j;
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
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

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
