#include "BaseWindow.h"

#include <Windows.h>
#include <cassert>
#include <BsuirBugTracker/Controls/Controls.h>

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
		nullptr
	);

	assert(Hwnd != nullptr);

	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	BeginWindowLifetime();

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
	EndWindowLifetime();

	DestroyWindow(Hwnd);

	WasInitialized = false;
	Hwnd = {};
}

LRESULT BaseWindow::WindowProcedureBase(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch (UMsg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(Hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW+1));
			EndPaint(Hwnd, &ps);

			break;
		}
		case WM_COMMAND:
		{
			HWND ControlHwnd = reinterpret_cast<HWND>(LParam);
			Button* Button = reinterpret_cast<class Button*>(GetWindowLongPtr(ControlHwnd, GWLP_USERDATA));
			Button->RaiseClickEvent();

			break;
		}
	}

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

void BaseWindow::BeginWindowLifetime()
{

}

void BaseWindow::EndWindowLifetime()
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
