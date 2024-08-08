// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"

struct FStateDataBase;
/**
 *
 */
template <typename TStateData = FStateDataBase>
class BMCORE_API StateMachineBase
{
public:
	StateMachineBase(TStateData* InFSMData);
	virtual ~StateMachineBase();
	StateMachineBase(StateMachineBase<TStateData> const&) = delete;
	StateMachineBase* operator=(const StateMachineBase<TStateData>&) = delete;

public:
	void StartFSM(StateBase<TStateData>* InitState);
	void StopFSM();
	void Suspend();
	void Resume();
	void Tick(float DeltaTime);
	void ResetFSM();

public:
	TStateData* GetCurrentState();

protected:
	virtual void OnInitialize() = 0;
	virtual void OnStarting() = 0;
	virtual void OnStarted() = 0;
	virtual void OnStopping() = 0;
	virtual void OnStopped() = 0;
	virtual void OnDestroy() = 0;

	// Recommond use StateBase->TransitionTo()
	// Don't use this unless you *really* know what you are doing!
	void ForceTransitionTo(StateBase<TStateData>* ToState);

private:
	void ExecuteStateTransition();

	void TransitionStateTo(StateBase<TStateData>* ToState);

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(StateTransitionDelegate, StateBase<TStateData>*, StateBase<TStateData>*);

	StateTransitionDelegate OnPreStateTransition;
	StateTransitionDelegate OnPostStateTransition;

protected:
	TStateData* FSMData;

private:
	StateBase<TStateData>* TargetState;

	StateBase<TStateData>* CurrentState;

	bool bIsSuspended = false;
};
