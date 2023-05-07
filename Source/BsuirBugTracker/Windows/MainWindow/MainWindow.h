#pragma once

#include "BsuirBugTracker/Windows/Controls/Controls.h"
#include "BugsListView.h"
#include "BugViewPanel.h"

class MainWindow : public Window
{
public:

	MainWindow() = default;

	MainWindow(const MainWindow&) = delete;

	MainWindow& operator = (const MainWindow&) = delete;

	MainWindow(MainWindow&&) = default;

	MainWindow& operator = (MainWindow&&) = default;

protected:

	LRESULT WindowProcedure(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam) override;

	[[nodiscard]] const wchar_t* GetWindowClassName() const override;

	[[nodiscard]] DWORD GetDefaultStyles() const override;

	void RegisterWindowClass() override;

	void BeginLifetime() override;

	void EndLifetime() override;

private:

	BugsListView BugsListView {};

	BugViewPanel BugViewPanel {};

};
