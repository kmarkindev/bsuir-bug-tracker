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
		.X = 308,
		.Y = 20,
		.Width = 500,
		.Height = 600,
		.ParentWindow = this,
	});

	BugsListView.GetOnBugSelectionChange().AddCallback([this](int Index, Bug* Ptr){
		BugViewPanel.SetBug(Ptr);
	});

	// Initialize Bugs ListView Filter

	BugsFilterPanel.Initialize(GetHInstance(), WindowInitializeParams{
		.X = 5,
		.Y = 20,
		.Width = 290,
		.Height = 380,
		.ParentWindow = this,
	});

	ImportButton.Initialize(GetHInstance(), WindowInitializeParams{
		.Name = BSUIR_TEXT("Импортировать данные"),
		.X = 5,
		.Y = 430,
		.Width = 290,
		.Height = 50,
		.ParentWindow = this,
	});
	ImportButton.GetOnButtonClicked().AddCallback([this](Button&){
		String Msg = BSUIR_TEXT("Импорт заменит все текущие данные на новые. Нажмите ОК если согласны продолжить");
		String Capt = BSUIR_TEXT("Подтверждение импорта");
		auto MsgResult = MessageBox(GetHwnd(), Msg.c_str(), Capt.c_str(), MB_OKCANCEL);

		if (MsgResult == IDOK)
		{
			wchar_t FilePathBuffer[512] { '\0' };

			OPENFILENAME OpenFileInfo = {};
			OpenFileInfo.lStructSize = sizeof(OPENFILENAME);
			OpenFileInfo.hwndOwner = GetHwnd();
			OpenFileInfo.hInstance = GetHInstance();
			OpenFileInfo.lpstrFilter = L"Bug Tracker Data\0*.BugTrackerData\0\0";
			OpenFileInfo.lpstrFile = FilePathBuffer;
			OpenFileInfo.nMaxFile = sizeof(FilePathBuffer);
			OpenFileInfo.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			BOOL Result = GetOpenFileName(&OpenFileInfo);

			if(Result == FALSE)
				return;

			StringView Path = FilePathBuffer;
			std::ifstream ifstream(Path.data());
			Storage.DeSerialize(ifstream);
		}
	});

	ExportButton.Initialize(GetHInstance(), WindowInitializeParams{
		.Name = BSUIR_TEXT("Экспортировать данные"),
		.X = 5,
		.Y = 480,
		.Width = 290,
		.Height = 50,
		.ParentWindow = this,
	});
	ExportButton.GetOnButtonClicked().AddCallback([this](Button&){

		wchar_t FilePathBuffer[512] { '\0' };

		OPENFILENAME OpenFileInfo = {};
		OpenFileInfo.lStructSize = sizeof(OPENFILENAME);
		OpenFileInfo.hwndOwner = GetHwnd();
		OpenFileInfo.hInstance = GetHInstance();
		OpenFileInfo.lpstrFilter = L"Bug Tracker Data\0*.BugTrackerData\0\0";
		OpenFileInfo.lpstrFile = FilePathBuffer;
		OpenFileInfo.nMaxFile = sizeof(FilePathBuffer);
		OpenFileInfo.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

		BOOL Result = GetSaveFileName(&OpenFileInfo);

		if(Result == FALSE)
			return;

		StringView Path = FilePathBuffer;
		std::ofstream ofstream(Path.data());
		Storage.Serialize(ofstream);
	});
}

void MainWindow::EndLifetime()
{
	BaseWindow::EndLifetime();

	BugsListView.Destroy();
	BugViewPanel.Destroy();
	CreateBugButton.Destroy();
	BugsFilterPanel.Destroy();
	ImportButton.Destroy();
	ExportButton.Destroy();

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
