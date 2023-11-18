// Fill out your copyright notice in the Description page of Project Settings.

#include "ParticalBase.h"
#include "HiddenWall.h"
//#include "Trail.h"

#define MASS_INDEX 1e-12

// Sets default values
AParticalBase::AParticalBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	//SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetCollisionProfileName("Partical");
	SphereCollision->SetSimulatePhysics(true);
	SphereCollision->SetEnableGravity(false);
	SphereCollision->SetLinearDamping(0.0);
	//SetRootComponent(SphereCollision);
	
	Mass *= MASS_INDEX;

	SphereCollision->BodyInstance.bOverrideMass = true;
	SphereCollision->BodyInstance.SetMassOverride(Mass);
}

// Called when the game starts or when spawned
void AParticalBase::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AParticalBase::OnOverlapBegin);

	/* Depricated
	//CurrentPosition = GetActorLocation();

	//GetWorldTimerManager().SetTimer(TrailTimerHandle, this, &AParticalBase::AddTrail, TrailTimer, true);
	*/
}

// Called every frame
void AParticalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SphereCollision->AddForce(ElectricForce, "None", true);
}

void AParticalBase::UpdateElectricForce(FVector Strength)
{
	// strength to force
	ElectricForce = Charge * Strength;
}

void AParticalBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AHiddenWall *HiddenWall = Cast<AHiddenWall>(OtherActor);

	if (HiddenWall != nullptr)
	{
		this->Destroy();
	}
}

void AParticalBase::UpdateInitImpulse(float Impulse)
{
	InitImpulse = Impulse;
	FVector SpeedVector;

	SpeedVector.Set(InitImpulse, 0.0, 0.0);
	SphereCollision->AddImpulse(SpeedVector, "None", true);
}
/* Depricated
void AParticalBase::AddTrail()
{
	if (!IsTrailOn)
	{
		GetWorldTimerManager().ClearTimer(TrailTimerHandle);
		return;
	}
	

	FVector PreviousPosition;
	ATrail* trail;

	PreviousPosition = CurrentPosition;
	CurrentPosition = GetActorLocation();

	trail = GetWorld()->SpawnActor<ATrail>(TrailClass, GetActorTransform());
	
	if (trail != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("The Actor's name is"));
		//trail->SetPoints(PreviousPosition, CurrentPosition);
		//Trails.Add(tmp);
	}
}

void AParticalBase::Destroyed()
{
	GetWorldTimerManager().ClearTimer(TrailTimerHandle);

	for (size_t i = 0; i < Trails.Num(); i++)
	{
		Trails[i]->Destroy();
	}
}
*/