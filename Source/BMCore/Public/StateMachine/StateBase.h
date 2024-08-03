// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

#include "StateBase.generated.h"

class StateDataBase;

/**
 *
 */
UCLASS(Abstract)
class BMCORE_API UStateBase : public UObject
{
	GENERATED_BODY()
public:
	UStateBase(const FObjectInitializer& ObjectInitializer);
	~UStateBase();

public:
	void Enter(StateDataBase* InCommonData);
	void Tick(float DeltaTime);
	void Exit();

protected:
	virtual void OnEnter(){};
	virtual void OnTick(float DeltaTime){};
	virtual void OnExit(){};

	void TransitionTo(TSubclassOf<UStateBase> NextSubStateBaseClass);

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FTransitionToHandler, TSubclassOf<UStateBase>);
	FTransitionToHandler OnTransitionTo;

protected:
	StateDataBase* CommonData;
};
