// Copyright BanMing

#include "Action/BaseAction.h"

#include "Action/BaseActionManager.h"

void BaseAction::StartAction(BaseActionManager* ActionManager)
{
	EndAction(ActionManager);
}

void BaseAction::EndAction(BaseActionManager* ActionManager)
{
	if (EndDelay > 0.f)
	{
		// TODO delay EndAction
	}
	else
	{
		ActionManager->ProceedFromOngoingAction(this);
	}
}
