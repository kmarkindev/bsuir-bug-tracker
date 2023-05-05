#pragma once

#include "BaseWindow.h"

class Panel : public BaseWindow
{
public:

	Panel() = default;

	Panel(const Panel&) = delete;

	Panel(Panel&& Other) noexcept = default;

	Panel& operator = (const Panel&) = delete;

	Panel& operator = (Panel&& Other) noexcept = default;

protected:

	void RegisterWindowClass() override;

	LRESULT WindowProcedure(HWND InHwnd, UINT UMsg, WPARAM WParam, LPARAM LParam) override;

	[[nodiscard]] DWORD GetDefaultStyles() const override;

	[[nodiscard]] const wchar_t* GetWindowClassName() const override;

};
