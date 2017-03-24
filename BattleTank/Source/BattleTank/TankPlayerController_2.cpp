// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController_2.h"

void ATankPlayerController_2::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("no player controlled tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controlled: %s"), *(ControlledTank->GetName()));
	}
	return;
}

// Called every frame
void ATankPlayerController_2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	return;
}

ATank* ATankPlayerController_2::GetControlledTank() const
{
	return Cast<ATank> (GetPawn());
}

void ATankPlayerController_2::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) //if hit landscape
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

//Line trace trough crosshair true if hits location
bool ATankPlayerController_2::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	FVector LookDirection;
	
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line trace along that direction 		//See what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection,HitLocation);
	}
	return true;
}

//Deproject the screen prosition of crosshair to world position
bool ATankPlayerController_2::GetLookDirection(FVector2D &ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController_2::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection*LineTraceRange;
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(255, 0, 0), false, -1, 0, 12.333);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
		))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else { 
		HitLocation = FVector(0., 0., 0.);
		return false; 
	}
}
