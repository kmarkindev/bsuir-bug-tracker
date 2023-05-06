#pragma once

#include "BaseWindow.h"

class ComboBox : public BaseWindow
{
public:

	ComboBox() = default;

	ComboBox(const ComboBox&) = delete;

	ComboBox(ComboBox&& Other) noexcept = default;

	ComboBox& operator = (const ComboBox&) = delete;

	ComboBox& operator = (ComboBox&& Other) noexcept = default;

	void AddItem(StringView StringView);

	void SetSelectedIndex(int NewIndex);

	[[nodiscard]] int GetSelectedIndex() const;

protected:

	[[nodiscard]] DWORD GetDefaultStyles() const override;

	[[nodiscard]] const wchar_t* GetWindowClassName() const override;

	void BeginLifetime() override;

};
