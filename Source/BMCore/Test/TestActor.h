// Copyright BanMing

#pragma once

// #include "BMCore/Public/Events/SynchronousEvent.h"
#include "CoreMinimal.h"
#include "Events/EventBase.h"
#include "Events/SynchronousEventSystem.h"
#include "GameFramework/Actor.h"

#include "TestActor.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FTestDelegeate, int32);
// typedef TMyMulticastDelegate<void(int32)> FTestDelegeate;

struct TestEvent : FEventBase
{
	int32 data;
	virtual void Release() override
	{
	}
};

UCLASS()
class BMCORE_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void OnTestEvet(TestEvent& Value);

private:
	class SynchronousEventSystem* EventSystem;
};
