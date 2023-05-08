#include "Storage.h"

void Storage::DeSerialize(std::istream& InStream)
{
	// DeSerialize removes all bugs and creates new ones
	// but we still need to follow bugs lifecycle, so
	// raise all events and call all lifecycle methods

	// Call events before actually deleting bugs
	for(auto& Bug : Bugs)
	{
		OnBugAddOrRemove.RaiseEvent(false, Bug);

		Bug.RemoveBug();
	}

	Bugs.DeSerialize(InStream);

	// Call events after bugs creation
	for(auto& NewBug : Bugs)
	{
		OnBugAddOrRemove.RaiseEvent(true, NewBug);
	}
}

void Storage::Serialize(std::ostream& OutStream) const
{
	Bugs.Serialize(OutStream);
}

const SerializeableList<Bug>& Storage::GetBugs() const
{
	return Bugs;
}

Bug& Storage::AddBug(Bug NewBug)
{
	Bug& InsertedBug = Bugs.emplace_back(std::move(NewBug));

	OnBugAddOrRemove.RaiseEvent(true, InsertedBug);

	return InsertedBug;
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

	if (iter != Bugs.end())
	{
		OnBugAddOrRemove.RaiseEvent(false, *iter);

		iter->RemoveBug();
		Bugs.erase(iter);
	}
	else
	{
		assert(false);
	}
}

Event<bool, Bug&>& Storage::GetOnBugAddOrRemove()
{
	return OnBugAddOrRemove;
}
