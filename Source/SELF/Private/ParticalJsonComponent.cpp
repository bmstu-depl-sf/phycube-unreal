// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticalJsonComponent.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"

// Sets default values for this component's properties
UParticalJsonComponent::UParticalJsonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UParticalJsonComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UParticalJsonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UParticalJsonComponent::LoadJson(FString Path)
{
	bool rc = true;

	//FString Filename = "Particals.json";
	//FString FullPathContent = Path + Filename;

	FString JsonStr;

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*Path))
	{
		/*FullPathContent = FPaths::GameSourceDir() + Filename;

		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullPathContent))
		{
			FullPathContent = FPaths::LaunchDir() + Filename;

			if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullPathContent))
			{
				rc = false;
			}
		}
		*/
		rc = false;
	}

	if (rc)
	{
		FFileHelper::LoadFileToString(JsonStr, *Path);

		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		FJsonSerializer::Deserialize(JsonReader, JsonObject);

		TArray<TSharedPtr<FJsonValue>> Particals;

		Particals = JsonObject->GetArrayField("particals");

		FParticleDataStruct tmp;

		for (size_t i = 0; i < Particals.Num(); i++)
		{
			tmp.Name = Particals[i]->AsObject()->GetStringField("name");
			tmp.Trail = Particals[i]->AsObject()->GetBoolField("trail");
			tmp.Impulse = Particals[i]->AsObject()->GetNumberField("impulse");
			tmp.Mass = Particals[i]->AsObject()->GetNumberField("mass");
			tmp.Charge = Particals[i]->AsObject()->GetNumberField("charge");
			tmp.Timer = Particals[i]->AsObject()->GetNumberField("timer");
			tmp.Rate = Particals[i]->AsObject()->GetNumberField("rate");
			tmp.Red = Particals[i]->AsObject()->GetNumberField("red");
			tmp.Green = Particals[i]->AsObject()->GetNumberField("green");
			tmp.Blue = Particals[i]->AsObject()->GetNumberField("blue");

			ParticleData.Add(tmp);
		}
	}
}