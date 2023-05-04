#pragma once

#include <string>
#include "BsuirBugTracker/Types/SerializedDataTypes.h"

template<typename T>
class SerializeableString : public std::basic_string<T>
{
public:

	SerializeableString() = default;

	SerializeableString(const typename std::basic_string<T>::size_type count, const T ch)
		: std::basic_string<T>(count, ch)
	{
	}

	void Serialize(std::ostream& OutStream) const
	{

	}

	void DeSerialize(std::istream& InStream)
	{

	}

};

template<typename T>
class SerializeableStringView : public std::basic_string_view<T>
{
public:

	SerializeableStringView() = default;

	SerializeableStringView(const SerializeableString<T>& view)
		: std::basic_string_view<T>(view)
	{
	}

	void Serialize(std::ostream& OutStream) const
	{

	}

	void DeSerialize(std::istream& InStream)
	{

	}

};