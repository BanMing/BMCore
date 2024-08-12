// Copyright BanMing

#include "StateMachine/StateMachineBase.h"

#include "StateMachine/StateBase.h"
#include "StateMachine/StateDataBase.h"

#include <iostream>
#include <typeinfo>

StateMachineBase::StateMachineBase(FStateDataBase* InFSMData) : FSMData(InFSMData)
{
}

StateMachineBase::~StateMachineBase()
{
	if (FSMData != nullptr)
	{
		FSMData->Release();
		delete FSMData;
		FSMData = nullptr;
	}
}

void StateMachineBase::StartFSM(StateBase* InitState)
{
	OnStarting();
	ForceTransitionTo(InitState);
	OnStarted();
}

void StateMachineBase::StopFSM()
{
	OnStopping();

	TargetState = nullptr;
	ExecuteStateTransition();

	OnStopped();
}

void StateMachineBase::Suspend()
{
	bIsSuspended = true;
}

void StateMachineBase::Resume()
{
	bIsSuspended = false;
}

void StateMachineBase::Tick(float DeltaTime)
{
	if (!bIsSuspended)
	{
		CurrentState->Tick(DeltaTime);
	}

	// Pending state transition? execute it!
	if (TargetState != nullptr)
	{
		ExecuteStateTransition();
	}
}

void StateMachineBase::ResetFSM()
{
	FSMData->Reset();
}

StateBase* StateMachineBase::GetCurrentState()
{
	return CurrentState;
}

void StateMachineBase::ForceTransitionTo(StateBase* ToState)
{
	TransitionStateTo(ToState);
	ExecuteStateTransition();
}

void StateMachineBase::ExecuteStateTransition()
{
	StateBase* FromState = CurrentState;
	StateBase* ToState = TargetState;
	TargetState = nullptr;

	OnPreStateTransition.Broadcast(FromState, ToState);

	if (FromState != nullptr)
	{
		FromState->Exit();
	}

	CurrentState = ToState;
	if (CurrentState != nullptr)
	{
		CurrentState->OnTransitionTo.AddRaw(this, &StateMachineBase::TransitionStateTo);

		CurrentState->Enter(FSMData);
		OnPostStateTransition.Broadcast(FromState, ToState);
	}

	// Destroy Old State
	if (FromState != nullptr)
	{
		FromState->OnTransitionTo.Clear();
		delete FromState;
		FromState = nullptr;
	}
}

void StateMachineBase::TransitionStateTo(StateBase* ToState)
{
	TargetState = ToState;
}
