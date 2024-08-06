// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "EventReceiver.h"
#include "IEventSystem.h"

#include <iostream>
#include <memory>
#include <typeinfo>
/**
 *	-----------------------------------------------------------------------------------------------
 *	Create New Event System:
 *
 *	AsyncEventSystem = new AsynchronousEventSystem();
 *	-----------------------------------------------------------------------------------------------
 *	Add Listener:
 *
 *	AsyncEventSystem->AddHandler<TestEvent>(this, &ThisClass::OnTestEvet);
 *	-----------------------------------------------------------------------------------------------
 *	Boradcast:
 *
 *	TestEvent Agrs;
 *	Agrs.data = 3;
 *	AsyncEventSystem->Boradcast(Agrs);
 *	-----------------------------------------------------------------------------------------------
 *	The real broadcast event, which should be called in the Tick method:
 *
 *	AsyncEventSystem->DispatchEvents();
 *
 */
struct FEventBase;

class BMCORE_API AsynchronousEventSystem : public EventReceiver, public IEventSystem
{
private:
	struct CacheEventInfo
	{
		FEventBase* EventBase;
		size_t EventKey;
	};

public:
	void DispatchEvents();

	// Inherited via IEventSystem
	virtual void Initialize() override;
	virtual void Destroy() override;

	template <typename TEvent = FEventBase>
	void Boradcast(TEvent& Event)
	{
		size_t Key = typeid(TEvent).hash_code();
		if (Listeners.Contains(Key))
		{
			EventPoolLock.Lock();
			CacheEvents.Enqueue({&Event, Key});
			EventPoolLock.Unlock();
		}
	}

private:
	TQueue<CacheEventInfo> CacheEvents;
	TArray<CacheEventInfo> ActiveEvents;
	FCriticalSection EventPoolLock;
};