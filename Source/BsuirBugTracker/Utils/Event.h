#pragma once

#include <functional>
#include <cassert>

template<typename... Arguments>
class Event
{
	using CallbackType = std::function<void(Arguments...)>;

	struct SavedCallback
	{
		size_t id {};
		CallbackType Callback {};

		bool operator == (size_t IdToCheck)
		{
			return id == IdToCheck;
		}
	};

public:

	Event() = default;

	Event(const Event&) = delete;

	Event(Event&& Other) noexcept = default;

	Event& operator=(const Event&) = delete;

	Event& operator=(Event&& Other) noexcept = default;

	~Event() = default;

	size_t AddCallback(CallbackType Callback)
	{
		size_t Index = LastCallbackIndex++;

		Callbacks.push_back({
			Index,
			std::move(Callback)
		});

		return Index;
	}

	void RemoveCallback(size_t Index)
	{
		auto RemoveIter = std::remove(Callbacks.begin(), Callbacks.end(), Index);
		Callbacks.erase(RemoveIter, Callbacks.end());
	}

	void RaiseEvent(Arguments ... Args) const
	{
		for(const auto& SavedCallback : Callbacks)
		{
			if(SavedCallback.Callback)
			{
				SavedCallback.Callback(Args...);
			}
			else
			{
				assert(false);
			}
		}
	}

private:

	// start counting from 1 to allow to do null checks based on zero value
	size_t LastCallbackIndex { 1 };

	std::vector<SavedCallback> Callbacks {};

};