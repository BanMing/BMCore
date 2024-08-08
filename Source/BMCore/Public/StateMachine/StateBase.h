// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

struct FStateDataBase;

/**
 *
 */
template <typename TStateData = FStateDataBase>
class BMCORE_API StateBase
{
public:
	StateBase(bool InbIsReusing = false);
	virtual ~StateBase();

public:
	void Enter(TStateData* InCommonData);
	void Tick(float DeltaTime);
	void Exit();

protected:
	virtual void OnInitialize() = 0;
	virtual void OnEnter() = 0;
	virtual void OnTick(float DeltaTime) = 0;
	virtual void OnExit() = 0;
	virtual void OnDestroy() = 0;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FTransitionToHandler, StateBase<TStateData>*);
	FTransitionToHandler OnTransitionTo;

protected:
	TStateData* CommonData;
	bool bIsReusing;
};
