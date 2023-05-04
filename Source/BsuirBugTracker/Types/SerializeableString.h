#pragma once

#include <string>
#include "BsuirBugTracker/Types/SerializedDataTypes.h"

template<typename T>
class SerializeableString : public std::basic_string<T>
{
public:

	[[nodiscard]] SerializedData Serialize() const
	{
		return {};
	}

	void DeSerialize(SerializeDataView dataView)
	{

	}

};

template<typename T>
class SerializeableStringView : public std::basic_string_view<T>
{
public:

	[[nodiscard]] SerializedData Serialize() const
	{
		return {};
	}

	void DeSerialize(SerializeDataView dataView)
	{

	}

};