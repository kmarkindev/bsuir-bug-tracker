#include <Windows.h>

#include "BsuirBugTracker/Types/Types.h"
#include "BsuirBugTracker/Storage/StorageHelpers.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	bool error = false;
	String path = GetAssetPath(BSUIR_TEXT("qwe"), error);

	return 7788;
}