#include "BaseWindow.h"

#include <Windows.h>
#include <cassert>
#include "WindowHelpers.h"

void BaseWindow::Initialize(HINSTANCE InHInstance, const WindowInitializeParams& Params)
{
	if(WasInitialized)
	{
		assert(false);
		return;
	}

	HInstance = InHInstance;

	const wchar_t* ClassName = GetWindowClassName();

	assert(ClassName != nullptr);

	LPWNDCLASSEX ClassInfo {};
	BOOL ClassInfoExists = GetClassInfoEx(HInstance, ClassName, ClassInfo);

	if(ClassInfoExists == FALSE)
		RegisterWindowClass();

	DWORD Styles = Params.Styles | GetDefaultStyles();

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

void BaseWindow::SetWindowVisibility(bool bShowWindow)
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
	WindowClass.hIcon = LoadIcon(GetHInstance(), MAKEINTRESOURCE(1));

	RegisterClass(&WindowClass);
}

void BaseWindow::Destroy()
{
	if(!WasInitialized)
	{
		assert(false);
		return;
	}

	EndLifetime();

	DestroyWindow(Hwnd);

	WasInitialized = false;
	Hwnd = {};
}

LRESULT BaseWindow::WindowProcedureEntry(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	// Handle the case if event was generated by control
	// To process it in control class, not window class
	if(UMsg == WM_COMMAND)
	{
		WORD NotificationCode = HIWORD(WParam);
		BaseWindow* WindowInstance = GetWindowInstance(reinterpret_cast<HWND>(LParam));

		if (WindowInstance)
			WindowInstance->HandleWMCommand(NotificationCode, WParam, LParam);
	}

	if(UMsg == WM_NOTIFY)
	{
		LPNMHDR NotifyInfo = reinterpret_cast<LPNMHDR>(LParam);

		if(NotifyInfo->hwndFrom != nullptr)
		{
			BaseWindow* WindowInstance = GetWindowInstance(NotifyInfo->hwndFrom);

			if (WindowInstance)
				WindowInstance->HandleWMNotify(NotifyInfo, WParam, LParam);
		}
	}

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
	return DefaultWindowProcedure(InHwnd, UMsg, WParam, LParam);
}

void BaseWindow::RegisterWindowClass()
{

}

void BaseWindow::ReplaceDefaultWindowProcedureWithExisting()
{
	DefaultWindowProcedure = reinterpret_cast<WNDPROC>(GetWindowLongPtr(GetHwnd(), GWLP_WNDPROC));

	SetWindowLongPtr(GetHwnd(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(BaseWindow::WindowProcedureEntry));
}

void BaseWindow::HandleWMCommand(WORD NotificationCode, WPARAM WParam, LPARAM LParam)
{

}

void BaseWindow::HandleWMNotify(LPNMHDR NotifyInfo, WPARAM WParam, LPARAM LParam)
{

}

BaseWindow::~BaseWindow()
{
	if(WasInitialized)
	{
		assert(false);
	}
}
