// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

#include <functional>
struct FEventBase;

using FEventHandle = size_t;

struct FEventInfo
{
	std::function<void(FEventBase*)> Handler;
	FEventHandle Handle;
};

class BMCORE_API IEventSystem
{
public:
	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
	virtual ~IEventSystem()
	{
	}
};
