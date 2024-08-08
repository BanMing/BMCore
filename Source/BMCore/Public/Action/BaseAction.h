// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
class BaseActionManager;

/**
 *
 */
class BMCORE_API BaseAction
{
public:
	virtual ~BaseAction() = default;

	// Useful if you want to access variables from actors that can be destroyed between when an action is queued and when it is run.
	// If so you can access them here and store them in variables to be used when playing the action
	virtual void SetUpAction(BaseActionManager* ActionManager) = 0;

	virtual void StartAction(BaseActionManager* ActionManager);
	virtual void EndAction(BaseActionManager* ActionManager);

	virtual void DestroyAction() = 0;

protected:
	float EndDelay = 0.f;
};
