#pragma once
#include "framework.h"

#define MAX_LOADSTRING 100
#define WM_USER_SHELLICON WM_USER + 1

HICON hMainIcon;
NOTIFYICONDATA nidApp;
UINT menuItemId;
POINT ok;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

bool InitializeTrayIcon(int nCmdShow);