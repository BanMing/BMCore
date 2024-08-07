// Copyright BanMing

#include "Events/AsynchronousEventSystem.h"

#include "Events/EventBase.h"

void AsynchronousEventSystem::DispatchEvents()
{
	if (!CacheEvents.IsEmpty())
	{
		EventPoolLock.Lock();
		while (!CacheEvents.IsEmpty())
		{
			CacheEventInfo EventInfo;
			CacheEvents.Dequeue(EventInfo);
			ActiveEvents.Add(MoveTemp(EventInfo));
		}
		EventPoolLock.Unlock();

		// Invoke events
		for (const CacheEventInfo& EventInfo : ActiveEvents)
		{
			if (EventInfo.EventPtr != nullptr && Listeners.Contains(EventInfo.EventKey))
			{
				for (const FEventInfo& Info : Listeners[EventInfo.EventKey])
				{
					if (Info.Handler != nullptr)
					{
						Info.Handler(EventInfo.EventPtr);
					}
				}
			}
		}

		ClearActiveEvents();
	}
}

void AsynchronousEventSystem::Initialize()
{
}

void AsynchronousEventSystem::Destroy()
{
	RemoveAllHandlers();

	ClearActiveEvents();
	ClearCacheEvents();

	EventPoolLock.~FWindowsCriticalSection();
}

void AsynchronousEventSystem::ClearCacheEvents()
{
	EventPoolLock.Lock();
	while (!CacheEvents.IsEmpty())
	{
		CacheEventInfo EventInfo;
		CacheEvents.Dequeue(EventInfo);
		if (EventInfo.EventPtr != nullptr)
		{
			EventInfo.EventPtr->Release();
			delete EventInfo.EventPtr;
		}
	}
	EventPoolLock.Unlock();
}

void AsynchronousEventSystem::ClearActiveEvents()
{
	EventPoolLock.Lock();
	for (const CacheEventInfo& EventInfo : ActiveEvents)
	{
		if (EventInfo.EventPtr != nullptr)
		{
			EventInfo.EventPtr->Release();
			delete EventInfo.EventPtr;
		}
	}
	ActiveEvents.Empty();
	EventPoolLock.Unlock();
}
