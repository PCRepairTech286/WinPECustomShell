#include "FileManagerWindow.h"
#include "WinPEFileManager.h"
#include "StartProcess.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
		MessageBox(hwnd, cannotCloseMsg, szAppTitle, MB_ICONEXCLAMATION + MB_OK);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_7ZIP:
			startup(L"7zFM.exe", L"", currentdir);
			return 0;
		case ID_CMDOPEN:
			startup(L"cmd.exe", L"/k title Command Prompt", systemdir);
			return 0;
		case ID_RESTART:
			if (MessageBox(hwnd, rsConfirmation, szAppTitle, MB_ICONINFORMATION + MB_YESNO) == IDYES)
			{
				DestroyWindow(hWnd);
			}
			return 0;
		case ID_ABOUT:
			MessageBox(hwnd, aboutText2, aboutTitle2, MB_ICONINFORMATION + MB_OK);
			return 0;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

BOOL Initialization(HINSTANCE hInst, SIZE size)
{
	LoadString(hInst, CURRENTDIRECTORY, currentdir, MAX_PATH);
	LoadString(hInst, APPTITLE, szAppTitle, 1000);
	LoadString(hInst, CANNOTCLOSE, cannotCloseMsg, 1000);
	LoadString(hInst, RESTARTCONFIRMATION, rsConfirmation, 1000);
	LoadString(hInst, ABOUTTEXT, aboutText2, 1000);
	LoadString(hInst, ABOUTTITLE, aboutTitle2, 1000);
	GetSystemDirectory(systemdir, MAX_PATH);
	WNDCLASSEX  wndClass;
	LPCWSTR className = TEXT("WindowClass");

	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.cbSize = sizeof(wndClass);
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = className;
	wndClass.hInstance = hInst;
	wndClass.hbrBackground = CreatePatternBrush(LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACKGROUND)));
	wndClass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_FILEMANAGER));
	wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
	wndClass.style = CS_DBLCLKS;

	if (RegisterClassEx(&wndClass) == NULL) return FALSE;

	hWnd = CreateWindow(
		className,
		szAppTitle,
		WS_OVERLAPPEDWINDOW,
		100, 100,
		size.cx, size.cy,
		NULL,
		NULL,
		hInst,
		NULL);

	if (hWnd == NULL) return FALSE;

	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);

	return TRUE;
}

WPARAM MsgCommunicationLoop(HACCEL hAccelerators)
{
	MSG msg;
	while (GetMessage(&msg, hWnd, 0, 0) > 0)
	{
		TranslateAccelerator(hWnd, hAccelerators, &msg);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}