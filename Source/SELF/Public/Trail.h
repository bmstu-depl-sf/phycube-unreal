// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trail.generated.h"

UCLASS()
class SELF_API ATrail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrail();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetPoints(FVector Begin, FVector End);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FVector BeginPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FVector EndPoint;

	bool IsInit;
};
