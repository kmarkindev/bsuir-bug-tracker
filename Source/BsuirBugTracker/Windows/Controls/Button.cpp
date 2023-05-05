#include "Button.h"

#include <CommCtrl.h>

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
	return WC_BUTTON;
}

DWORD Button::GetDefaultStyles() const
{
	return WS_TABSTOP | WS_CHILD | BS_DEFPUSHBUTTON;
}

void Button::BeginLifetime()
{
	ReplaceDefaultWindowProcedureWithExisting();
}

void Button::HandleControlMessage(WORD NotificationCode)
{
	BaseWindow::HandleControlMessage(NotificationCode);

	if(NotificationCode == BN_CLICKED)
	{
		RaiseClickEvent();
	}
}
