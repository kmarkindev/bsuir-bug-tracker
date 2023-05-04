#pragma once

#include <string>
#include "BsuirBugTracker/Types/SerializedDataTypes.h"

template<typename T>
class SerializeableString : public std::basic_string<T>
{
public:

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

	void Serialize(std::ostream& OutStream) const
	{

	}

	void DeSerialize(std::istream& InStream)
	{

	}

};