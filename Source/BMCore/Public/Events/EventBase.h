// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

/**
 * Base class from which all events derive. All events have a time and place;
 * derived event types can add additional information. This is an abstract.
 */
class BMCORE_API EventBase
{
public:
	virtual void Release() = 0;

public:
	// This is an approximate number of classes deriving EventBase (it's actually ~183)
	const int kApproxNUmberOfDerivedTypes = 200;
};
