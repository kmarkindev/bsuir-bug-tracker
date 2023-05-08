#pragma once

#include "BaseWindow.h"

class TimestampPicker : public BaseWindow
{
public:

	TimestampPicker() = default;

	TimestampPicker(const TimestampPicker&) = delete;

	TimestampPicker(TimestampPicker&& Other) noexcept = default;

	TimestampPicker& operator = (const TimestampPicker&) = delete;

	TimestampPicker& operator = (TimestampPicker&& Other) noexcept = default;

	[[nodiscard]] bool HasSelectedTime() const;

	void ClearValue();

	[[nodiscard]] Timestamp GetTime() const;

protected:

	void BeginLifetime() override;

	[[nodiscard]] DWORD GetDefaultStyles() const override;

	[[nodiscard]] const wchar_t* GetWindowClassName() const override;

};
