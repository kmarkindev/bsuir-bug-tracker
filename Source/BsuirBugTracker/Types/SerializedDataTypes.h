#pragma once

#include <istream>
#include <ostream>

template<typename T>
concept IsSerializeable = requires (T t, std::ostream& ostream, std::istream& istream) {
	{ std::as_const(t).Serialize(ostream) } -> std::same_as<void>;
	{ t.DeSerialize(istream) } -> std::same_as<void>;
};