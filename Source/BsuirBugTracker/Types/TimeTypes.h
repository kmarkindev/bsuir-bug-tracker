#pragma once

#include "SerializeableTimestamp.h"

using Timestamp = SerializeableTimePoint<std::chrono::seconds>;

inline String TimestampToString(const Timestamp& Timestamp)
{
	// FIXME: dont do two string allocations
	// FIXME: it works only if Timestamp has a second duration

	std::chrono::sys_seconds SysTime = Timestamp;

	if(SysTime.time_since_epoch() == std::chrono::seconds { 0 })
	{
		return BSUIR_TEXT("Нет");
	}

	std::chrono::zoned_time Zoned { std::chrono::current_zone(),  SysTime };
	std::chrono::local_seconds LocalTime { Zoned };

	auto Formatted = std::format(L"{0:%F} {0:%T}", LocalTime);

	return { Formatted.c_str() };
}