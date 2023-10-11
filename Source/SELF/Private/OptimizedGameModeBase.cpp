// Fill out your copyright notice in the Description page of Project Settings.


#include "OptimizedGameModeBase.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameViewportClient.h"

// Called when the game starts or when spawned
void AOptimizedGameModeBase::UnlitModeOn()
{

	UGameViewportClient* GameViewport = GetWorld()->GetGameViewport();
	GameViewport->ViewModeIndex = 2;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// The command being executed.
	FString Command = "ShowFlag.Tonemapper 0";
	PlayerController->ConsoleCommand(*Command);

	// The below commands are for the shipping
	// build.
	Command = "r.TonemapperGamma 0";
	PlayerController->ConsoleCommand(*Command);

	Command = "r.TonemapperFilm 0";
	PlayerController->ConsoleCommand(*Command);

	Command = "r.Tonemapper.Sharpen 0";
	PlayerController->ConsoleCommand(*Command);

	Command = "r.Tonemapper.GrainQuantization 0";
	PlayerController->ConsoleCommand(*Command);

	Command = "r.Tonemapper.Quality 0";
	PlayerController->ConsoleCommand(*Command);

}

void AOptimizedGameModeBase::UnlitModeOff()
{

	UGameViewportClient *GameViewport = GetWorld()->GetGameViewport();
	GameViewport->ViewModeIndex = 2;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// The command being executed.
	FString Command = "ShowFlag.Tonemapper 1";
	PlayerController->ConsoleCommand(*Command);

	// The below commands are for the shipping
	// build.
	Command = "r.TonemapperGamma 3";
	PlayerController->ConsoleCommand(*Command);

	Command = "r.TonemapperFilm 3";
	PlayerController->ConsoleCommand(*Command);

	Command = "r.Tonemapper.Sharpen 3";
	PlayerController->ConsoleCommand(*Command);

	Command = "r.Tonemapper.GrainQuantization 3";
	PlayerController->ConsoleCommand(*Command);

	Command = "r.Tonemapper.Quality 3";
	PlayerController->ConsoleCommand(*Command);

}

void AOptimizedGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UnlitModeOn();
}