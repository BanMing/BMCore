// Copyright BanMing

#include "Events/EventReceiver.h"

void EventReceiver::RemoveAllHandlers()
{
	for (TTuple<size_t, TArray<FEventInfo>>& Pairs : Listeners)
	{
		for (FEventInfo& Info : Pairs.Value)
		{
			Info.Handler = nullptr;
		}
	}
	Listeners.Empty();
	NextEventHandle = 0;
}
