#pragma once

#include <BsuirBugTracker/Types.h>

class Attachment
{

public:

	[[nodiscard]] SerializedData Serialize() const;

	void DeSerialize(SerializeDataView dataView);

};
