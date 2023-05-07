#pragma once

#include <Windows.h>
#include "BsuirBugTracker/Types/Types.h"
#include "BaseWindow.h"
#include <functional>
#include "BsuirBugTracker/Utils/Event.h"

class Button : public BaseWindow
{
public:

	Button() = default;

	Button(const Button&) = delete;

	Button(Button&& Other) noexcept = default;

	Button& operator = (const Button&) = delete;

	Button& operator = (Button&& Other) noexcept = default;

	Event<Button&>& GetOnButtonClicked();

protected:

	void HandleWMCommand(WORD NotificationCode, WPARAM WParam, LPARAM LParam) override;

	void BeginLifetime() override;

	[[nodiscard]] const wchar_t* GetWindowClassName() const override;

	[[nodiscard]] DWORD GetDefaultStyles() const override;

private:

	Event<Button&> OnButtonClicked {};
};
