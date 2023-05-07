#include "TextInput.h"

#include <Richedit.h>
#include "WindowHelpers.h"

DWORD TextInput::GetDefaultStyles() const
{
	return WS_CHILD | WS_BORDER | WS_TABSTOP | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL;
}

const wchar_t* TextInput::GetWindowClassName() const
{
	return MSFTEDIT_CLASS;
}

void TextInput::SetText(StringView NewText)
{
	SetWindowText(GetHwnd(), NewText.data());
}

String TextInput::GetText() const
{
	String Result(GetWindowTextLength(GetHwnd()), '\0');

	// Add 1 to cover \0
	GetWindowText(GetHwnd(), Result.data(), static_cast<int>(Result.size() + 1));

	return Result;
}

void TextInput::SetReadOnly(bool bEnableReadOnly)
{
	SendMessage(GetHwnd(), EM_SETREADONLY, bEnableReadOnly ? TRUE : FALSE, 0);
}

bool TextInput::IsReadOnly() const
{
	return WindowHasStyle(GetHwnd(), ES_READONLY);
}

void TextInput::BeginLifetime()
{
	BaseWindow::BeginLifetime();

	ReplaceDefaultWindowProcedureWithExisting();
}
