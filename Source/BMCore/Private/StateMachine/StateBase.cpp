// Copyright BanMing
#include "StateMachine/StateBase.h"

#include "StateMachine/StateDataBase.h"

template <typename TStateData>
UStateBase<TStateData>::~UStateBase()
{
	CommonData = nullptr;
}

template <typename TStateData>
void UStateBase<TStateData>::Enter(TStateData* InCommonData)
{
	CommonData = InCommonData;
	OnEnter();
}

template <typename TStateData>
void UStateBase<TStateData>::Tick(float DeltaTime)
{
	OnTick(DeltaTime);
}

template <typename TStateData>
void UStateBase<TStateData>::Exit()
{
	OnExit();
	CommonData = nullptr;
}
