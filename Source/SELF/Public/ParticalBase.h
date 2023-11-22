// Fill out your copyright notice in the Description page of Project Settings.
// All characteristcs are multilply on 1e19

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ParticleDefinitions.h"
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
	void UpdateElectricForce(FVector Strength);
	UFUNCTION(BlueprintCallable, Category = "Partical Base")
	void UpdateInitImpulse(float Impulse);
	UFUNCTION(BlueprintCallable, Category = "Partical Base")
	void SetPaused(bool Paused);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsTrailOn;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UParticleSystem* TrailPS;
	
	class UParticleSystemComponent* TrailComponent;
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		FVector VectorMultiply(FVector a, FVector b);

	UFUNCTION()
	void UpdateLorentzForce();

	UFUNCTION()
	void AddTrail();

	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ElectricForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LorentzForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MagneticInduction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Mass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Charge;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TrailTimer;

	FVector CurrentPosition;
	FTimerHandle TrailTimerHandle;

	TArray<UParticleSystemComponent*> TrailArray;

	bool IsPaused;
	FVector OldVelocity;
	FVector OldAcceleration;
};
