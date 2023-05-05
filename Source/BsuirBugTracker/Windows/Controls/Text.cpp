#include "Text.h"

#include <CommCtrl.h>

DWORD Text::GetDefaultStyles() const
{
	return WS_CHILD | SS_SIMPLE;
}

const wchar_t* Text::GetWindowClassName() const
{
	return WC_STATIC;
}

void Text::BeginLifetime()
{
	BaseWindow::BeginLifetime();

	ReplaceDefaultWindowProcedureWithExisting();
}

void Text::SetText(StringView NewText)
{
	SetWindowText(GetHwnd(), NewText.data());
}
