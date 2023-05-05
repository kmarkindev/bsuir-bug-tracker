#pragma once

#include "BaseWindow.h"

class Window : public BaseWindow
{

public:

	Window() = default;

	Window(const Window&) = delete;

	Window(Window&& Other) noexcept = default;

	Window& operator = (const Window&) = delete;

	Window& operator = (Window&& Other) noexcept = default;

protected:

	[[nodiscard]] DWORD GetDefaultStyles() const override;

};
