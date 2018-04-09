// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


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
		
		GetControlledTank()->AimAt(HitLocation);

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


//	UE_LOG(LogTemp, Warning, TEXT("CH Location: %s"), *CrosshairLocation.ToString())

		//deproject screen position of crosshair to world direction
	FVector LookDirection;
	if (GetLookDirection(CrosshairLocation, LookDirection)) {
	
	//UE_LOG(LogTemp, Warning, TEXT("World Direction : %s"), *LookDirection.ToString());

		//ray-cast out to reach distance
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
		
	
	}
	else {
		return false;
	}

	
	

}

bool ATankPlayerController::GetLookDirection(FVector2D CrosshairLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation; //to be discarded
	return DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, CameraWorldLocation, LookDirection);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{

	FHitResult Hit;
	HitLocation = FVector::ZeroVector;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	bool Result;
	//	FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetControlledTank());
	Result =  GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);
	if (Result) {
	
		HitLocation = Hit.Location;

	}
	//DrawDebugLine(GetWorld(), StartLocation, LookDirection * LineTraceRange, FColor::Red, false, 1.0F, 0, 5);
	return Result;
	
}

