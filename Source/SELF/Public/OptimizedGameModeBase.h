// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OptimizedGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class SELF_API AOptimizedGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "GraphicAPI")
		virtual void UnlitModeOn();
		UFUNCTION(BlueprintCallable, Category = "GraphicAPI")
		virtual void UnlitModeOff();
protected:
	virtual void BeginPlay() override;
};