#include "Storage.h"

void Storage::DeSerialize(std::istream& InStream)
{
	Bugs.DeSerialize(InStream);
}

void Storage::Serialize(std::ostream& OutStream) const
{
	Bugs.Serialize(OutStream);
}

const SerializeableList<Bug>& Storage::GetBugs() const
{
	return Bugs;
}

void Storage::AddBug(Bug NewBug)
{
	Bug& InsertedBug = Bugs.emplace_back(std::move(NewBug));

	OnBugAddOrRemove.RaiseEvent(true, InsertedBug);
}

void Storage::RemoveAllBugs()
{
	for(auto& Bug : Bugs)
	{
		OnBugAddOrRemove.RaiseEvent(false, Bug);

		Bug.RemoveBug();
	}

	Bugs.clear();
}

void Storage::RemoveBug(const Bug& Bug)
{
	auto iter = std::find(Bugs.begin(), Bugs.end(), Bug);

	if(iter != Bugs.end())
	{
		OnBugAddOrRemove.RaiseEvent(false, *iter);

		iter->RemoveBug();
		Bugs.erase(iter);
	}
}

Event<bool, Bug&>& Storage::GetOnBugAddOrRemove()
{
	return OnBugAddOrRemove;
}
