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
	void BeginPlay() override;
	ATank* GetControlledTank() const;
	
};
