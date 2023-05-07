#pragma once

#include <combaseapi.h>
#include <cassert>
#include "BsuirBugTracker/Types/Types.h"

inline String GenerateGuid()
{
	GUID GeneratedGuid {};
	if(CoCreateGuid(&GeneratedGuid) != S_OK)
	{
		assert(false);

		return {};
	}

	wchar_t szGUID[64] = {0};
	if(StringFromGUID2(GeneratedGuid, szGUID, 64) == 0)
	{
		assert(false);

		return {};
	}

	return String { szGUID };
}