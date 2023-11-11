// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomVectorLibrary.h"
#include "Math/UnrealMathUtility.h"

FVector UCustomVectorLibrary::RadialToVector(float alpha, float beta, float force)
{
	FVector vector;

	if (alpha < 0)
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