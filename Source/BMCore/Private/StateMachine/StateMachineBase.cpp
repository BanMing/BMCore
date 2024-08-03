// Copyright BanMing

#include "StateMachine/StateMachineBase.h"

#include "StateMachine/StateBase.h"
#include "StateMachine/StateDataBase.h"

class UDefaultIdleState : public UStateBase
{
};

static UDefaultIdleState* kDefaultIdleState = NewObject<UDefaultIdleState>();

bool UStateMachineBase::IsIdleState(UStateBase* State)
{
	return kDefaultIdleState == State;
}

UStateMachineBase::UStateMachineBase()
{
}

UStateMachineBase::UStateMachineBase(const FObjectInitializer& ObjectInitializer, StateDataBase* InFSMData) : Super(ObjectInitializer), FSMData(InFSMData)
{
}

UStateMachineBase::~UStateMachineBase()
{
	if (FSMData != nullptr)
	{
		FSMData->Release();
		delete FSMData;
		FSMData = nullptr;
	}
}

void UStateMachineBase::StartFSM(TSubclassOf<UStateBase> SubStateBaseClass)
{
	ensureMsgf(IsValid(SubStateBaseClass), TEXT("Invalid type %s for state supplied as initial state"), *SubStateBaseClass->GetDefaultObjectName().ToString());
	OnStarting();
	CurrentState = kDefaultIdleState;
	TransitionStateTo(SubStateBaseClass);
	ExecuteStateTransition();
	OnStarted();
}

void UStateMachineBase::StopFSM()
{
	OnStopping();

	TransitionStateTo(UDefaultIdleState::StaticClass());
	ExecuteStateTransition();

	OnStopped();
}

void UStateMachineBase::Suspend()
{
	bIsSuspended = true;
}

void UStateMachineBase::Resume()
{
	bIsSuspended = false;
}

void UStateMachineBase::Tick(float DeltaTime)
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

void UStateMachineBase::ResetFSM()
{
	CurrentState = kDefaultIdleState;
	FSMData->Reset();
}

void UStateMachineBase::ForceTransitionTo(TSubclassOf<UStateBase> SubStateBaseClass)
{
	TransitionStateTo(SubStateBaseClass);
	ExecuteStateTransition();
}

void UStateMachineBase::TransitionStateTo(TSubclassOf<UStateBase> SubStateBaseClass)
{
	// TODO: check use CDO rather than new object
	TargetState = NewObject<UStateBase>(this, SubStateBaseClass);
}

void UStateMachineBase::ExecuteStateTransition()
{
	UStateBase* FromState = CurrentState;
	UStateBase* ToState = TargetState;
	TargetState = nullptr;

	OnPreStateTransition.Broadcast(FromState, ToState);

	CurrentState->Exit();
	CurrentState = ToState;
	CurrentState->OnTransitionTo.AddUObject(this, &ThisClass::TransitionStateTo);
	CurrentState->Enter(FSMData);
	OnPostStateTransition.Broadcast(FromState, ToState);

	// Destroy Old State
	if (!FromState->IsA<UDefaultIdleState>())
	{
		FromState->OnTransitionTo.Clear();
		FromState->ConditionalBeginDestroy();
		FromState = nullptr;
	}
}
