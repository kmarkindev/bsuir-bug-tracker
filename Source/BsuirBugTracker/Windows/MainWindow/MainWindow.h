#pragma once

#include <BsuirBugTracker/Windows/BaseWindow.h>
#include <BsuirBugTracker/Controls/Button.h>

class MainWindow : public BaseWindow
{
public:

	MainWindow() = default;

	MainWindow(const MainWindow&) = delete;

	MainWindow& operator = (const MainWindow&) = delete;

	MainWindow(MainWindow&&) = default;

	MainWindow& operator = (MainWindow&&) = default;

protected:

	static LRESULT CALLBACK WindowProc(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam);

	[[nodiscard]] const wchar_t* GetWindowClassName() const override;

	void RegisterWindowClass() override;

	void BeginWindowLifetime() override;

	void EndWindowLifetime() override;

private:

	Button TestButton;

};
