// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomVectorLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SELF_API UCustomVectorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "SELF extensions")
		static FVector RadialToVector(float alpha, float beta, float force);
	UFUNCTION(BlueprintCallable, Category = "SELF extensions")
		static FVector ChangeDirectionByCharge(FVector ElectricForce, float Charge);
	UFUNCTION(BlueprintCallable, Category = "SELF extensions")
		static TArray<int> GenerateRandomIntArray(int Size, int Min, int Max);
	UFUNCTION(BlueprintCallable, Category = "SELF extensions")
		static bool IsIntInArray(TArray<int> Array, int Element);
};
