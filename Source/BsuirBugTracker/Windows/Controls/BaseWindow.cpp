#include "BaseWindow.h"

#include <Windows.h>
#include <cassert>
#include "WindowHelpers.h"

void BaseWindow::Initialize(HINSTANCE InHInstance, const WindowInitializeParams& Params)
{
	HInstance = InHInstance;

	const wchar_t* ClassName = GetWindowClassName();

	assert(ClassName != nullptr);

	LPWNDCLASSEX ClassInfo {};
	BOOL ClassInfoExists = GetClassInfoEx(HInstance, ClassName, ClassInfo);

	if(ClassInfoExists == FALSE)
		RegisterWindowClass();

	DWORD Styles = GetDefaultStyles();

	if(Params.InitiallyShown)
		Styles |= WS_VISIBLE;

	Hwnd = CreateWindowEx(
		0,
		ClassName,
		Params.Name.c_str(),
		Styles,
		Params.X, Params.Y, Params.Width, Params.Height,
		Params.ParentWindow ? Params.ParentWindow->GetHwnd() : nullptr,
		nullptr,
		HInstance,
		nullptr
	);

	assert(Hwnd != nullptr);

	SetWindowInstance(Hwnd, this);

	BeginLifetime();

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

void BaseWindow::RegisterWindowClassHelper()
{
	WNDCLASS WindowClass {};
	WindowClass.lpfnWndProc = BaseWindow::WindowProcedureEntry;
	WindowClass.hInstance = HInstance;
	WindowClass.lpszClassName = GetWindowClassName();
	WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&WindowClass);
}

BOOL CALLBACK DestroyChildWindowsCallback(HWND Hwnd, LPARAM LParam)
{
	BaseWindow* WindowInstance = GetWindowInstance(Hwnd);
	WindowInstance->Destroy();

	return TRUE;
}

void BaseWindow::Destroy()
{
	EndLifetime();

	EnumChildWindows(Hwnd, DestroyChildWindowsCallback, 0);

	DestroyWindow(Hwnd);

	WasInitialized = false;
	Hwnd = {};
}

LRESULT BaseWindow::WindowProcedureEntry(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	BaseWindow* WindowInstance = GetWindowInstance(Hwnd);

	if(!WindowInstance)
		return DefWindowProc(Hwnd, UMsg, WParam, LParam);

	return WindowInstance->WindowProcedure(Hwnd, UMsg, WParam, LParam);
}

BaseWindow::BaseWindow(BaseWindow&& other) noexcept
	: Hwnd(other.Hwnd), HInstance(other.HInstance), WasInitialized(other.WasInitialized)
{
	SetWindowInstance(Hwnd, this);
}

BaseWindow& BaseWindow::operator=(BaseWindow&& other) noexcept
{
	Hwnd = other.Hwnd;
	HInstance = other.HInstance;
	WasInitialized = other.WasInitialized;

	SetWindowInstance(Hwnd, this);

	return *this;
}

void BaseWindow::BeginLifetime()
{

}

void BaseWindow::EndLifetime()
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

LRESULT BaseWindow::WindowProcedure(HWND InHwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch (UMsg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(InHwnd, &ps);
			FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW+1));
			EndPaint(InHwnd, &ps);

			break;
		}
	}

	return DefWindowProc(InHwnd, UMsg, WParam, LParam);
}

void BaseWindow::RegisterWindowClass()
{

}
