// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"//must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
		ATank* GetControlledTank() const;				

		virtual void BeginPlay() override;		

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		//start the tank moving barrel against to crosshair
		void AimTowardsCrosshair();

		//return out
		bool GetSight(FVector& HitLocation) const;

		UPROPERTY(EditAnywhere)
			float CrosshairLocX = 0.5;
		UPROPERTY(EditAnywhere)
			float CrosshairLocY = 0.33333;

		bool GetLookDirection(FVector2D Crosshair, FVector& LookDirection) const;

		bool GetLookVectorHitLocation(FVector& HitLocation,FVector LookDirection) const;

		UPROPERTY(EditAnywhere)
			float LineTraceRange=10000.0;
};
