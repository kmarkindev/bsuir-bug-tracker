#pragma once

#include "BaseWindow.h"

class TextInput : public BaseWindow
{
public:

	TextInput() = default;

	TextInput(const TextInput&) = delete;

	TextInput(TextInput&& Other) noexcept = default;

	TextInput& operator = (const TextInput&) = delete;

	TextInput& operator = (TextInput&& Other) noexcept = default;

	void SetText(StringView NewText);

	[[nodiscard]] String GetText() const;

	void SetReadOnly(bool bEnableReadOnly);

	[[nodiscard]] bool IsReadOnly() const;

protected:

	[[nodiscard]] DWORD GetDefaultStyles() const override;

	[[nodiscard]] const wchar_t* GetWindowClassName() const override;

};
