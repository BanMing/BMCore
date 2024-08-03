// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class BMCORE_API StateDataBase
{
public:
	virtual ~StateDataBase() = default;
	virtual void Release() = 0;
	virtual void Reset() = 0;
};
