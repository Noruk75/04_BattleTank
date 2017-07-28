// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    ATank* GetControlledTank() const;
    ATank* GetPlayerTank() const;


    // Start the tank moving the barrel so that a 
    // shot would hit where the crosshair intersect the world.
    void AimTowardsPlayer();

};
