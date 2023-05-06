#include "ListView.h"

#include <CommCtrl.h>

DWORD ListView::GetDefaultStyles() const
{
	return WS_CHILD | LVS_REPORT | WS_BORDER;
}

const wchar_t* ListView::GetWindowClassName() const
{
	return WC_LISTVIEW;
}

void ListView::BeginLifetime()
{
	BaseWindow::BeginLifetime();

	ReplaceDefaultWindowProcedureWithExisting();
}

int ListView::AddColumn(int InsertIndex, StringView ColumnName, int ColumnWidth)
{
	LVCOLUMN Lvc = {};
	Lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	Lvc.iSubItem = InsertIndex;
	Lvc.pszText = const_cast<wchar_t*>(ColumnName.data());
	Lvc.cx = ColumnWidth;

	return ListView_InsertColumn(GetHwnd(), InsertIndex, &Lvc);
}

void ListView::RemoveColumn(int ColumnIndex)
{
	auto Result = ListView_DeleteColumn(GetHwnd(), ColumnIndex);

	assert(Result != -1);
}

void ListView::SetItemText(StringView Text, int ItemIndex, int ColumnIndex)
{
	ListView_SetItemText(GetHwnd(), ItemIndex, ColumnIndex, const_cast<wchar_t*>(Text.data()));
}

int ListView::AddItem(int InsertIndex)
{
	LVITEM ItemInfo {};
	ItemInfo.iItem = InsertIndex;
	ListView_InsertItem(GetHwnd(), &ItemInfo);

	return ListView_InsertItem(GetHwnd(), &ItemInfo);
}

void ListView::RemoveItem(int ItemIndex)
{
	ListView_DeleteItem(GetHwnd(), ItemIndex);
}
