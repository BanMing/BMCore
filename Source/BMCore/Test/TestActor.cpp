// Copyright BanMing

#include "BMCore/Test/TestActor.h"

#include "Events/AsynchronousEventSystem.h"
#include "Events/SynchronousEventSystem.h"

ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EventSystem = new SynchronousEventSystem();
	EventSystem->AddHandler<TestEvent>(this, &ThisClass::OnTestEvet);
	AsyncEventSystem = new AsynchronousEventSystem();
	AsyncEventSystem->AddHandler<TestEvent>(this, &ThisClass::OnTestEvet);
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
	AsyncEventSystem->Boradcast(Agrs);

	TestEvent Agrs1;
	Agrs1.data = 5;
	AsyncEventSystem->Boradcast(Agrs1);

	TestEvent Agrs2;
	Agrs2.data = 1;
	AsyncEventSystem->Boradcast(Agrs2);

	TArray<int32> TEST1{1, 3, 4, 5};
	TArray<int32> TEST2;

	TEST2 = MoveTemp(TEST1);
	UE_LOG(LogTemp, Error, TEXT("TEST1 %d"), TEST1.Num());
	UE_LOG(LogTemp, Error, TEXT("TEST2 %d"), TEST2.Num());
	AsyncEventSystem->DispatchEvents();
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestActor::OnTestEvet(const TestEvent& Value)
{
	UE_LOG(LogTemp, Error, TEXT("EVENT %d"), Value.data);
}
