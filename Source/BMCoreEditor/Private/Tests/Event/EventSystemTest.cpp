// Fill out your copyright notice in the Description page of Project Settings.

#include "Tests/Event/EventSystemTest.h"

#include "Events/AsynchronousEventSystem.h"
#include "Events/EventBase.h"
#include "Events/IEventSystem.h"
#include "Events/SynchronousEventSystem.h"
#include "Misc/AutomationTest.h"

struct FTestEvent : public FEventBase
{
	int32 Value;

	FTestEvent(int32 InValue) : Value(InValue)
	{
	}

	// Inherited via FEventBase
	void Release() override
	{
		Value = 0;
	}
};

struct FTestFloatEvent : public FEventBase
{
	float Value;

	FTestFloatEvent(float InValue) : Value(InValue)
	{
	}

	// Inherited via FEventBase
	void Release() override
	{
		Value = 0;
	}
};

class Listener
{
public:
	void OnEvent(const FTestEvent& Event)
	{
		UE_LOG(LogEvent, Log, TEXT("Receive Event Int32 Value: %d"), Event.Value);
	}

	void OnFloatEvent(const FTestFloatEvent& Event)
	{
		UE_LOG(LogEvent, Log, TEXT("Receive Event Float Value: %f"), Event.Value);
	}

public:
	int32 Data;
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAsynchronousEventSystemTest, "BMCore.Event.AsynchronousEventSystem Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FAsynchronousEventSystemTest::RunTest(const FString& Parameters)
{
	Listener* ListenerPtr = new Listener();

	AsynchronousEventSystem* EventSystem = new AsynchronousEventSystem();
	EventSystem->AddHandler<FTestEvent>(ListenerPtr, &Listener::OnEvent);
	EventSystem->AddHandler<FTestFloatEvent>(ListenerPtr, &Listener::OnFloatEvent);

	for (int32 i = 0; i < 10; i++)
	{
		FTestEvent* TestEvent = new FTestEvent(i);
		EventSystem->Boradcast(TestEvent);

		FTestFloatEvent* TestFloatEvent = new FTestFloatEvent(i + 0.1f);
		EventSystem->Boradcast(TestFloatEvent);
	}

	EventSystem->DispatchEvents();

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSynchronousEventSystemTest, "BMCore.Event.SynchronousEventSystem Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FSynchronousEventSystemTest::RunTest(const FString& Parameters)
{
	Listener* ListenerPtr = new Listener();

	SynchronousEventSystem* EventSystem = new SynchronousEventSystem();
	EventSystem->AddHandler<FTestEvent>([](const FTestEvent& Event) { UE_LOG(LogEvent, Log, TEXT("Receive Lambda Event Int32 Value: %d"), Event.Value); });
	size_t Key = typeid(FTestEvent).hash_code();
	EventSystem->AddHandler<FTestFloatEvent>([](const FTestFloatEvent& Event) { UE_LOG(LogEvent, Log, TEXT("Receive Lambda Event Float Value: %f"), Event.Value); });

	for (int32 i = 0; i < 10; i++)
	{
		FTestEvent* TestEvent = new FTestEvent(i);
		EventSystem->Boradcast(TestEvent);
		size_t Key1 = typeid(FTestEvent).hash_code();
		FTestFloatEvent* TestFloatEvent = new FTestFloatEvent(i + 0.1f);
		EventSystem->Boradcast(TestFloatEvent);
	}

	return true;
}