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
		FEventBase* EventPtr;
		size_t EventKey;
	};

public:
	void DispatchEvents();

	// Inherited via IEventSystem
	virtual void Initialize() override;
	virtual void Destroy() override;

	// The Event point will be deleted automatic 
	template <typename TEvent = FEventBase>
	void Boradcast(TEvent* EventPtr)
	{
		size_t Key = typeid(TEvent).hash_code();
		if (Listeners.Contains(Key))
		{
			EventPoolLock.Lock();
			CacheEvents.Enqueue({EventPtr, Key});
			EventPoolLock.Unlock();
		}
	}

protected:
	void ClearCacheEvents();
	void ClearActiveEvents();

private:
	TQueue<CacheEventInfo> CacheEvents;
	TArray<CacheEventInfo> ActiveEvents;
	FCriticalSection EventPoolLock;
};