// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Not Posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Posessing: %s"), *(ControlledTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Posessed Tank"));
	return Cast<ATank>(GetPawn());
}
