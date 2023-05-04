#pragma once

#include <string>
#include <cstdint>
#include <chrono>
#include <type_traits>
#include <vector>
#include <stdexcept>

// UCS-2 string on Windows
using String = std::wstring;

// String of bytes ready to be written on disk
using SerializedData = std::basic_string<unsigned char>;

using SerializeDataView = std::basic_string_view<unsigned char>;

// UNIX Timestamp in seconds
using Timestamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;

// Check if type is serializeable
template<typename T>
concept IsSerializeable = requires (T t, SerializeDataView dataView) {
	{ std::as_const(t).Serialize() } -> std::same_as<SerializedData>;
	{ t.DeSerialize(dataView) } -> std::same_as<void>;
};

String convertFromUtf8(std::string_view utf8String);

#define BSUIR_TEXT(text) convertFromUtf8(text)