// Copyright BanMing

#include "BMCore/Test/TestActor.h"

// void OnTestEvet(const TestEvet& Event)
//{
// }
//  Sets default values
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EventSystem = new SynchronousEventSystem();
	EventSystem->AddHandler<TestEvent>(this, &ThisClass::OnTestEvet);
	// EventSystem->RegisterListener<TestEvent>(this, [](const TestEvent& Value) { UE_LOG(LogTemp, Error, TEXT("EVENT %d"), Value.data); });
	//  EventSystem =  SynchronousEventSystem();
	//  SynchronousEventSystem TEST;
	//  TEST.Test = FTestDelegeate;
	//   EventSystem->AddHandler<TestEvet>(&OnTestEvet);
	//  EventSystem->TestEvent1
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	/*FTestDelegeate::FDelegate::TFuncType*/
	// FTestDelegeate test;
	// EventSystem->AddUObject<FTestDelegeate>(12, this, &ThisClass::OnTestEvet);
	TestEvent Agrs;
	Agrs.data = 3;
	EventSystem->Boradcast(Agrs);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestActor::OnTestEvet(TestEvent& Value)
{
	UE_LOG(LogTemp, Error, TEXT("EVENT %d"), Value.data);
}
