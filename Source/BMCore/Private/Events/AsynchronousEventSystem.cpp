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
			if (EventInfo.EventBase != nullptr && Listeners.Contains(EventInfo.EventKey))
			{
				for (const FEventInfo& Info : Listeners[EventInfo.EventKey])
				{
					if (Info.Handler != nullptr)
					{
						Info.Handler(EventInfo.EventBase);
					}
				}
			}
		}

		EventPoolLock.Lock();
		ActiveEvents.Empty();
		EventPoolLock.Unlock();
	}
}

void AsynchronousEventSystem::Initialize()
{
}

void AsynchronousEventSystem::Destroy()
{
	RemoveAllHandlers();

	EventPoolLock.Lock();
	CacheEvents.Empty();
	ActiveEvents.Empty();
	EventPoolLock.Unlock();

	EventPoolLock.~FWindowsCriticalSection();
}
