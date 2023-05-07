#pragma once

#include "BsuirBugTracker/Types/SerializedDataTypes.h"
#include <list>

template<IsSerializeable T>
class SerializeableList : public std::list<T>
{
public:

	void Serialize(std::ostream& OutStream) const
	{
		std::uint64_t size = this->size();
		OutStream.write(reinterpret_cast<char*>(&size), sizeof(size));

		for(const auto& item : *this)
		{
			item.Serialize(OutStream);
		}
	}

	void DeSerialize(std::istream& InStream)
	{
		this->clear();

		std::uint64_t size {};
		InStream.read(reinterpret_cast<char*>(&size), sizeof(size));

		// IDE says "Condition is always false" but it's false
		while(size > 0)
		{
			T item {};

			item.DeSerialize(InStream);

			this->emplace_back(std::move(item));

			--size;
		}
	}

};
