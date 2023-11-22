// Fill out your copyright notice in the Description page of Project Settings.

#include "ParticalBase.h"
#include "HiddenWall.h"
#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ParticleDefinitions.h"
//#include "Trail.h"

#define MASS_INDEX 1e-12
#define VZERO FVector(0,0,0)

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

	TrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));
	TrailComponent->SetupAttachment(RootComponent);

	IsPaused = false;
}

// Called when the game starts or when spawned
void AParticalBase::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AParticalBase::OnOverlapBegin);

	CurrentPosition = GetActorLocation();

	GetWorldTimerManager().SetTimer(TrailTimerHandle, this, &AParticalBase::AddTrail, TrailTimer, true);
}

// Called every frame
void AParticalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsPaused)
	{
		SphereCollision->AddForce(ElectricForce, "None", true);
		UpdateLorentzForce();
		SphereCollision->AddForce(LorentzForce, "None", true);
	}
}

void AParticalBase::UpdateElectricForce(FVector Strength)
{
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

void AParticalBase::UpdateLorentzForce()
{
	LorentzForce = VectorMultiply(MagneticInduction, SphereCollision->GetComponentVelocity());
	LorentzForce *= Charge;
}

FVector AParticalBase::VectorMultiply(FVector a, FVector b)
{
	FVector res;

	res.X = a.Y * b.Z - a.Z * b.Y;
	res.Y = a.X * b.Z - a.Z * b.X;
	res.Z = a.X * b.Y - a.Y * b.X;

	return res;
}

void AParticalBase::AddTrail()
{
	if (!IsTrailOn)
	{
		GetWorldTimerManager().ClearTimer(TrailTimerHandle);
		return;
	}
	
	FVector PreviousPosition = CurrentPosition;
	CurrentPosition = GetActorLocation();
	TrailComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TrailPS, GetActorTransform());
	TrailComponent->SetBeamSourcePoint(0, PreviousPosition, 0);
	TrailComponent->SetBeamTargetPoint(0, CurrentPosition, 0);
	TrailArray.Add(TrailComponent);
}


void AParticalBase::Destroyed()
{
	GetWorldTimerManager().ClearTimer(TrailTimerHandle);

	for (size_t i = 0; i < TrailArray.Num(); i++)
	{
		if (IsValid(TrailArray[i]))
		{
			TrailArray[i]->DeactivateSystem();
			TrailArray[i]->DestroyComponent();
		}
	}
	TrailArray.Empty();
}

void AParticalBase::SetPaused(bool Paused)
{
	if (Paused)
	{
		IsPaused = Paused;
		GetWorldTimerManager().ClearTimer(TrailTimerHandle);
		OldVelocity = SphereCollision->GetPhysicsLinearVelocity();
		SphereCollision->SetPhysicsLinearVelocity(VZERO);
		SphereCollision->SetSimulatePhysics(false);
	}
	else
	{
		IsPaused = Paused;
		GetWorldTimerManager().SetTimer(TrailTimerHandle, this, &AParticalBase::AddTrail, TrailTimer, true);
		SphereCollision->SetSimulatePhysics(true);
		SphereCollision->SetPhysicsLinearVelocity(OldVelocity);

		if (SphereCollision->GetComponentVelocity() == VZERO)
			UpdateInitImpulse(InitImpulse);
	}
}