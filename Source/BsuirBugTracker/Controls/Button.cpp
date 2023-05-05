#include "Button.h"

#include <BsuirBugTracker/Windows/BaseWindow.h>

Button::Button(Button&& Other) noexcept
	: Hwnd(Other.Hwnd), WasInitialized(Other.WasInitialized)
{
	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

Button& Button::operator=(Button&& Other) noexcept
{
	Hwnd = Other.Hwnd;
	WasInitialized = Other.WasInitialized;

	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	return *this;
}

void Button::InitializeButtonInstance(const BaseWindow& ParentWindow, const ButtonInitializeParams& Params)
{
	DWORD Styles = WS_TABSTOP | WS_CHILD | BS_DEFPUSHBUTTON;

	if(Params.InitiallyShown)
		Styles |= WS_VISIBLE;

	Hwnd = CreateWindow(
		L"BUTTON",
		Params.ButtonText.c_str(),
		Styles,
		Params.X,
		Params.Y,
		Params.Width,
		Params.Height,
		ParentWindow.GetHwnd(),
		nullptr,
		ParentWindow.GetHInstance(),
		nullptr
	);

	assert(Hwnd != nullptr);

	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	WasInitialized = true;
}

void Button::DestroyButtonInstance()
{
	DestroyWindow(Hwnd);

	Hwnd = {};
	WasInitialized = false;
}

bool Button::IsValid() const
{
	return WasInitialized;
}

void Button::RaiseClickEvent()
{
	if(Callback)
		Callback(*this);
}

void Button::SetOnClickCallback(std::function<void(Button&)> NewCallback)
{
	Callback = std::move(NewCallback);
}
