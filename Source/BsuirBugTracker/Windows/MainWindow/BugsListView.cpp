#include "BugsListView.h"

void BugsListView::HandleWMNotify(LPNMHDR NotifyInfo, WPARAM WParam, LPARAM LParam)
{
	BaseWindow::HandleWMNotify(NotifyInfo, WParam, LParam);

	if(NotifyInfo->code == LVN_ITEMACTIVATE && Callback)
	{
		int SelectedIndex = ListView_GetNextItem(GetHwnd(), -1, LVNI_SELECTED);

		if(SelectedIndex == -1)
		{
			assert(false);
			return;
		}

		Bug* SelectedBugPtr = GetItemPtrByIndex(SelectedIndex);

		if(!SelectedBugPtr)
		{
			assert(false);
			return;
		}

		Callback(SelectedIndex, SelectedBugPtr);
	}
}

void BugsListView::SetSelectEventCallback(std::function<void(int, Bug*)> NewCallback)
{
	Callback = std::move(NewCallback);
}

int BugsListView::AddItem(int InsertIndex, Bug* ItemPtr)
{
	if(!ItemPtr)
	{
		assert(false);
		return -1;
	}

	int Index = ListView::AddItem(InsertIndex, ItemPtr);

	SetItemText(ItemPtr->GetName(), Index, 0);
	SetItemText(TimestampToString(ItemPtr->GetUpdatedAt()), Index, 1);

	return Index;
}

void BugsListView::BeginLifetime()
{
	ListView::BeginLifetime();

	AddColumn(0, BSUIR_TEXT("Название"), 350);
	AddColumn(1, BSUIR_TEXT("Последнее изменение"), 150);
}