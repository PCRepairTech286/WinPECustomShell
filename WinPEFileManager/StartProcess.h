#include <Windows.h>

VOID startup(LPCWSTR lpApplicationName, LPCWSTR lpCommandLine, LPCWSTR lpCurrentDirectory)
{
	ShellExecute(NULL, L"open", lpApplicationName, lpCommandLine, lpCurrentDirectory, SW_SHOWDEFAULT);
}