// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

struct FStateDataBase;
/**
 *
 */
template <typename TStateData = FStateDataBase>
class BMCORE_API UStateBase
{
public:
	UStateBase() = default;
	~UStateBase();

public:
	void Enter(TStateData* InCommonData);
	void Tick(float DeltaTime);
	void Exit();

protected:
	virtual void OnEnter(){};
	virtual void OnTick(float DeltaTime){};
	virtual void OnExit(){};

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FTransitionToHandler, UStateBase<TStateData>*);
	FTransitionToHandler OnTransitionTo;

protected:
	TStateData* CommonData;
};
