// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "EventReceiver.h"
#include "IEventSystem.h"

#include <iostream>
#include <memory>
#include <typeinfo>

struct FEventBase;

class BMCORE_API SynchronousEventSystem : public EventReceiver, public IEventSystem
{
public:
	// Boradcast the event immediately
	// The Event point will be deleted automatic
	template <typename TEvent = FEventBase>
	void Boradcast(TEvent* EventPtr)
	{
		size_t Key = typeid(TEvent).hash_code();
		if (Listeners.Contains(Key))
		{
			for (const FEventInfo& Info : Listeners[Key])
			{
				if (Info.Handler != nullptr)
				{
					Info.Handler(EventPtr);
				}
			}
		}
		EventPtr->Release();
		delete EventPtr;
	}

	// Inherited via IEventSystem
	virtual void Initialize() override;
	virtual void Destroy() override;
};