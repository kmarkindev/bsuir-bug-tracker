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
	Bugs.emplace_back(std::move(NewBug));
}

void Storage::RemoveAllBugs()
{
	for(auto& Bug : Bugs)
	{
		Bug.RemoveBug();
	}

	Bugs.clear();
}

void Storage::RemoveBug(const Bug& Bug)
{
	auto iter = std::find(Bugs.begin(), Bugs.end(), Bug);

	if(iter != Bugs.end())
	{
		iter->RemoveBug();
		Bugs.erase(iter);
	}
}
