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

	void InitializeWindowInstance(HINSTANCE InHInstance, const WindowInitializeParams& Params);

	void DestroyWindowInstance();

	[[nodiscard]] bool IsValid() const;

	void SetVindowVisibility(bool bShowWindow);

	HWND GetHwnd() const;

	HINSTANCE GetHInstance() const;

protected:

	[[nodiscard]] virtual const wchar_t* GetWindowClassName() const = 0;

	virtual void RegisterWindowClass() = 0;

	void RegisterWindowClassHelper(WNDPROC WndProc);

	static LRESULT CALLBACK WindowProcedureHelper(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam);

	virtual void InitWindowLayout();

	virtual void DestroyWindowLayout();

private:

	bool WasInitialized = false;

	HWND Hwnd {};

	HINSTANCE HInstance {};

};
