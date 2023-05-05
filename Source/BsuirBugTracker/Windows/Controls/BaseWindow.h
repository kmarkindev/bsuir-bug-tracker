#pragma once

#include <memory>
#include <Windows.h>
#include <cassert>
#include "BsuirBugTracker/Types/Types.h"

class BaseWindow;

struct WindowInitializeParams
{
	String Name { L"No Name"};
	int X = CW_USEDEFAULT;
	int Y = CW_USEDEFAULT;
	int Width = CW_USEDEFAULT;
	int Height = CW_USEDEFAULT;
	BaseWindow* ParentWindow {};
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

	~BaseWindow();

	void Initialize(HINSTANCE InHInstance, const WindowInitializeParams& Params);

	// Note: Make sure to destroy all child windows as well
	virtual void Destroy();

	[[nodiscard]] bool IsValid() const;

	void SetVindowVisibility(bool bShowWindow);

	[[nodiscard]] HWND GetHwnd() const;

	[[nodiscard]] HINSTANCE GetHInstance() const;

protected:

	// Note: use InHwnd (method argument) instead of Hwnd (class member) since
	// top level WindowProcedure may call Destroy() and Hwnd is going to be invalid
	virtual LRESULT WindowProcedure(HWND InHwnd, UINT UMsg, WPARAM WParam, LPARAM LParam);

	[[nodiscard]] virtual DWORD GetDefaultStyles() const = 0;

	[[nodiscard]] virtual const wchar_t* GetWindowClassName() const = 0;

	virtual void RegisterWindowClass();

	void RegisterWindowClassHelper();

	virtual void BeginLifetime();

	virtual void EndLifetime();

	virtual void HandleControlMessage(WORD NotificationCode);

	static LRESULT CALLBACK WindowProcedureEntry(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam);

	// Use it when you need to wrap already existing windows class
	// to use its window procedure as a default
	// and implement events on top of it
	void ReplaceDefaultWindowProcedure();

private:

	bool WasInitialized = false;

	HWND Hwnd {};

	HINSTANCE HInstance {};

	WNDPROC DefaultWindowProcedure = DefWindowProc;

};
