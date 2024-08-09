// Copyright BanMing

#include "StateMachine/StateBase.h"

#include "StateMachine/StateDataBase.h"

StateBase::StateBase(bool InbIsReusing) : bIsReusing(InbIsReusing)
{
}

StateBase::~StateBase()
{
	CommonData = nullptr;
}

void StateBase::Enter(FStateDataBase* InCommonData)
{
	CommonData = InCommonData;
	OnEnter();
}

void StateBase::Tick(float DeltaTime)
{
	OnTick(DeltaTime);
}

void StateBase::Exit()
{
	OnExit();
	CommonData = nullptr;
}
