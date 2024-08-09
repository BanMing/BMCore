// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

struct FStateDataBase;
class StateBase;
/**
 *
 */
class BMCORE_API StateMachineBase
{
public:
	StateMachineBase() = default;
	StateMachineBase(FStateDataBase* InFSMData);
	virtual ~StateMachineBase();

public:
	void StartFSM(StateBase* InitState);
	void StopFSM();
	void Suspend();
	void Resume();
	void Tick(float DeltaTime);
	void ResetFSM();

public:
	StateBase* GetCurrentState();

protected:
	virtual void OnStarting() = 0;
	virtual void OnStarted() = 0;
	virtual void OnStopping() = 0;
	virtual void OnStopped() = 0;

	// Recommond use StateBase->TransitionTo()
	// Don't use this unless you *really* know what you are doing!
	void ForceTransitionTo(StateBase* ToState);

private:
	void ExecuteStateTransition();

	void TransitionStateTo(StateBase* ToState);

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(StateTransitionDelegate, StateBase*, StateBase*);

	StateTransitionDelegate OnPreStateTransition;
	StateTransitionDelegate OnPostStateTransition;

protected:
	FStateDataBase* FSMData;

private:
	StateBase* TargetState;

	StateBase* CurrentState;

	bool bIsSuspended = false;
};
