// Copyright BanMing

#include "StateMachine/StateMachineBase.h"

#include "StateMachine/StateBase.h"
#include "StateMachine/StateDataBase.h"

#include <iostream>
#include <typeinfo>

template <typename TStateData>
bool UStateMachineBase<TStateData>::IsIdleState(UStateBase<TStateData>* State)
{
	return typeid(*State) == typeid(UDefaultIdleState);
}

template <typename TStateData>
UStateMachineBase<TStateData>::UStateMachineBase(TStateData* InFSMData) : FSMData(InFSMData)
{
	CurrentState = kDefaultIdleState;
}

template <typename TStateData>
UStateMachineBase<TStateData>::~UStateMachineBase()
{
	if (FSMData != nullptr)
	{
		FSMData->Release();
		delete FSMData;
		FSMData = nullptr;
	}
}

template <typename TStateData>
void UStateMachineBase<TStateData>::StartFSM(UStateBase<TStateData>* InitState)
{
	OnStarting();
	ForceTransitionTo(InitState);
	OnStarted();
}

template <typename TStateData>
void UStateMachineBase<TStateData>::StopFSM()
{
	OnStopping();

	TransitionStateTo(UDefaultIdleState::StaticClass());
	ExecuteStateTransition();

	OnStopped();
}

template <typename TStateData>
void UStateMachineBase<TStateData>::Suspend()
{
	bIsSuspended = true;
}

template <typename TStateData>
void UStateMachineBase<TStateData>::Resume()
{
	bIsSuspended = false;
}

template <typename TStateData>
void UStateMachineBase<TStateData>::Tick(float DeltaTime)
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
void UStateMachineBase<TStateData>::ResetFSM()
{
	CurrentState = kDefaultIdleState;
	FSMData->Reset();
}

template <typename TStateData>
void UStateMachineBase<TStateData>::ForceTransitionTo(UStateBase<TStateData>* ToState)
{
	TransitionStateTo(ToState);
	ExecuteStateTransition();
}

template <typename TStateData>
void UStateMachineBase<TStateData>::ExecuteStateTransition()
{
	UStateBase* FromState = CurrentState;
	UStateBase* ToState = TargetState;
	TargetState = nullptr;

	OnPreStateTransition.Broadcast(FromState, ToState);

	FromState->Exit();
	CurrentState = ToState;
	CurrentState->OnTransitionTo.AddRaw(this, &UStateMachineBase<TStateData>::TransitionStateTo);

	CurrentState->Enter(FSMData);
	OnPostStateTransition.Broadcast(FromState, ToState);

	// Destroy Old State
	if (!IsIdleState(FromState))
	{
		FromState->OnTransitionTo.Clear();
		delete FromState;
		FromState = nullptr;
	}
}

template <typename TStateData>
void UStateMachineBase<TStateData>::TransitionStateTo(UStateBase<TStateData>* ToState)
{
	TargetState = ToState;
}
