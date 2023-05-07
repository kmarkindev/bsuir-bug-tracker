#pragma once

#include "BsuirBugTracker/Types/Types.h"

String GetExecutablePath(bool& error) noexcept;

String GetExecutableFolder(bool& error) noexcept;

String GetStorageFolder(bool& error) noexcept;

String GetAssetPath(StringView RelativeAssetPath, bool& error) noexcept;

bool DoesAssetExist(StringView RelativeAssetPath, bool& error) noexcept;

void RemoveAsset(StringView RelativeAssetPath, bool& error) noexcept;