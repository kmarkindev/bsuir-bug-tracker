#include "StorageHelpers.h"

#include <Windows.h>
#include "Shlwapi.h"
#include "winbase.h"

String GetExecutablePath(bool& error) noexcept
{
	error = false;

	String result(MAX_PATH, L'\0');

	int res = GetModuleFileName(nullptr, result.data(), static_cast<DWORD>(result.size()));

	if(res == 0)
	{
		error = true;
		result.clear();
	}

	return result;
}

String GetExecutableFolder(bool& error) noexcept
{
	error = false;

	String exePath = GetExecutablePath(error);

	if(error)
		return {};

	auto index = exePath.find_last_of(L'\\');

	if(index == String::npos)
	{
		error = true;
		return {};
	}

	exePath.erase(index, exePath.size() - index);

	return exePath;
}

String GetStorageFolder(bool& error) noexcept
{
	error = false;

	String folder = GetExecutableFolder(error);

	if(error)
		return {};

	//folder += L"\\Storage";

	return folder;
}

String GetAssetPath(StringView RelativeAssetPath, bool& error) noexcept
{
	error = false;

	String path = GetStorageFolder(error);

	if(error)
		return {};

	path += L'\\';
	path += RelativeAssetPath;

	return path;
}

bool DoesAssetExist(StringView RelativeAssetPath, bool& error) noexcept
{
	error = false;

	String fullPath = GetAssetPath(RelativeAssetPath, error);

	if(error)
		return false;

	BOOL result = PathFileExists(fullPath.c_str());

	return result == TRUE;
}

void RemoveAsset(StringView RelativeAssetPath, bool& error) noexcept
{
	error = false;

	String fullPath = GetAssetPath(RelativeAssetPath, error);

	if(error)
		return;

	BOOL result = DeleteFile(fullPath.c_str());

	error = result == TRUE;
}