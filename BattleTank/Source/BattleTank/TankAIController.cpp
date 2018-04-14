// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::Tick(float DeltaTime)
{
	if (!ControlledTank) {
		return;
	}
	AimTowardsPlayer();

	ControlledTank->Fire();

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ControlledTank = Cast<ATank>(GetPawn());

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Reporting: tank pawn is not found"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Reporting: tank pawn is: %s"), *ControlledTank->GetName())
	}
	
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Reporting: player pawn is not found"))
	} else {
	UE_LOG(LogTemp, Warning, TEXT("AI Reporting: player pawn is: %s"), *PlayerTank->GetName())
	}

	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::AimTowardsPlayer()
{
	if (PlayerTank) {

		//TODO move towards player

		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire if ready to fire
	}

}

