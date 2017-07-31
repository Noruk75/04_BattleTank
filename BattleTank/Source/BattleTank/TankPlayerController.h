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

protected:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    ATank* GetControlledTank() const;


private:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;
    
	
    // Start the tank moving the barrel so that a 
    // shot would hit where the crosshair intersect the world.
    void AimTowardsCrosshair();
	
    bool GetSightRayHitLocation(FVector &HitLocation);

    bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
    bool GetLookVectorHitLocation(FVector LookLocation, FVector &HitLocation) const;

    UPROPERTY(EditDefaultsOnly)
    double CrossHairXLocation = 0.5;
    
    UPROPERTY(EditDefaultsOnly)
    double CrossHairYLocation = 1.0 / 3.0;

    UPROPERTY(EditDefaultsOnly)
    double LineTraceRange = 1000000.f;
};
