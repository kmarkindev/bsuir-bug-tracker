#include "MainWindow.h"

#include <Windows.h>
#include <BsuirBugTracker/Utils/GuidGenerator.h>

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
		String Guid = GenerateGuid();
		MessageBox(nullptr, Guid.c_str(), L"Button click", MB_OK);
	});

	TestListView.Initialize(GetHInstance(), WindowInitializeParams{
		.X = 300,
		.Y = 20,
		.Width = 400,
		.Height = 500,
		.ParentWindow = this,
	});

	static Bug TestBug { GenerateGuid() };
	TestBug.SetName(BSUIR_TEXT("Тестовое название бага"));
	TestBug.SetUpdatedAt({ std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()) });

	static Bug TestBug2 { GenerateGuid() };
	TestBug2.SetName(BSUIR_TEXT("Еще один баг лол"));
	auto time = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
	time -= std::chrono::seconds { 30 };
	TestBug2.SetUpdatedAt({ time });

	TestListView.AddItem(0, &TestBug);
	TestListView.AddItem(0, &TestBug2);

	TestListView.SetSelectEventCallback([](int Index, Bug* Ptr){
		MessageBox(nullptr, Ptr->GetGuid().c_str(), Ptr->GetName().c_str(), MB_OK);
	});

	TestText.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = BSUIR_TEXT("Пробный text! @# !@ !%@#^^ qwe123123123"),
		.X = 20,
		.Y = 200,
		.Width = 250,
		.Height = 150,
		.ParentWindow = this,
	});

	TestTextInput.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = BSUIR_TEXT("Text Text Text"),
		.X = 20,
		.Y = 400,
		.Width = 250,
		.Height = 75,
		.ParentWindow = this,
	});

	TestPanel.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = L"Test Panel",
		.X = 20,
		.Y = 500,
		.Width = 250,
		.Height = 75,
		.ParentWindow = this,
	});

	TestComboBox.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = L"Test Combo box",
		.X = 20,
		.Y = 600,
		.Width = 250,
		.Height = 150,
		.ParentWindow = this,
	});

	TestComboBox.AddItem(L"Test 1");
	TestComboBox.AddItem(L"Test 2");
	TestComboBox.AddItem(L"ATest 3");

	TestTimestampPicker.Initialize(GetHInstance(), WindowInitializeParams {
		.Name = L"Test Timestamp picker",
		.X = 300,
		.Y = 600,
		.Width = 250,
		.Height = 35,
		.ParentWindow = this,
	});
}

void MainWindow::EndLifetime()
{
	BaseWindow::EndLifetime();

	TestButton.Destroy();
	TestListView.Destroy();
	TestText.Destroy();
	TestTextInput.Destroy();
	TestPanel.Destroy();
	TestComboBox.Destroy();
	TestTimestampPicker.Destroy();
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
