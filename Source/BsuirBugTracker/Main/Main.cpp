#include <Windows.h>
#include <cassert>
#include <BsuirBugTracker/Windows/MainWindow/MainWindow.h>
#include <CommCtrl.h>

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
			.dwICC = ICC_LISTVIEW_CLASSES
	};
	InitCommonControlsEx(&InitCommonControlsStruct);
}

int WINAPI wWinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, PWSTR PCmdLine, int NCmdShow)
{
	RegisterICC();

	LoadLibrary(TEXT("Msftedit.dll"));

	MainWindow MainWindow {};
	MainWindow.Initialize(HInstance, WindowInitializeParams{
		.Name = L"Main Window",
		.Width = 1200,
		.Height = 800
	});

	RunMainLoop();

	MainWindow.Destroy();

	return 0;
}