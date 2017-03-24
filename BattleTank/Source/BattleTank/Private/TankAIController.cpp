// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
//#include "..\Public\TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto AIControlledTank = GetControlledTank();
	auto PlayerControlledTank = GetPlayerTank();
	if (!AIControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("no ai controlled tank"));
	}
	else if (!PlayerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("no player controlled tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIcontrolled: %s   looks at: %s"), *AIControlledTank->GetName(), *PlayerControlledTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
	return;
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank> (GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank> (GetWorld()->GetFirstPlayerController()->GetPawn());
}


