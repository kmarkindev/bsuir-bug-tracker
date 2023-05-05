#include "Button.h"

void Button::RaiseClickEvent()
{
	if(Callback)
		Callback(*this);
}

void Button::SetOnClickCallback(std::function<void(Button&)> NewCallback)
{
	Callback = std::move(NewCallback);
}

const wchar_t* Button::GetWindowClassName() const
{
	return L"BUTTON";
}

DWORD Button::GetDefaultStyles() const
{
	return WS_TABSTOP | WS_CHILD | BS_DEFPUSHBUTTON;
}

LRESULT Button::WindowProcedure(HWND InHwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch(UMsg)
	{
		case WM_COMMAND:
		{
			RaiseClickEvent();
			break;
		}
	}

	return BaseWindow::WindowProcedure(InHwnd, UMsg, WParam, LParam);
}
