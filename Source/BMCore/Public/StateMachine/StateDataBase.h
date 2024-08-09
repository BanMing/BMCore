// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
struct BMCORE_API FStateDataBase
{
	virtual ~FStateDataBase() = default;
	virtual void Release(){};
	virtual void Reset(){};
};
