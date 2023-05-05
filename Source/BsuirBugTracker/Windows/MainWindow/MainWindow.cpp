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

	TestButton.InitializeButtonInstance(*this, ButtonInitializeParams {
		.ButtonText = L"My Test Button"
	});

	TestButton.SetOnClickCallback([](Button&){
		MessageBox(nullptr, L"Test text after button click", L"Test caption", MB_OK);
	});
}

void MainWindow::EndWindowLifetime()
{
	BaseWindow::EndWindowLifetime();


}
