#include "Storage.h"

void Storage::DeSerialize(std::istream& InStream)
{

}

void Storage::Serialize(std::ostream& OutStream) const
{

}

const SerializeableList<Bug>& Storage::GetBugs() const
{
	return Bugs;
}

void Storage::AddBug(Bug NewBug)
{

}

void Storage::RemoveAllBugs()
{

}

void Storage::RemoveBug(Bug bug)
{

}
