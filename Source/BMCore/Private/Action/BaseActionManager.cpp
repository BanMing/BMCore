// Copyright BanMing

#include "Action/BaseActionManager.h"

#include "Action/BaseAction.h"

void BaseActionManager::SetUp()
{
	ActionQueue.Empty();
	ActionsThisTick = 0;
}

void BaseActionManager::Tick(float DeltaSeconds)
{
	ActionsThisTick = 0;
}

void BaseActionManager::Destroy()
{
	while (!ActionQueue.IsEmpty())
	{
		BaseAction* Action;
		ActionQueue.Dequeue(Action);
		if (Action != nullptr)
		{
			Action->DestroyAction();
			delete Action;
		}
	}
}

void BaseActionManager::AttemptToPlayNextAction()
{
	if (ActionQueue.IsEmpty() || ActionQueue.Peek() == nullptr || ActionsThisTick >= MaxActionsPerTick)
	{
		return;
	}
	ActionsThisTick++;

	BaseAction* Action;
	ActionQueue.Dequeue(Action);
	Action->StartAction(this);
}

void BaseActionManager::QueueAction(BaseAction* Action)
{
	if (Action != nullptr)
	{
		ActionQueue.Enqueue(Action);
	}
}

void BaseActionManager::ProceedFromOngoingAction(BaseAction* OngoingAction)
{
	OngoingAction->DestroyAction();
	delete OngoingAction;
	AttemptToPlayNextAction();
}
