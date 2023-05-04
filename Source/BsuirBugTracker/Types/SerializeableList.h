#pragma once

#include "BsuirBugTracker/Types/SerializedDataTypes.h"

template<IsSerializeable T>
class SerializeableList : public std::vector<T>
{
public:

	[[nodiscard]] SerializedData Serialize() const
	{
		return {};
	}

	void DeSerialize(SerializeDataView SerializeDataView)
	{

	}

};
