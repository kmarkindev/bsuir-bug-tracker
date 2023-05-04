#pragma once

#include <string>
#include <vector>
#include <BsuirBugTracker/Types.h>

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
