// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "IEventSystem.h"
class EventBase;
// class IEventSystem;
/**
 *
 */
// template <typename TEvent>
class BMCORE_API SynchronousEventSystem	   //: public IEventSystem<TEvent>
{
public:
	template <typename TEvent>
	void AddHandler(EventHandler<TEvent> handler);

#pragma region Nested Classes
private:
	class EventPosterBase
	{
	};
	template <typename TEvent>
	class EventPoster
	{
	public:
		bool IsEmpty()
		{
			return Listeners.IsEmpty();
		}

		int ReceiverCount()
		{
			return Listeners.Num();
		}
		void DeliverEvent(TEvent evt)
		{
			for (EventHandler<TEvent> handler : Listeners)
			{
				if (handler != nullptr)
				{
					handler(evt);
				}
			}
		}

	private:
		TArray<EventHandler<TEvent>> Listeners;
	};
#pragma endregion
private:
	TMap<TSubclassOf<EventBase>, EventPosterBase> Handles;
};

template <typename TEvent>
inline void SynchronousEventSystem::AddHandler(EventHandler<TEvent> handler)
{
	EventPosterBase* Poster = Handles.Find(TEvent::StaticClass());
	if (Poster == nullptr)
	{
		Poster = New<EventPoster<TEvent>>();
		Handles[TEvent::StaticClass()] = Poster;
	}
}
