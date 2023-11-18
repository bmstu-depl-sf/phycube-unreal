// Fill out your copyright notice in the Description page of Project Settings.


#include "Trail.h"

// Sets default values
ATrail::ATrail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsInit = false;
}

// Called when the game starts or when spawned
void ATrail::BeginPlay()
{
	Super::BeginPlay();
	while (!IsInit);
}

// Called every frame
void ATrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrail::SetPoints(FVector Begin, FVector End)
{
	BeginPoint = Begin;
	EndPoint = End;
	IsInit = true;
}