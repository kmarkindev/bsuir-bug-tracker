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

	TestButton.SetOnClickCallback([this](Button& btn){
		MessageBox(btn.GetHwnd(), L"Test button click", L"Button click", MB_OK);
	});

	TestListView.Initialize(GetHInstance(), WindowInitializeParams{
		.X = 300,
		.Y = 20,
		.Width = 400,
		.Height = 500,
		.ParentWindow = this,
	});

	TestListView.AddColumn(1, L"Col 1", 100);
	TestListView.AddColumn(2, L"Col 2", 100);
	TestListView.AddColumn(3, L"Col 3", 100);

	TestListView.RemoveColumn(0);

	TestText.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = BSUIR_TEXT("Пробный text! @# !@ !%@#^^ qwe123123123"),
		.X = 20,
		.Y = 200,
		.Width = 250,
		.Height = 150,
		.ParentWindow = this,
	});


}

void MainWindow::EndLifetime()
{
	BaseWindow::EndLifetime();

	TestButton.Destroy();
	TestListView.Destroy();
	TestText.Destroy();
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

DWORD MainWindow::GetDefaultStyles() const
{
	return WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
}
