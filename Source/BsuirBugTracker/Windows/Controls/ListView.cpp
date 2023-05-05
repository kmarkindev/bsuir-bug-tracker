#include "ListView.h"

#include <CommCtrl.h>

DWORD ListView::GetDefaultStyles() const
{
	return WS_CHILD | LVS_REPORT | LVS_EDITLABELS;
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

void ListView::AddColumn(int ColumnIndex, StringView ColumnName, int ColumnWidth)
{
	LVCOLUMN Lvc = {};
	Lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	Lvc.iSubItem = ColumnIndex;
	Lvc.pszText = const_cast<wchar_t*>(ColumnName.data());
	Lvc.cx = ColumnWidth;

	auto Result = ListView_InsertColumn(GetHwnd(), ColumnIndex, &Lvc);

	assert(Result != -1);
}

void ListView::RemoveColumn(int ColumnIndex)
{
	auto Result = ListView_DeleteColumn(GetHwnd(), ColumnIndex);

	assert(Result != -1);
}
