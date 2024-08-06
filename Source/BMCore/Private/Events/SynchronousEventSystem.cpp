// Copyright BanMing

#include "Events/SynchronousEventSystem.h"

void SynchronousEventSystem::Initialize()
{
}

void SynchronousEventSystem::Destroy()
{
	RemoveAllHandlers();
}
