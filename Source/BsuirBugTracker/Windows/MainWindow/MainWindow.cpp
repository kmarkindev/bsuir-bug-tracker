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
		default:
		{
			return WindowProcedureHelper(Hwnd, UMsg, WParam, LParam);
		}
	}
}

const wchar_t* MainWindow::GetWindowClassName() const
{
	return L"MainWindow Class";
}

void MainWindow::RegisterWindowClass(HINSTANCE HInstance)
{
	RegisterWindowClassHelper(HInstance, MainWindow::WindowProc);
}
