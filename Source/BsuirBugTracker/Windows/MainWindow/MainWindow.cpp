#include "MainWindow.h"

#include <Windows.h>

const wchar_t* MainWindow::GetWindowClassName() const
{
	return L"Main Window Class";
}

void MainWindow::RegisterWindowClass()
{
	RegisterWindowClassHelper();
}

void MainWindow::BeginLifetime()
{
	BaseWindow::BeginLifetime();

	TestButton.Initialize(GetHInstance(), WindowInitializeParams{
		.Name = L"My Test Button",
		.X = 20,
		.Y = 20,
		.Width = 250,
		.Height = 150,
		.ParentWindow = this,
	});

	TestButton.SetOnClickCallback([](Button& btn){
		MessageBox(nullptr, L"Test text after button click", L"Test caption", MB_OK);
	});
}

void MainWindow::EndLifetime()
{
	BaseWindow::EndLifetime();
}

LRESULT MainWindow::WindowProcedure(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch(UMsg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return Window::WindowProcedure(Hwnd, UMsg, WParam, LParam);
}