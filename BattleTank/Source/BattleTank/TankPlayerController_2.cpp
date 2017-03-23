// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController_2.h"

void ATankPlayerController_2::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("no player controlled tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controlled: %s"), *(ControlledTank->GetName()));
	}
}

ATank* ATankPlayerController_2::GetControlledTank() const
{
	return Cast<ATank> (GetPawn());
}


