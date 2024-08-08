// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
class BaseAction;
/**
 *
 */
class BMCORE_API BaseActionManager
{
public:
	virtual ~BaseActionManager() = default;

	virtual void SetUp();
	virtual void Tick(float DeltaSeconds);
	virtual void Destroy();

	virtual void AttemptToPlayNextAction();
	virtual void QueueAction(BaseAction* Action);
	virtual void ProceedFromOngoingAction(BaseAction* OngoingAction);

protected:
	TQueue<BaseAction*> ActionQueue;

	int32 ActionsThisTick;
	int32 MaxActionsPerTick = 5;
};
