// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

struct FStateDataBase;

/**
 *
 */
class BMCORE_API StateBase
{
public:
	StateBase(bool InbIsReusing = false);
	virtual ~StateBase();

public:
	void Enter(FStateDataBase* InCommonData);
	void Tick(float DeltaTime);
	void Exit();

protected:
	virtual void OnEnter() = 0;
	virtual void OnTick(float DeltaTime) = 0;
	virtual void OnExit() = 0;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FTransitionToHandler, StateBase*);
	FTransitionToHandler OnTransitionTo;

protected:
	FStateDataBase* CommonData;
	bool bIsReusing;
};
