#pragma once

#include <istream>
#include <ostream>

template<typename T>
concept IsSerializeable = requires (T t, std::ostream& ostream, std::istream& istream) {
	{ std::as_const(t).Serialize(ostream) } -> std::same_as<void>;
	{ t.DeSerialize(istream) } -> std::same_as<void>;
};

inline void SerializeInteger(std::ostream& OutStream, std::int32_t ToSerialize)
{
	OutStream.write(reinterpret_cast<char*>(&ToSerialize), sizeof(ToSerialize));
}

inline std::int32_t DeSerializeInteger(std::istream& InStream)
{
	std::int32_t Result {};
	InStream.read(reinterpret_cast<char*>(&Result), sizeof(Result));

	return Result;
}