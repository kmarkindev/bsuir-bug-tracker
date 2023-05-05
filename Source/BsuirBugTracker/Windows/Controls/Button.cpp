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

void Button::BeginLifetime()
{
	ReplaceDefaultWindowProcedure();
}

void Button::HandleControlMessage(WORD NotificationCode)
{
	BaseWindow::HandleControlMessage(NotificationCode);

	if(NotificationCode == BN_CLICKED)
	{
		RaiseClickEvent();
	}
}