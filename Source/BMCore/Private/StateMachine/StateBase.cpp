// Copyright BanMing

#include "StateMachine/StateBase.h"

#include "StateMachine/StateDataBase.h"

template <typename TStateData>
StateBase<TStateData>::StateBase(bool InbIsReusing) : bIsReusing(InbIsReusing)
{
	OnInitialize();
}

template <typename TStateData>
StateBase<TStateData>::~StateBase()
{
	CommonData = nullptr;
	OnDestroy();
}

template <typename TStateData>
void StateBase<TStateData>::Enter(TStateData* InCommonData)
{
	CommonData = InCommonData;
	OnEnter();
}

template <typename TStateData>
void StateBase<TStateData>::Tick(float DeltaTime)
{
	OnTick(DeltaTime);
}

template <typename TStateData>
void StateBase<TStateData>::Exit()
{
	OnExit();
	CommonData = nullptr;
}
