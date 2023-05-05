#pragma once

#include <Windows.h>
#include "BaseWindow.h"

class ListView : public BaseWindow
{
public:

	ListView() = default;

	ListView(const ListView&) = delete;

	ListView(ListView&& Other) noexcept = default;

	ListView& operator = (const ListView&) = delete;

	ListView& operator = (ListView&& Other) noexcept = default;

	void AddColumn(int ColumnIndex, StringView ColumnName, int ColumnWidth);

	void RemoveColumn(int ColumnIndex);

protected:

	void BeginLifetime() override;

	[[nodiscard]] DWORD GetDefaultStyles() const override;

	[[nodiscard]] const wchar_t* GetWindowClassName() const override;

};
