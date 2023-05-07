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

	explicit SerializeableString(std::basic_string<T> right)
		: std::basic_string<T>(std::move(right))
	{

	}

	SerializeableString(const T* const ptr)
		: std::basic_string<T>(ptr)
	{
	}

	void Serialize(std::ostream& OutStream) const
	{
		std::int64_t size = this->size();
		OutStream.write(reinterpret_cast<char*>(&size), sizeof(size));
		OutStream.write(reinterpret_cast<const char*>(this->data()), size * sizeof(T));
	}

	void DeSerialize(std::istream& InStream)
	{
		this->clear();

		std::int64_t size {};
		InStream.read(reinterpret_cast<char*>(&size), sizeof(size));

		this->resize(size);

		InStream.read(reinterpret_cast<char*>(this->data()), size * sizeof(T));
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

	SerializeableStringView(const T* ntcts)
		: std::basic_string_view<T>(ntcts)
	{
	}

	SerializeableStringView(const std::basic_string<T, std::char_traits<T>>& view)
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