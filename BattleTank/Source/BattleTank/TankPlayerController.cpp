// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("My tank pawn is: %s"), *GetControlledTank()->GetName())
		PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//aim towards crosshair

	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{

	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation;  //out parameter

	if (GetSightRayHitLocation(HitLocation)) {

	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
	}

	//get world location through crosshair linetrace
	//if it hits something, then 
	//controlled tank aims at point of hit
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{

	//find crosshair position
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto CrosshairLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);


	UE_LOG(LogTemp, Warning, TEXT("CH Location: %s"), *CrosshairLocation.ToString())
	//deproject screen position of crosshair to world direction

	//line trace along that look direction, see what we hit up to max range



	/*
	//ray-cast out to reach distance
	FHitResult Hit;

	//setup query parameters

	FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetControlledTank());

	if (GetWorld()->LineTraceSingleByObjectType(

		OUT Hit,
		GetControlledTank()->GetActorLocation(),
		GetControlledTank()->GetActorLocation() + GetControlledTank()->GetActorRotation().Vector() * 10000,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters


	)) {
		return true;
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.Actor->GetName());
		OutHitLocation.X = Hit.ImpactPoint.X;
		OutHitLocation.Y = Hit.ImpactPoint.Y;
		OutHitLocation.Z = Hit.ImpactPoint.Z;
	} else {
	return false;
	}
	*/
	OutHitLocation = FVector(1);
	return true;
}

