#pragma once

#include <memory>
#include <Windows.h>
#include <cassert>
#include <BsuirBugTracker/Types/Types.h>

struct WindowInitializeParams
{
	String WindowName {L"New Window"};
	int X = CW_USEDEFAULT;
	int Y = CW_USEDEFAULT;
	int Width = CW_USEDEFAULT;
	int Height = CW_USEDEFAULT;
	HWND ParentWindow {};
	bool InitiallyShown = true;
};

class BaseWindow
{
public:

	BaseWindow() = default;

	BaseWindow(const BaseWindow&) = delete;

	BaseWindow& operator = (const BaseWindow&) = delete;

	BaseWindow(BaseWindow&& other) noexcept;

	BaseWindow& operator = (BaseWindow&& other) noexcept;

	void InitializeWindowInstance(HINSTANCE HInstance, const WindowInitializeParams& Params);

	void DestroyWindowInstance();

	[[nodiscard]] bool IsValid() const;

	void SetVindowVisibility(bool bShowWindow);

protected:

	[[nodiscard]] virtual const wchar_t* GetWindowClassName() const = 0;

	virtual void RegisterWindowClass(HINSTANCE InHInstance) = 0;

	void RegisterWindowClassHelper(HINSTANCE HInstance, WNDPROC WndProc);

	static LRESULT CALLBACK WindowProcedureHelper(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam);

private:

	bool WasInitialized = false;

	HWND Hwnd {};

	HINSTANCE HInstance {};

};
