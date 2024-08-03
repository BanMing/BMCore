// Copyright BanMing

#include "Events/SynchronousEvent.h"

void SynchronousEvent::Release()
{
	OnEventReleased();
}
