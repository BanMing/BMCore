// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

/**
 * Base class from which all events derive. All events have a time and place;
 * derived event types can add additional information. This is an abstract.
 *
 *	struct TestEvent : FEventBase
 *	{
 *		int32 data;
 *		virtual void Release() override{}
 *	};
 *
 */
struct BMCORE_API FEventBase
{
public:
	virtual void Release() = 0;

public:
	// This is an approximate number of classes deriving FEventBase (it's actually ~183)
	const int kApproxNUmberOfDerivedTypes = 200;
};
