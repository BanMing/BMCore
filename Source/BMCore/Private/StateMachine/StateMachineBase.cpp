// Copyright BanMing

#include "StateMachine/StateMachineBase.h"

#include "StateMachine/StateBase.h"
#include "StateMachine/StateDataBase.h"

#include <iostream>
#include <typeinfo>

template <typename TStateData>
StateMachineBase<TStateData>::StateMachineBase(TStateData* InFSMData) : FSMData(InFSMData)
{
	OnInitialize();
}

template <typename TStateData>
StateMachineBase<TStateData>::~StateMachineBase()
{
	if (FSMData != nullptr)
	{
		FSMData->Release();
		delete FSMData;
		FSMData = nullptr;
	}
	OnDestroy();
}

template <typename TStateData>
void StateMachineBase<TStateData>::StartFSM(StateBase<TStateData>* InitState)
{
	OnStarting();
	ForceTransitionTo(InitState);
	OnStarted();
}

template <typename TStateData>
void StateMachineBase<TStateData>::StopFSM()
{
	OnStopping();

	ExecuteStateTransition();

	OnStopped();
}

template <typename TStateData>
void StateMachineBase<TStateData>::Suspend()
{
	bIsSuspended = true;
}

template <typename TStateData>
void StateMachineBase<TStateData>::Resume()
{
	bIsSuspended = false;
}

template <typename TStateData>
void StateMachineBase<TStateData>::Tick(float DeltaTime)
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

template <typename TStateData>
void StateMachineBase<TStateData>::ResetFSM()
{
	FSMData->Reset();
}

template <typename TStateData>
TStateData* StateMachineBase<TStateData>::GetCurrentState()
{
	return CurrentState;
}

template <typename TStateData>
void StateMachineBase<TStateData>::ForceTransitionTo(StateBase<TStateData>* ToState)
{
	TransitionStateTo(ToState);
	ExecuteStateTransition();
}

template <typename TStateData>
void StateMachineBase<TStateData>::ExecuteStateTransition()
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
	CurrentState->OnTransitionTo.AddRaw(this, &StateMachineBase<TStateData>::TransitionStateTo);

	CurrentState->Enter(FSMData);
	OnPostStateTransition.Broadcast(FromState, ToState);

	// Destroy Old State
	if (FromState != nullptr)
	{
		FromState->OnTransitionTo.Clear();
		delete FromState;
		FromState = nullptr;
	}
}

template <typename TStateData>
void StateMachineBase<TStateData>::TransitionStateTo(StateBase<TStateData>* ToState)
{
	TargetState = ToState;
}
