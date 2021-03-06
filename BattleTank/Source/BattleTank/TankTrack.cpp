// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {

	auto Name = GetName();
	
	auto ForceApplied =GetForwardVector() * Throttle * TrackMaxDrivingForce;
	//UE_LOG(LogTemp, Warning, TEXT("%s Force applied: %f "), *Name, Throttle)

	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

