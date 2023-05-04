#pragma once

#include "BsuirBugTracker/Types/SerializedDataTypes.h"

template<IsSerializeable T>
class SerializeableList : public std::vector<T>
{
public:

	void Serialize(std::ostream& OutStream) const
	{

	}

	void DeSerialize(std::istream& InStream)
	{

	}

};
