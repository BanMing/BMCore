// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

struct FStateDataBase;

/**
 *
 */
template <typename TStateData = FStateDataBase>
class BMCORE_API UStateMachineBase
{
private:
	class UDefaultIdleState : public UStateBase<TStateData>
	{
	};

	static UDefaultIdleState* kDefaultIdleState = new UDefaultIdleState();

public:
	static bool IsIdleState(UStateBase<TStateData>* State);

public:
	UStateMachineBase() = default;
	UStateMachineBase(TStateData* InFSMData);
	~UStateMachineBase();

public:
	void StartFSM(UStateBase<TStateData>* InitState);
	void StopFSM();
	void Suspend();
	void Resume();
	void Tick(float DeltaTime);
	void ResetFSM();

public:
	TStateData* GetCurrentState() const
	{
		return CurrentState;
	}

protected:
	virtual void OnStarting(){};
	virtual void OnStarted(){};
	virtual void OnStopping(){};
	virtual void OnStopped(){};

	// Recommond use StateBase->TransitionTo()
	// Don't use this unless you *really* know what you are doing!
	void ForceTransitionTo(UStateBase<TStateData>* ToState);

private:
	void ExecuteStateTransition();

	void TransitionStateTo(UStateBase<TStateData>* ToState);

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(StateTransitionDelegate, UStateBase<TStateData>*, UStateBase<TStateData>*);

	StateTransitionDelegate OnPreStateTransition;
	StateTransitionDelegate OnPostStateTransition;

protected:
	TStateData* FSMData;

private:
	TObjectPtr<UStateBase<TStateData>> TargetState;

	TObjectPtr<UStateBase<TStateData>> CurrentState;

	bool bIsSuspended = false;
};

