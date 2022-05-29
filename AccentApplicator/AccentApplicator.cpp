// AccentApplicator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "AccentApplicator.h"
#include "AccentColorHelper.h"
#include "AccentControls.h"

typedef void(*BitmapHandler)(int* r, int* g, int* b, int* a);

typedef struct {
	int r;
	int g;
	int b;
} rgb;

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

int RecolorizeBitmap(HBITMAP hbm, BitmapHandler handler)
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

			handler(&r, &g, &b, &a);

			pPixel[2] = r;
			pPixel[1] = g;
			pPixel[0] = b;
			pPixel[3] = a;

			#pragma region AccentAuto

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

			#pragma endregion

            //pPixel[3] = 1;
            pPixel += 4;
        }
    }
    SetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);
    delete[] pBits;
    return TRUE;
}

int ModifyStyle(LPCWSTR pszClassList, int iPartId, int iStateId, int iPropId, BitmapHandler handler)
{
    HBITMAP hBitmap;

    HTHEME hTheme = OpenThemeData(GetForegroundWindow(), pszClassList);
    GetThemeBitmap(hTheme, iPartId, iStateId, iPropId, GBF_DIRECT, &hBitmap);
    CloseThemeData(hTheme);

    return RecolorizeBitmap(hBitmap, handler);
}

void ModifyStyles()
{
	int i;
	ModifyStyle(VSCLASS_BUTTON, BP_PUSHBUTTON, 0, TMT_DIBDATA, Accent_Button);
	ModifyStyle(VSCLASS_BUTTON, BP_CHECKBOX, 0, 3, Accent_CheckBox);
	for (i = CP_DROPDOWNBUTTON; i <= CP_DROPDOWNBUTTONLEFT; i++)
	{
		ModifyStyle(VSCLASS_COMBOBOX, i, 0, TMT_DIBDATA, Accent_Button);
	}
	for (i = EP_EDITBORDER_NOSCROLL; i <= EP_EDITBORDER_HVSCROLL; i++)
	{
		ModifyStyle(VSCLASS_EDIT, i, 0, TMT_DIBDATA, Accent_Button);
	}
	for (i = TABP_TABITEM; i <= TABP_TOPTABITEMBOTHEDGE; i++)
	{
		ModifyStyle(VSCLASS_TAB, i, 0, TMT_DIBDATA, Accent_Tab);
	}
	for (i = TKP_THUMB; i <= TKP_THUMBRIGHT; i++)
	{
		ModifyStyle(VSCLASS_TRACKBAR, i, 0, 2, Accent_Trackbar);
		ModifyStyle(VSCLASS_TRACKBAR, i, 0, 3, Accent_Trackbar);
	}
	for (i = LBCP_BORDER_HSCROLL; i <= LBCP_ITEM; i++)
	{
		ModifyStyle(VSCLASS_LISTBOX, i, 0, TMT_DIBDATA, Accent_Button);
	}
	for (i = SPNP_UP; i <= SPNP_DOWNHORZ; i++)
	{
		ModifyStyle(VSCLASS_SPIN, i, 0, TMT_DIBDATA, Accent_Spin);
	}
	/*
	ModifyStyle(VSCLASS_BUTTON, BP_RADIOBUTTON, 0, 3);
    ModifyStyle(VSCLASS_HEADERSTYLE, HP_HEADERITEM, 0, 2);
    for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
    {
        ModifyStyle(VSCLASS_TOOLBAR, i, 0, TMT_DIBDATA);
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
	*/
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
