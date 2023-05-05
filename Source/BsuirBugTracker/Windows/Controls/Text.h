#pragma once

#include "BaseWindow.h"

class Text : public BaseWindow
{
public:

	Text() = default;

	Text(const Text&) = delete;

	Text(Text&& Other) noexcept = default;

	Text& operator = (const Text&) = delete;

	Text& operator = (Text&& Other) noexcept = default;

	void SetText(StringView NewText);

protected:

	void BeginLifetime() override;

	[[nodiscard]] DWORD GetDefaultStyles() const override;

	[[nodiscard]] const wchar_t* GetWindowClassName() const override;
};
