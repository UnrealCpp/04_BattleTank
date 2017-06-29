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
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
		//TODO tell controlled tank to aim at this point
	}

}

// gET WORLD LOCATION OF LINETRACE THROUGH CROSSHAIR, TRUE IF IT HITS LANDSCAPE
bool ATankPlayerController::GetSight(FVector& HitLocation) const
{
	//HitLocation = FVector(1.0);
	//find crosshair
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);//OUT PARAMETER
	
	FVector2D Crosshair;
	Crosshair.X = ViewportSizeX*CrosshairLocX;
	Crosshair.Y = ViewportSizeY*CrosshairLocY;

	//UE_LOG(LogTemp, Warning, TEXT("Crosshair : %s"), *Crosshair.ToString());
	//de project the screen position of the crosshair to a world direction
	FVector Cameraworldloc;
	FVector worldDirection;
	if (DeprojectScreenPositionToWorld(Crosshair.X, Crosshair.Y, Cameraworldloc, worldDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("World : %s"), *worldDirection.ToString());
	}

	//line trace along that look direction, and see what we hit (up to max range)
	return true;
}