// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("Player Controller tick"))
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Not Posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Posessing: %s"),*(ControlledTank->GetName()));
	}
}



ATank* ATankPlayerController::GetControlledTank() const
{
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Posessed Tank"));
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	                      
	FVector HitLocation;	//OUT Parameter
	//FRotator HitRotation;
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(HitLocation, HitRotation);
	//UE_LOG(LogTemp, Warning, TEXT("hitLoc: %s"), *HitLocation.ToString());
	//FVector LineTraceEnd = HitLocation + HitRotation.Vector() * 100;
	if (GetSight(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("hitLoc: %s"), *HitLocation.ToString());
		//TODO tell controlled tank to aim at this point
	}

}

bool ATankPlayerController::GetSight(FVector& HitLocation) const
{
	HitLocation = FVector(1.0);
	return true;
}