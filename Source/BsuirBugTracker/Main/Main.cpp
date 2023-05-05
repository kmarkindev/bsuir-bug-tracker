#include <Windows.h>
#include <cassert>
#include <BsuirBugTracker/Windows/MainWindow/MainWindow.h>

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

int WINAPI wWinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, PWSTR PCmdLine, int NCmdShow)
{
	MainWindow MainWindow {};
	MainWindow.InitializeWindowInstance(HInstance, WindowInitializeParams {
		.Width = 800,
		.Height = 600
	});

	RunMainLoop();

	MainWindow.DestroyWindowInstance();

	return 0;
}