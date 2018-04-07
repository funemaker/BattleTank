// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Reporting: tank pawn is not found"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Reporting: tank pawn is: %s"), *ControlledTank->GetName())
	}
	
	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Reporting: player pawn is not found"))
	} else {
	UE_LOG(LogTemp, Warning, TEXT("AI Reporting: player pawn is: %s"), *PlayerTank->GetName())
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
