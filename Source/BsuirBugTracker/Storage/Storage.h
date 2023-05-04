#pragma once

#include <BsuirBugTracker/Types/Types.h>

class Storage
{
public:

	void Serialize(std::ostream& OutStream) const;

	void DeSerialize(std::istream& InStream);

};
