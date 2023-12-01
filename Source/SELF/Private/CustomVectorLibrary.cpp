// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomVectorLibrary.h"
#include "Math/UnrealMathUtility.h"

FVector UCustomVectorLibrary::RadialToVector(float alpha, float beta, float force)
{
	FVector vector;

	if (alpha < 0.0)
		alpha -= 90;
	else
		alpha = 90 - alpha;

	alpha = FMath::DegreesToRadians(alpha);
	beta = FMath::DegreesToRadians(beta);

	vector.X = force * FMath::Sin(alpha) * FMath::Cos(beta);
	vector.Y = force * FMath::Sin(alpha) * FMath::Sin(beta);
	vector.Z = force * FMath::Cos(alpha);

	return vector;
}

FVector UCustomVectorLibrary::ChangeDirectionByCharge(FVector ElectricForce, float Charge)
{
	if (Charge > 0.0)
	{
		ElectricForce.X = ElectricForce.X * (-1.0);
		ElectricForce.Y = ElectricForce.Y * (-1.0);
		ElectricForce.Z = ElectricForce.Z * (-1.0);
	}

	return ElectricForce;
}

TArray<int> UCustomVectorLibrary::GenerateRandomIntArray(int Size, int Min, int Max)
{
	TArray<int> RandomArray;
	int tmp;

	if (FMath::Abs(Max - Min + 1) < Size)
		return RandomArray;

	for (int i = 0; i < Size; i++)
	{
		tmp = FMath::RandRange(Min, Max);

		while (IsIntInArray(RandomArray, tmp))
		{
			tmp = FMath::RandRange(Min, Max);
		}

		RandomArray.Add(tmp);
	}

	return RandomArray;
}

bool UCustomVectorLibrary::IsIntInArray(TArray<int> Array, int Element)
{
	bool IsFound = false;

	for (size_t i = 0; (i < Array.Num()) && (!IsFound); i++)
	{
		if (Array[i] == Element)
			IsFound = true;
	}

	return IsFound;
}
