// Copyright BanMing

#pragma once

#include "BMCore/Public/Events/SynchronousEvent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TestActor.generated.h"
class TestEvet : public SynchronousEvent
{
protected:
	// Inherited via SynchronousEvent
	void OnEventReleased() override
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
	//void OnTestEvet(const TestEvet& Event);

private:
	class SynchronousEventSystem* EventSystem;
};
