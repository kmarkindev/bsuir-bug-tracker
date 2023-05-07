#include <Windows.h>
#include <cassert>
#include <CommCtrl.h>
#include "BsuirBugTracker/Windows/MainWindow/MainWindow.h"

void RunMainLoop()
{
	MSG Message {};
	BOOL LastGetMessageReturn {};
	while((LastGetMessageReturn = GetMessage(&Message, nullptr, 0, 0)) != 0)
	{
		assert(LastGetMessageReturn != -1);

		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
}

void RegisterICC()
{
	INITCOMMONCONTROLSEX InitCommonControlsStruct = {
			.dwSize = sizeof(InitCommonControlsStruct),
			.dwICC = ICC_LISTVIEW_CLASSES | ICC_DATE_CLASSES
	};
	InitCommonControlsEx(&InitCommonControlsStruct);
}

int WINAPI wWinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, PWSTR PCmdLine, int NCmdShow)
{
	RegisterICC();

	LoadLibrary(TEXT("Msftedit.dll"));

	MainWindow MainWindow {};
	MainWindow.Initialize(HInstance, WindowInitializeParams{
		.Name = BSUIR_TEXT("Баг-трекер"),
		.Width = 1300,
		.Height = 670
	});

	RunMainLoop();

	MainWindow.Destroy();

	return 0;
}