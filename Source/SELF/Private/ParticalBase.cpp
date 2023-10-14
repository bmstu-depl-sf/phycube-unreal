// Fill out your copyright notice in the Description page of Project Settings.

#include "ParticalBase.h"
#include "HiddenWall.h"

// Sets default values
AParticalBase::AParticalBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AParticalBase::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AParticalBase::OnOverlapBegin);
}

// Called every frame
void AParticalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovement(Speed);
}

void AParticalBase::AddMovement(float LSpeed)
{
	FVector DeltaLocation;

	DeltaLocation.X = GetWorld()->GetDeltaSeconds() * LSpeed;

	SphereCollision->AddWorldOffset(DeltaLocation, true);
}

void AParticalBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AHiddenWall *HiddenWall = Cast<AHiddenWall>(OtherActor);

	if (HiddenWall != nullptr)
	{
		this->Destroy();
	}
}
