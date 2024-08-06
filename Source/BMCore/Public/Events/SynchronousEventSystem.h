// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "IEventSystem.h"
#include "EventReceiver.h"

#include <iostream>
#include <memory>
#include <typeinfo>

struct FEventBase;

class BMCORE_API SynchronousEventSystem : public EventReceiver, public IEventSystem
{
public:
	// Boradcast the event immediately
	template <typename TEvent = FEventBase>
	void Boradcast(TEvent& Event)
	{
		size_t Key = typeid(TEvent).hash_code();
		if (Listeners.Contains(Key))
		{
			for (const FEventInfo& Info : Listeners[Key])
			{
				if (Info.Handler != nullptr)
				{
					Info.Handler(&Event);
				}
			}
		}
	}

	// Inherited via IEventSystem
	virtual void Initialize() override;
	virtual void Destroy() override;
};