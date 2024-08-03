// Copyright BanMing
#include "StateMachine/StateBase.h"

#include "StateMachine/StateDataBase.h"

UStateBase::UStateBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UStateBase::~UStateBase()
{
}

void UStateBase::Enter(StateDataBase* InCommonData)
{
	CommonData = InCommonData;
	OnEnter();
}

void UStateBase::Tick(float DeltaTime)
{
	OnTick(DeltaTime);
}

void UStateBase::Exit()
{
	OnExit();
	CommonData = nullptr;
}

void UStateBase::TransitionTo(TSubclassOf<UStateBase> NextSubStateBaseClass)
{
	OnTransitionTo.Broadcast(NextSubStateBaseClass);
}
