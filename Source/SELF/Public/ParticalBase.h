// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "ParticalBase.generated.h"


UCLASS()
class SELF_API AParticalBase : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticalBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent *SphereCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Speed;

	UFUNCTION()
	void AddMovement(float LSpeed);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
