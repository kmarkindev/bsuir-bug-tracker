#pragma once

#include <string>

using SerializedData = std::basic_string<unsigned char>;
using SerializeDataView = std::basic_string_view<unsigned char>;

template<typename T>
concept IsSerializeable = requires (T t, SerializeDataView dataView) {
	{ std::as_const(t).Serialize() } -> std::same_as<SerializedData>;
	{ t.DeSerialize(dataView) } -> std::same_as<void>;
};