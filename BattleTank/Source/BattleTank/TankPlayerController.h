// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;
    
    ATank* GetControlledTank() const;
	
    // Start the tank moving the barrel so that a 
    // shot would hit where the crosshair intersect the world.
    void AimTowardsCrosshair();
	
    bool GetSightRayHitLocation(FVector &HitLocation);

    bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
    bool GetLookVectorHitLocation(FVector LookLocation, FVector &HitLocation) const;

    UPROPERTY(EditAnywhere)
    double CrossHairXLocation = 0.5;
    
    UPROPERTY(EditAnywhere)
    double CrossHairYLocation = 1.0 / 3.0;

    UPROPERTY(EditAnywhere)
    double LineTraceRange = 1000000.f;
};
