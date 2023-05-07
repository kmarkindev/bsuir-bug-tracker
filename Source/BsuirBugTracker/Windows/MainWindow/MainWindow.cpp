#include "MainWindow.h"

#include "Windows.h"
#include "BsuirBugTracker/Utils/GuidGenerator.h"

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

	// Test data

	static Bug TestBug { GenerateGuid() };
	TestBug.SetName(BSUIR_TEXT("Тестовое названиеgf s fgdsgfds sgdf gsrd sgrd rs srg rgs srg srg srg srg srg srg sr gsr gsrg sr g sgr srg sgr srg srg sgr srg srg srg  бага"));
	TestBug.SetUpdatedAt({ std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()) });

	static Bug TestBug2 { GenerateGuid() };
	TestBug2.SetName(BSUIR_TEXT("Еще один баг лол"));
	auto time = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
	time -= std::chrono::seconds { 30 };
	TestBug2.SetUpdatedAt({ time });

	// Initialize Bug View Panel

	BugViewPanel.Initialize(GetHInstance(), WindowInitializeParams {
			.X = 720,
			.Y = 20,
			.Width = 450,
			.Height = 600,
			.ParentWindow = this,
	});

	// Initialize Bugs List View

	BugsListView.Initialize(GetHInstance(), WindowInitializeParams{
		.X = 200,
		.Y = 20,
		.Width = 500,
		.Height = 600,
		.ParentWindow = this,
	});

	BugsListView.GetOnBugSelectionChange().AddCallback([this](int Index, Bug* Ptr){
		BugViewPanel.SetBug(Ptr);
	});

	// Test data

	BugsListView.AddItem(0, &TestBug);
	BugsListView.AddItem(0, &TestBug2);
}

void MainWindow::EndLifetime()
{
	BaseWindow::EndLifetime();

	BugsListView.Destroy();
	BugViewPanel.Destroy();
}

LRESULT MainWindow::WindowProcedure(HWND InHwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch(UMsg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return Window::WindowProcedure(InHwnd, UMsg, WParam, LParam);
}

DWORD MainWindow::GetDefaultStyles() const
{
	return WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
}
