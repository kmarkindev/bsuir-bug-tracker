#include "Types.h"

#include <Windows.h>

String convertFromUtf8(std::string_view utf8String)
{
	String result;

	if (!utf8String.empty())
	{
		int convertResult = MultiByteToWideChar(CP_UTF8, 0, utf8String.data(),
				static_cast<int>(utf8String.size()), nullptr, 0);
		if (convertResult <= 0)
		{
			throw std::runtime_error("Can't convert multi byte string to wide string. Pass #1");
		}
		else
		{
			result.resize(convertResult);
			convertResult = MultiByteToWideChar(CP_UTF8, 0, utf8String.data(),
					static_cast<int>(utf8String.size()),result.data(), static_cast<int>(result.size()));
			if (convertResult <= 0)
			{
				throw std::runtime_error("Can't convert multi byte string to wide string. Pass #2");
			}
		}
	}

	return result;
}