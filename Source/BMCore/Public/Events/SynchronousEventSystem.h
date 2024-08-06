// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "IEventSystem.h"

#include <functional>
#include <iostream>
#include <memory>
#include <typeinfo>

struct FEventBase;

class BMCORE_API SynchronousEventSystem
{
private:
	struct EventInfo
	{
		std::function<void(void*)> Handler;
		EventHandle Handle;
	};

public:
	// Add an event handler for events of a specified type.
	// Note that handler will also be invoked when events derived
	// from TEvent are posted. A handler added for FEventBase will
	// be invoked for all events.
	template <typename TEvent = FEventBase, typename UserClass>
	EventHandle AddHandler(UserClass* ListenerObj, typename TMemFunPtrType<false, UserClass, void(TEvent&)>::Type InFunc)
	{
		size_t Key = typeid(TEvent).hash_code();
		EventHandle Handle = NextEventHandle++;
		auto Wrapper = [ListenerObj, InFunc](void* Event)
		{
			if (ListenerObj != nullptr)
			{
				// Type conversion is performed here, and if the current event is extremely performance - critical,
				// it is recommended to use UE's own FDelegat
				(ListenerObj->*InFunc)(*static_cast<TEvent*>(Event));
			}
		};
		if (Listeners.Contains(Key))
		{
			Listeners[Key].Add({Wrapper, Handle});
		}
		else
		{
			Listeners.Add(Key, {{Wrapper, Handle}});
		}
		return Handle;
	}

	// Remove an event handler.
	template <typename TEvent = FEventBase>
	void RemoveHandler(EventHandle Handle)
	{
		size_t Key = typeid(TEvent).hash_code();
		if (Listeners.Contains(Key))
		{
			Listeners[Key].RemoveAllSwap([Handle](const EventInfo& Info) { return Handle = Info.Handle; });
		}
	}

	void RemoveAllHandlers()
	{
		for (TTuple<size_t, TArray<EventInfo>>& Pairs : Listeners)
		{
			for (EventInfo& Info : Pairs.Value)
			{
				Info.Handler = nullptr;
			}
		}
		Listeners.Empty();
		NextEventHandle = 0;
	}

	// Boradcast the event immediately
	template <typename TEvent = FEventBase>
	void Boradcast(TEvent& Event)
	{
		size_t Key = typeid(TEvent).hash_code();
		if (Listeners.Contains(Key))
		{
			for (const EventInfo& Info : Listeners[Key])
			{
				if (Info.Handler != nullptr)
				{
					Info.Handler(&Event);
					Event.Release();
				}
			}
		}
	}

private:
	TMap<size_t, TArray<EventInfo>> Listeners;
	EventHandle NextEventHandle = 0;
};