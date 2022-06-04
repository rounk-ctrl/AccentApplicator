#include "TrayIcon.h"
//#include "AccentApplicator.h"
#include "resource.h"

bool InitializeTrayIcon(HINSTANCE hInstance, int nCmdShow) {
	return InitInstance(hInstance, nCmdShow);
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
		//ApplyAccentColorization();
		break;
	}
	default:
		if (message == s_uTaskbarRestart) {
			TrayIcon(hWnd, hInst);
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
