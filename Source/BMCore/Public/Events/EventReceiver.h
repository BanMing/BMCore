// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "IEventSystem.h"

struct FEventBase;

// Event receiver supports event listeners (think of it like a radio receiver)
class BMCORE_API EventReceiver
{
public:
	// Add an event handler for events of a specified type.
	// Note that handler will also be invoked when events derived
	// from TEvent are posted. A handler added for FEventBase will
	// be invoked for all events.
	template <typename TEvent = FEventBase, typename UserClass>
	FEventHandle AddHandler(UserClass* ListenerObj, typename TMemFunPtrType<false, UserClass, void(const TEvent&)>::Type InFunc)
	{
		size_t Key = typeid(TEvent).hash_code();
		FEventHandle Handle = NextEventHandle++;
		auto Wrapper = [ListenerObj, InFunc](FEventBase* Event)
		{
			if (ListenerObj != nullptr)
			{
				// Type conversion is performed here, and if the current event is extremely performance - critical,
				// it is recommended to use UE's FDelegate
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

	template <typename TEvent = FEventBase, typename FunctorType>
	FEventHandle AddHandler(FunctorType&& InFunc)
	{
		size_t Key = typeid(TEvent).hash_code();
		FEventHandle Handle = NextEventHandle++;
		auto Wrapper = [InFunc](FEventBase* Event)
		{
			// Type conversion is performed here, and if the current event is extremely performance - critical,
			// it is recommended to use UE's FDelegate
			InFunc(*static_cast<TEvent*>(Event));
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
	void RemoveHandler(FEventHandle Handle)
	{
		size_t Key = typeid(TEvent).hash_code();
		if (Listeners.Contains(Key))
		{
			Listeners[Key].RemoveAllSwap([Handle](const FEventInfo& Info) { return Handle = Info.Handle; });
		}
	}

	void RemoveAllHandlers();

protected:
	TMap<size_t, TArray<FEventInfo>> Listeners;
	FEventHandle NextEventHandle = 0;
};