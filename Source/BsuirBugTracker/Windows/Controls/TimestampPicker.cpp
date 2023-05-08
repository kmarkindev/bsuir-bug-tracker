#include "TimestampPicker.h"
#include <CommCtrl.h>

DWORD TimestampPicker::GetDefaultStyles() const
{
	return WS_CHILD | WS_BORDER | DTS_SHOWNONE | DTS_LONGDATEFORMAT | DTS_TIMEFORMAT;
}

const wchar_t* TimestampPicker::GetWindowClassName() const
{
	return DATETIMEPICK_CLASS;
}

void TimestampPicker::BeginLifetime()
{
	BaseWindow::BeginLifetime();

	ReplaceDefaultWindowProcedureWithExisting();

	SendMessage(GetHwnd(), DTM_SETFORMAT, 0, reinterpret_cast<LPARAM>(TEXT("yyyy-MM-dd HH:mm:ss")));
}

bool TimestampPicker::HasSelectedTime() const
{
	DATETIMEPICKERINFO Info = {
		.cbSize = sizeof(DATETIMEPICKERINFO)
	};
	DateTime_GetDateTimePickerInfo(GetHwnd(), &Info);

	return Info.stateCheck == STATE_SYSTEM_CHECKED;
}

Timestamp TimestampPicker::GetTime() const
{
	if(!HasSelectedTime())
	{
		assert(false);
		return {};
	}

	SYSTEMTIME SysTime = {};
	DateTime_GetSystemtime(GetHwnd(), &SysTime);

	auto LocalTime = std::chrono::local_seconds {
		std::chrono::local_days {
			std::chrono::year_month_day {
				std::chrono::year { SysTime.wYear },
				std::chrono::month { SysTime.wMonth },
				std::chrono::day { SysTime.wDay }
			}
		}
	};

	LocalTime += std::chrono::hours { SysTime.wHour };
	LocalTime += std::chrono::minutes { SysTime.wMinute };
	LocalTime += std::chrono::seconds { SysTime.wSecond };

	std::chrono::zoned_seconds ZonedSeconds(std::chrono::current_zone(), LocalTime);

	return { ZonedSeconds.get_sys_time() };
}

void TimestampPicker::ClearValue()
{
	DateTime_SetSystemtime(GetHwnd(), GDT_NONE, 0);
}
