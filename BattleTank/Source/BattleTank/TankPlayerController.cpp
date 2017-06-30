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
		GetControlledTank()->AimAt(HitLocation);
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
	FVector LookDirection;
	if (GetLookDirection(Crosshair, LookDirection))
	{	//line trace along that look direction, and see what we hit (up to max range)
		//UE_LOG(LogTemp, Warning, TEXT("World : %s"), *LookDirection.ToString());
		GetLookVectorHitLocation(HitLocation, LookDirection); //OUT hitlocation
	}


	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D Crosshair, FVector& LookDirection) const
{
	FVector Cameraworldloc;
	return DeprojectScreenPositionToWorld(Crosshair.X, Crosshair.Y, Cameraworldloc, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}

