#include "AccentApplicator.h"

HANDLE hHandle;

void ApplyAccentColorization() {
	UpdateAccentColors();
	ModifySysColors();
	ModifyStyles();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
	hHandle = CreateMutex(NULL, TRUE, L"ACCENTAPPLICATOR");
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		// Program already running somewhere
		return 1;
	}

	ApplyAccentColorization();

	/*

	// Window initialization
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ASDF, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitializeTrayIcon(nCmdShow))
	{
		return 1;
	}

	MSG msg;
	while (true) {
		GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ReleaseMutex(hHandle);
	CloseHandle(hHandle);

	return (int)msg.wParam;

	*/
	return 0;
}