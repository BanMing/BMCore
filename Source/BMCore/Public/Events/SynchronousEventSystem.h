// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "IEventSystem.h"
// class EventBase;
//// class IEventSystem;
///**
// *
// */
//// template <typename TEvent>
// class BMCORE_API SynchronousEventSystem	   //: public IEventSystem<TEvent>
//{
// public:
//	//template <typename TEvent>
//	//void AddHandler(EventHandler<TEvent> handler);
//
// #pragma region Nested Classes
// private:
//	class EventPosterBase
//	{
//	};
//	template <typename TEvent>
//	class EventPoster
//	{
//	public:
//		bool IsEmpty()
//		{
//			return Listeners.IsEmpty();
//		}
//
//		int ReceiverCount()
//		{
//			return Listeners.Num();
//		}
//		void DeliverEvent(TEvent evt)
//		{
//			for (EventHandler<TEvent> handler : Listeners)
//			{
//				if (handler != nullptr)
//				{
//					handler(evt);
//				}
//			}
//		}
//
//	private:
//		TArray<EventHandler<TEvent>> Listeners;
//	};
// #pragma endregion
// private:
//	TMap<TSubclassOf<EventBase>, EventPosterBase> Handles;
// };

// template <typename TEvent>
// inline void SynchronousEventSystem::AddHandler(EventHandler<TEvent> handler)
//{
//	EventPosterBase* Poster = Handles.Find(TEvent::StaticClass());
//	if (Poster == nullptr)
//	{
//		Poster = New<EventPoster<TEvent>>();
//		Handles[TEvent::StaticClass()] = Poster;
//	}
// }
// class IDelegate
//{
// public:
//	template <typename... ParamTypes>
//	 void Broadcast(int32 EventId, ParamTypes... Params);
//
//	 virtual bool IsLocalBound()=0;
//};
//
// template <typename RetValType, typename... ParamTypes>
// class TMyMulticastDelegate : public TMulticastDelegate<RetValType(ParamTypes...), FDefaultDelegateUserPolicy>, public IDelegate
//{
// public:
//	 virtual bool IsLocalBound() override
//	 {
//		 return IsBound();
//	 };
//};
//
// class BMCORE_API SynchronousEventSystem
//{
//	// using FMulticastDelegateExtras = TMulticastDelegateBase<FDefaultDelegateUserPolicy>;
//
// public:
//	// SynchronousEventSystem() = default;
//	template <typename TMulticastDelegate, typename UserClass, typename... VarTypes>
//	inline FDelegateHandle AddUObject(int32 EventId, UserClass* InUserObject, typename TMemFunPtrType<false, UserClass, void(int32, std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
//	{
//		/*if (Listenters.Contains(EventId))
//		{
//			if (!Listenters[EventId].IsBoundToObject(InUserObject))
//			{
//				Listenters[EventId].AddDelegateInstance(TMulticastDelegate.FDelegate::CreateRaw(InUserObject, InFunc, Forward<VarTypes>(Vars)...));
//			}
//		}*/
//		TMulticastDelegate NewMulticastDelegateIns;
//		FDelegateHandle Handle = NewMulticastDelegateIns.AddUObject(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
//		Listenters.Add(EventId, NewMulticastDelegateIns);
//		return Handle;
//	}
//
//	// void RemoveHandler(){};
//
//	// template <typename TMulticastDelegate, typename... ParamTypes>
//	// inline void Broadcast(int32 EventId, ParamTypes... Params){
//	//	/*	if (Listenters.Contains(EventId) && Listenters[EventId].IsBound())
//	//		{
//	//			Listenters[EventId].Broadcast(Params...);
//	//		}*/
//	// };
//
//	template <typename... ParamTypes>
//	inline void Broadcast(int32 EventId, ParamTypes... Params)
//	{
//		if (Listenters.Contains(EventId) && Listenters[EventId].IsLocalBound())
//		{
//			Listenters[EventId].Broadcast(Params...);
//		}
//	};
//
// public:
//	TMap<int32, IDelegate> Listenters;
//	// TMulticastDelegateBase<UserPolicy> Test;
//	// UserPolicy Test;
//	// TMulticastDelegateBase<FDefaultDelegateUserPolicy> Test;
//};
//// typedef SynchronousEventSystem<FDefaultDelegateUserPolicy> TestSynchronousEventSystem;

// class BMCORE_API SynchronousEventSystem
//{
// public:
//	enum EeventID
//	{
//		TestEvent1,
//		TestEvent2,
//	};
//
// public:
//	template <typename... ParamTypes>
//	void Boradcast(EeventID ID, ParamTypes... Params)
//	{
//		OnTestDelegeate.Broadcast(Params...);
//	}
//
// protected:
//	DECLARE_MULTICAST_DELEGATE_OneParam(FTestDelegeate, int32);
//	FTestDelegeate OnTestDelegeate;
// };
#include <functional>
#include <iostream>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>
class BMCORE_API SynchronousEventSystem
{
private:
	using ListenerID = size_t;
	struct ListenerInfo
	{
		std::function<void(const void*)> Listener;
		ListenerID ID;
		/*std::weak_ptr<void>*/ const void* ListenerObj;
	};
	std::unordered_map<std::type_index, std::vector<ListenerInfo>> Listeners;
	ListenerID NextListenerID = 0;

public:
	template <typename TEvent>
	ListenerID RegisterListener(const void* ListenerObj, const std::function<void(const TEvent&)>& Func)
	{
		auto Key = std::type_index(typeid(TEvent));
		auto ID = NextListenerID++;
		auto Wrapper = [Func, ID](const void* Event) { Func(*static_cast<const TEvent*>(Event)); };
		ListenerInfo Info{Wrapper, ID, ListenerObj};
		Listeners[Key].push_back(Info);
		return ID;
	}

	template <typename TEvent>
	void RemoveListener(ListenerID ID)
	{
		auto Key = std::type_index(typeid(TEvent));
		if (Listeners.find(Key) != Listeners.end())
		{
			auto& Vec = Listeners[Key];
			Vec.erase(std::remove_if(Vec.begin(), Vec.end(), [ID](const ListenerInfo& Info) { return Info.ID = ID; }), Vec.end());
			if (Vec.empty())
			{
				Listeners.erase(Key);
			}
		}
	}

	void RemoveListener(const void* ListenerObj)
	{
	}

	template <typename TEvent>
	void TriggerEvent(const TEvent& Event)
	{
		auto Key = std::type_index(typeid(TEvent));
		if (Listeners.find(Key) != Listeners.end())
		{
			for (const auto& Info : Listeners[Key])
			{
				if (Info.ListenerObj)
				{
					Info.Listener(&Event);
				}
			}
		}
	}
};