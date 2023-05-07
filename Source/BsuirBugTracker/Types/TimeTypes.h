#pragma once

#include "SerializeableTimestamp.h"

using Timestamp = SerializeableTimePoint<std::chrono::seconds>;

inline String TimestampToString(const Timestamp& Timestamp)
{
	// FIXME: dont do two string allocations
	// FIXME: it works only if Timestamp has a second duration

	std::chrono::sys_seconds SysTime = Timestamp;

	auto Formatted = std::format(L"{0:%F} {0:%T}", SysTime);

	return { Formatted.c_str() };
}