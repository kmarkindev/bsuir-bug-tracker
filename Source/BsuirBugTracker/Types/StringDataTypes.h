#pragma once

#include "SerializeableString.h"

// UCS-2 string on Windows
using String = SerializeableString<wchar_t>;
using StringView = SerializeableStringView<wchar_t>;

String convertFromUtf8(std::string_view utf8String);

#define BSUIR_TEXT(text) convertFromUtf8(text)