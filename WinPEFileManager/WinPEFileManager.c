#include "WinPEFileManager.h"
#include "FileManagerWindow.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR CommandLine, int ShowCmd) {
	SIZE sSize;
	sSize.cx = 1000; sSize.cy = 600;
	if (!Initialization(hInst, sSize))
	{
		MessageBox(NULL, TEXT("Function cWindow.Initialization failure!"), TEXT("Error"), MB_OK | MB_ICONERROR);
	}

	HACCEL hAccelerators = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	if (!hAccelerators)
	{
		MessageBox(NULL, TEXT("Cannot load accelerators!"), TEXT("Error"), MB_OK | MB_ICONERROR);
	}

	return MsgCommunicationLoop(hAccelerators);
}