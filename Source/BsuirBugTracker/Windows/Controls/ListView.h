#pragma once

#include <Windows.h>
#include "BaseWindow.h"

// FIXME: Idk, but ListView may want to control columns and items text memory by itself
//	It may cause memory errors since ListView will delete someones memory
//	need to test it and fix
// FIXME: 2nd+ columns do not allow to select text but 1st does
class ListView : public BaseWindow
{
public:

	ListView() = default;

	ListView(const ListView&) = delete;

	ListView(ListView&& Other) noexcept = default;

	ListView& operator = (const ListView&) = delete;

	ListView& operator = (ListView&& Other) noexcept = default;

	int AddColumn(int InsertIndex, StringView ColumnName, int ColumnWidth);

	void RemoveColumn(int ColumnIndex);

	int AddItem(int InsertIndex);

	void RemoveItem(int ItemIndex);

	void SetItemText(StringView Text, int ItemIndex, int ColumnIndex);

protected:

	void BeginLifetime() override;

	[[nodiscard]] DWORD GetDefaultStyles() const override;

	[[nodiscard]] const wchar_t* GetWindowClassName() const override;

};
