// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FParticleDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FParticleDataStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Data")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Data")
		bool Trail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Data")
		float Impulse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Data")
		float Mass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Data")
		float Charge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Data")
		float Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Data")
		float Rate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Data")
		float Red;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Data")
		float Green;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Data")
		float Blue;
};
