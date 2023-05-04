#pragma once

#include <chrono>
#include "SerializedDataTypes.h"

template<typename Duration>
class SerializeableTimePoint : public std::chrono::time_point<std::chrono::system_clock, Duration>
{
public:

	SerializeableTimePoint() = default;

	SerializeableTimePoint(const Duration& other)
		: std::chrono::time_point<std::chrono::system_clock, Duration>(other)
	{
	}

	SerializeableTimePoint(const std::chrono::time_point<std::chrono::system_clock, Duration>& tp)
		: std::chrono::time_point<std::chrono::system_clock, Duration>(tp)
	{
	}

	void Serialize(std::ostream& OutStream) const
	{
		auto ticks = this->time_since_epoch().count();
		OutStream.write(reinterpret_cast<char*>(&ticks), sizeof(ticks));
	}

	void DeSerialize(std::istream& InStream)
	{
		std::int64_t ticks {};
		InStream.read(reinterpret_cast<char*>(&ticks), sizeof(ticks));

		*this = Duration{ticks};
	}

};