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
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Posessed Tank"));
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }


}
