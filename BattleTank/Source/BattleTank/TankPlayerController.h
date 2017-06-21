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

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		//start the tank moving barrel against to crosshair
		void AimTowardsCrosshair();

		ATank* GetControlledTank() const;

		virtual void BeginPlay() override;
	
};
