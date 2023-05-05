#include "BaseWindow.h"

#include <Windows.h>
#include <cassert>

void BaseWindow::InitializeWindowInstance(HINSTANCE InHInstance, const WindowInitializeParams& Params)
{
	HInstance = InHInstance;

	const wchar_t* ClassName = GetWindowClassName();

	assert(ClassName != nullptr);

	LPWNDCLASSEX ClassInfo {};
	BOOL ClassInfoExists = GetClassInfoEx(HInstance, ClassName, ClassInfo);

	if(ClassInfoExists == FALSE)
		RegisterWindowClass();

	DWORD Styles = WS_OVERLAPPEDWINDOW;

	if(Params.InitiallyShown)
		Styles |= WS_VISIBLE;

	Hwnd = CreateWindowEx(
		0,
		ClassName,
		Params.WindowName.c_str(),
		Styles,
		Params.X, Params.Y, Params.Width, Params.Height,
		Params.ParentWindow,
		nullptr,
		HInstance,
		this
	);

	assert(Hwnd != nullptr);

	InitWindowLayout();

	WasInitialized = true;
}

bool BaseWindow::IsValid() const
{
	return WasInitialized && HInstance && Hwnd;
}

void BaseWindow::SetVindowVisibility(bool bShowWindow)
{
	ShowWindow(Hwnd, bShowWindow ? SW_SHOW : SW_HIDE);
}

void BaseWindow::RegisterWindowClassHelper(WNDPROC WndProc)
{
	WNDCLASS WindowClass {};
	WindowClass.lpfnWndProc = WndProc;
	WindowClass.hInstance = HInstance;
	WindowClass.lpszClassName = GetWindowClassName();
	WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&WindowClass);
}

void BaseWindow::DestroyWindowInstance()
{
	DestroyWindowLayout();

	DestroyWindow(Hwnd);

	WasInitialized = false;
	Hwnd = {};
}

LRESULT BaseWindow::WindowProcedureHelper(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	return DefWindowProc(Hwnd, UMsg, WParam, LParam);
}

BaseWindow::BaseWindow(BaseWindow&& other) noexcept
	: Hwnd(other.Hwnd), HInstance(other.HInstance), WasInitialized(other.WasInitialized)
{
	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

BaseWindow& BaseWindow::operator=(BaseWindow&& other) noexcept
{
	Hwnd = other.Hwnd;
	HInstance = other.HInstance;
	WasInitialized = other.WasInitialized;

	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	return *this;
}

void BaseWindow::InitWindowLayout()
{

}

void BaseWindow::DestroyWindowLayout()
{

}

HWND BaseWindow::GetHwnd() const
{
	return Hwnd;
}

HINSTANCE BaseWindow::GetHInstance() const
{
	return HInstance;
}
