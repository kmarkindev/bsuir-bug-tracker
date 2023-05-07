#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include "BaseWindow.h"

// FIXME: Idk, but ListView may want to control columns and items text memory by itself
//	It may cause memory errors since ListView will delete someones memory
//	need to test it and fix
// FIXME: 2nd+ columns do not allow to select text but 1st does
// FIXME: add IsValid checks to all methods
template<typename ItemType>
class ListView : public BaseWindow
{
public:

	ListView() = default;

	ListView(const ListView&) = delete;

	ListView(ListView&& Other) noexcept = default;

	ListView& operator = (const ListView&) = delete;

	ListView& operator = (ListView&& Other) noexcept = default;

	int AddColumn(int InsertIndex, StringView ColumnName, int ColumnWidth)
	{
		LVCOLUMN Lvc = {};
		Lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		Lvc.iSubItem = InsertIndex;
		Lvc.pszText = const_cast<wchar_t*>(ColumnName.data());
		Lvc.cx = ColumnWidth;

		return ListView_InsertColumn(GetHwnd(), InsertIndex, &Lvc);
	}

	void RemoveColumn(int ColumnIndex)
	{
		auto Result = ListView_DeleteColumn(GetHwnd(), ColumnIndex);

		assert(Result != -1);
	}

	// ListView user is responsible to manage ItemPtr
	virtual int AddItem(int InsertIndex, ItemType* ItemPtr)
	{
		LVITEM ItemInfo {};
		ItemInfo.mask = LVIF_PARAM;
		ItemInfo.iItem = InsertIndex;
		ItemInfo.lParam = reinterpret_cast<LPARAM>(ItemPtr);

		int result = ListView_InsertItem(GetHwnd(), &ItemInfo);

		if(result == -1)
		{
			assert(false);
		}

		return result;
	}

	ItemType* GetItemPtrByIndex(int ItemIndex) const
	{
		LVITEM ItemInfo = {};
		ItemInfo.mask = LVIF_PARAM;
		ItemInfo.iItem = ItemIndex;

		if(ListView_GetItem(GetHwnd(), &ItemInfo) == FALSE)
		{
			assert(false);
		}

		return reinterpret_cast<ItemType*>(ItemInfo.lParam);
	}

	int FindItemIndex(ItemType* ItemPtr) const
	{
		LVFINDINFO SearchInfo = {};
		SearchInfo.lParam = reinterpret_cast<LPARAM>(ItemPtr);

		return ListView_FindItem(GetHwnd(), -1, &SearchInfo);
	}

	void RemoveItem(int ItemIndex)
	{
		if(ListView_DeleteItem(GetHwnd(), ItemIndex) == FALSE)
		{
			assert(false);
		}
	}

	void RemoveItem(ItemType* ItemPtr)
	{
		int IndexToRemove = FindItemIndex(ItemPtr);

		if(IndexToRemove == -1)
		{
			assert(false);
			return;
		}

		auto Result = ListView_DeleteColumn(GetHwnd(), IndexToRemove);
		assert(Result != -1);
	}

	void SetItemText(StringView Text, int ItemIndex, int ColumnIndex)
	{
		ListView_SetItemText(GetHwnd(), ItemIndex, ColumnIndex, const_cast<wchar_t*>(Text.data()));
	}

protected:

	void BeginLifetime() override
	{
		BaseWindow::BeginLifetime();

		ReplaceDefaultWindowProcedureWithExisting();
	}

	[[nodiscard]] DWORD GetDefaultStyles() const override
	{
		return WS_CHILD | LVS_REPORT | WS_BORDER | LVS_SINGLESEL;
	}

	[[nodiscard]] const wchar_t* GetWindowClassName() const override
	{
		return WC_LISTVIEW;
	}

};
