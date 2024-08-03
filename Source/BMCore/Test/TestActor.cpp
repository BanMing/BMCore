// Copyright BanMing

#include "BMCore/Test/TestActor.h"

#include "BMCore/Public/Events/SynchronousEventSystem.h"
void OnTestEvet(const TestEvet& Event)
{
}
// Sets default values
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EventSystem = new SynchronousEventSystem();
	EventSystem->AddHandler<TestEvet>(&OnTestEvet);
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


