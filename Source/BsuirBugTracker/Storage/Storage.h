#pragma once

#include "BsuirBugTracker/Types/Types.h"
#include "Bug.h"

class Storage
{
public:

	void Serialize(std::ostream& OutStream) const;

	void DeSerialize(std::istream& InStream);

	void AddBug(Bug NewBug);

	void RemoveAllBugs();

	void RemoveBug(const Bug& bug);

	[[nodiscard]] const SerializeableList<Bug>& GetBugs() const;

private:

	SerializeableList<Bug> Bugs;

};
