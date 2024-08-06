// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "IEventSystem.h"

#include <functional>
#include <iostream>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>
class BMCORE_API NativeEventSystem
{
private:
	using ListenerID = size_t;
	struct ListenerInfo
	{
		std::function<void(const void*)> Listener;
		ListenerID ID;
		const void* ListenerObj;
	};
	std::unordered_map<std::type_index, std::vector<ListenerInfo>> Listeners;
	ListenerID NextListenerID = 0;

public:
	template <typename TEvent>
	ListenerID RegisterListener(const void* ListenerObj, const std::function<void(const TEvent&)>& Func)
	{
		auto Key = std::type_index(typeid(TEvent));
		auto ID = NextListenerID++;
		auto Wrapper = [Func, ID](const void* Event) { Func(*static_cast<const TEvent*>(Event)); };
		ListenerInfo Info{Wrapper, ID, ListenerObj};
		Listeners[Key].push_back(Info);
		return ID;
	}

	template <typename TEvent>
	void RemoveListener(ListenerID ID)
	{
		auto Key = std::type_index(typeid(TEvent));
		if (Listeners.find(Key) != Listeners.end())
		{
			auto& Vec = Listeners[Key];
			Vec.erase(std::remove_if(Vec.begin(), Vec.end(), [ID](const ListenerInfo& Info) { return Info.ID = ID; }), Vec.end());
			if (Vec.empty())
			{
				Listeners.erase(Key);
			}
		}
	}

	template <typename TEvent>
	void TriggerEvent(const TEvent& Event)
	{
		auto Key = std::type_index(typeid(TEvent));
		if (Listeners.find(Key) != Listeners.end())
		{
			for (const auto& Info : Listeners[Key])
			{
				if (Info.ListenerObj)
				{
					Info.Listener(&Event);
				}
			}
		}
	}
};