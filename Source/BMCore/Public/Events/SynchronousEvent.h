// Copyright BanMing

#pragma once
#include "CoreMinimal.h"
#include "EventBase.h"
/**
 *
 */
class BMCORE_API SynchronousEvent : public EventBase
{
public:
	// Inherited via EventBase
	virtual void Release() override;

protected:
	virtual void OnEventReleased() = 0;
};
