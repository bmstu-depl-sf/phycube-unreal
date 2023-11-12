// Fill out your copyright notice in the Description page of Project Settings.

#include "ParticalBase.h"
#include "HiddenWall.h"

// Sets default values
AParticalBase::AParticalBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	//SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetCollisionProfileName("Partical");
	SphereCollision->SetSimulatePhysics(true);
	SphereCollision->SetMassScale("", Charge);
	SphereCollision->SetEnableGravity(false);
	SphereCollision->SetLinearDamping(0.0);
	//SetRootComponent(SphereCollision);
	// Следующим кодом заменить SphereCollision->SetMassScale("", Charge);
	//SphereCollision->BodyInstance.bOverrideMass = true;
	//SphereCollision->BodyInstance.SetMassOverride(Charge);
}

FVector AParticalBase::ChangeDirectionByCharge(FVector ElectricForce, float Sight)
{
	if (Sight > 0.0)
	{
		ElectricForce.X = ElectricForce.X * (-1.0);
		ElectricForce.Y = ElectricForce.Y * (-1.0);
		ElectricForce.Z = ElectricForce.Z * (-1.0);
	}

	return ElectricForce;
}

// Called when the game starts or when spawned
void AParticalBase::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AParticalBase::OnOverlapBegin);

	ElectricForce = ChangeDirectionByCharge(ElectricForce, Sight);
}

// Called every frame
void AParticalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SphereCollision->AddForce(ElectricForce, "None", true);
}

void AParticalBase::UpdateElectricForce(FVector Force)
{
	this->ElectricForce = ChangeDirectionByCharge(Force, Sight);;
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

void AParticalBase::UpdateInitSpeed(float Speed)
{
	InitSpeed = Speed;
	FVector SpeedVector;

	SpeedVector.Set(InitSpeed, 0.0, 0.0);
	SphereCollision->AddImpulse(SpeedVector, "None", true);
}
