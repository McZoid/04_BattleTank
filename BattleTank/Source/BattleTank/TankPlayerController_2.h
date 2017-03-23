// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController_2.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController_2 : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	void Tick(float DeltaTime) override;

	//Called at start of game
	void BeginPlay() override;
private:
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
	
	bool GetLookDirection(FVector2D &ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
