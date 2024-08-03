// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
class EventBase;

template <typename TEvent>
using EventHandler = void (*)(const TEvent&);

// Event broadcaster can send events.
class BMCORE_API IEventBroadcaster
{
public:
	virtual void Post(EventBase evt) = 0;
};

// Event receiver supports event listeners (think of it like a radio receiver)
template <typename TEvent>
class BMCORE_API IEventReceiver
{
public:
	virtual void AddHandler(EventHandler<TEvent> handler) = 0;

	virtual void RemoveHandler(EventHandler<TEvent> handler)=0;

	virtual void RemoveAllHandlers() = 0;
};

 //An event "system" is both a broadcaster and a receiver.
template <typename TEvent>
class BMCORE_API IEventSystem : public IEventBroadcaster, public IEventReceiver<TEvent>
{
};
