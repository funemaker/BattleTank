// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) {
		return;
	}
	Barrel = BarrelToSet;
	UE_LOG(LogTemp, Warning, TEXT("Set barrel reference"));
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) {
		return;
	}
	Turret = TurretToSet;
	UE_LOG(LogTemp, Warning, TEXT("Set turret reference"));
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto OurTankName = GetOwner()->GetName();
	if (!Barrel) {
		return;
	}
	FVector TossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		TossVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution) {
	//	auto Time = GetWorld()->GetTimeSeconds();
	//	UE_LOG(LogTemp, Warning, TEXT("%f: have aim solution"), Time)
	
		//only log if success
		auto DesiredAimDirection = TossVelocity.GetSafeNormal();
		//Barrel->SetRelativeRotation(DesiredAimDirection.Rotation());
		MoveBarrelTowards(DesiredAimDirection);

	//	UE_LOG(LogTemp, Warning, TEXT("%s Firing with speed of %s"), *GetOwner()->GetName(), *DesiredAimDirection.ToString());
	//	UE_LOG(LogTemp, Warning, TEXT("%s Firing at %s from %s"), *GetOwner()->GetName(), *HitLocation.ToString(), *StartLocation.ToString());

	}
	
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("Aim as rotator %s"), *AimAsRotator.ToString())
}

