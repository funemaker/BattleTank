// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::ElevateBarrel(float RelativeSpeed) {


	float ClampedSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto ElevationChange = ClampedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("%f: Elevating by %f degrees per second"), Time, RelativeSpeed)
}


