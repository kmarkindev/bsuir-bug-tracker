#include "MainWindow.h"

#include <fstream>
#include "Windows.h"
#include "BsuirBugTracker/Utils/GuidGenerator.h"
#include "BsuirBugTracker/Storage/StorageHelpers.h"

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

	LoadStorage();

	// Initialize Create Bug Button
	CreateBugButton.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = BSUIR_TEXT("Новый баг"),
		.X = 5,
		.Y = 570,
		.Width = 290,
		.Height = 50,
		.ParentWindow = this,
	});

	CreateBugButton.GetOnButtonClicked().AddCallback([this](Button&){
		Bug& CreatedBug = Storage.AddBug(Bug { GenerateGuid() });

		BugViewPanel.SetBug(&CreatedBug);
	});

	// Initialize Bug View Panel

	BugViewPanel.Initialize(GetHInstance(), WindowInitializeParams {
		.X = 820,
		.Y = 20,
		.Width = 450,
		.Height = 600,
		.ParentWindow = this,
	});

	// Initialize Bugs List View

	BugsListView.Initialize(GetHInstance(), WindowInitializeParams{
		.X = 300,
		.Y = 20,
		.Width = 500,
		.Height = 600,
		.ParentWindow = this,
	});

	BugsListView.GetOnBugSelectionChange().AddCallback([this](int Index, Bug* Ptr){
		BugViewPanel.SetBug(Ptr);
	});
}

void MainWindow::EndLifetime()
{
	BaseWindow::EndLifetime();

	BugsListView.Destroy();
	BugViewPanel.Destroy();
	CreateBugButton.Destroy();

	SaveStorage();
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

void MainWindow::LoadStorage()
{
	bool Error = false;
	bool AssetExists = DoesAssetExist(L"Data", Error);

	if(Error)
	{
		assert(false);
		return;
	}

	if(!AssetExists)
		return;

	String StoragePath = GetAssetPath(L"Data", Error);

	if(Error)
	{
		assert(false);
		return;
	}

	std::ifstream IfStream(StoragePath.c_str());
	Storage.DeSerialize(IfStream);
}

void MainWindow::SaveStorage()
{
	bool Error = false;
	String StoragePath = GetAssetPath(L"Data", Error);

	if(Error)
	{
		assert(false);
		return;
	}

	std::ofstream OfStream(StoragePath.c_str(), std::ios::trunc);
	Storage.Serialize(OfStream);
}
