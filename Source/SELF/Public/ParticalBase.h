// Fill out your copyright notice in the Description page of Project Settings.
// All characteristcs are multilply on 1e19

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
	void UpdateElectricForce(FVector Strength);
	UFUNCTION(BlueprintCallable, Category = "Partical Base")
	void UpdateInitImpulse(float Impulse);
	/* Depricated
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool IsTrailOn;
	//UPROPERTY(EditDefaultsOnly, Category = "Partical Parameters")
	//TSubclassOf<AActor> TrailClass;
	*/
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		FVector VectorMultiply(FVector a, FVector b);

	UFUNCTION()
	void UpdateLorentzForce();
	/* Depricated
	//UFUNCTION()
	//	void AddTrail();

	//virtual void Destroyed() override;
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent *SphereCollision;

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

	/* Depricated
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//float TrailTimer;

	//FVector CurrentPosition;

	//TArray<AActor*> Trails;

	//FTimerHandle TrailTimerHandle;
	*/
};
