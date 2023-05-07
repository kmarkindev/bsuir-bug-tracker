#include "ComboBox.h"

#include <CommCtrl.h>
#include <cstring>

DWORD ComboBox::GetDefaultStyles() const
{
	return WS_CHILD | WS_OVERLAPPED | CBS_HASSTRINGS | WS_BORDER | WS_TABSTOP | CBS_DROPDOWNLIST;
}

const wchar_t* ComboBox::GetWindowClassName() const
{
	return WC_COMBOBOX;
}

void ComboBox::BeginLifetime()
{
	BaseWindow::BeginLifetime();

	ReplaceDefaultWindowProcedureWithExisting();
}

void ComboBox::AddItem(StringView StringView)
{
	wchar_t* Copy = new wchar_t[StringView.size() + 1];

	memcpy(Copy, StringView.data(), (StringView.size() + 1) * sizeof(wchar_t));

	SendMessage(GetHwnd(), CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(Copy));
}

int ComboBox::GetSelectedIndex() const
{
	return static_cast<int>(SendMessage(GetHwnd(), CB_GETCURSEL, 0, 0));
}

void ComboBox::SetSelectedIndex(int NewIndex)
{
	SendMessage(GetHwnd(), CB_SETCURSEL, NewIndex, 0);
}