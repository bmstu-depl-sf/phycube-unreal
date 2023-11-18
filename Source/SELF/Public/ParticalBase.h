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
	
	// Sets default values for this actor's properties
	AParticalBase();

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Partical Base")
	void UpdateElectricForce(FVector Force);
	UFUNCTION(BlueprintCallable, Category = "Partical Base")
	void UpdateInitSpeed(float Speed);
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool IsTrailOn;
	//UPROPERTY(EditDefaultsOnly, Category = "Partical Parameters")
	//TSubclassOf<AActor> TrailClass;

protected:
	UFUNCTION()
	FVector ChangeDirectionByCharge(FVector ElectricForce, float Sight);

	UFUNCTION()
	FVector AddMassOnVector(FVector Force);

	virtual void BeginPlay() override;

	UFUNCTION()
		void AddMovement(float LSpeed);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//	void AddTrail();

	//virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent *SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ElectricForce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Charge;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Sight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Mass;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//float TrailTimer;

	//FVector CurrentPosition;

	//TArray<AActor*> Trails;

	//FTimerHandle TrailTimerHandle;
};
