// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

#include "StateMachineBase.generated.h"

class UStateBase;
class StateDataBase;

DECLARE_MULTICAST_DELEGATE_TwoParams(StateTransitionDelegate, UStateBase*, UStateBase*);

/**
 *
 */
UCLASS(Abstract)
class BMCORE_API UStateMachineBase : public UObject
{
	GENERATED_BODY()
public:
	static bool IsIdleState(UStateBase* State);

public:
	UStateMachineBase();
	UStateMachineBase(const FObjectInitializer& ObjectInitializer, StateDataBase* InFSMData);
	~UStateMachineBase();

public:
	void StartFSM(TSubclassOf<UStateBase> SubStateBaseClass);
	void StopFSM();
	void Suspend();
	void Resume();
	void Tick(float DeltaTime);
	void ResetFSM();

public:
	UStateBase* GetCurrentState() const
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
	void ForceTransitionTo(TSubclassOf<UStateBase> SubStateBaseClass);

private:
	UFUNCTION()
	void TransitionStateTo(TSubclassOf<UStateBase> SubStateBaseClass);
	void ExecuteStateTransition();

public:
	StateTransitionDelegate OnPreStateTransition;
	StateTransitionDelegate OnPostStateTransition;

protected:
	StateDataBase* FSMData;

private:
	UPROPERTY()
	TObjectPtr<UStateBase> TargetState;

	UPROPERTY()
	TObjectPtr<UStateBase> CurrentState;
	bool bIsSuspended = false;
};
