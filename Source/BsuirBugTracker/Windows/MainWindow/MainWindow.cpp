#include "MainWindow.h"

#include <Windows.h>

LRESULT MainWindow::WindowProc(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch(UMsg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return WindowProcedureBase(Hwnd, UMsg, WParam, LParam);
}

const wchar_t* MainWindow::GetWindowClassName() const
{
	return L"MainWindow Class";
}

void MainWindow::RegisterWindowClass()
{
	RegisterWindowClassHelper(MainWindow::WindowProc);
}

void MainWindow::BeginWindowLifetime()
{
	BaseWindow::BeginWindowLifetime();

	HWND hwndButton = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed
		L"OK",      // Button text
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
		10,         // x position
		10,         // y position
		100,        // Button width
		100,        // Button height
		GetHwnd(),     // Parent window
		nullptr,
		GetHInstance(),
		nullptr
	);
}

void MainWindow::EndWindowLifetime()
{
	BaseWindow::EndWindowLifetime();


}
