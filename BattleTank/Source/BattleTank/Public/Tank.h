// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Fire();

    void AimAt(FVector HitLocation);

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
    UTankAimingComponent* TankAimingComponent = nullptr;

private:	

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.f;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.f;
    
    // Local barrel reference for spawning projectile
    UTankBarrel* Barrel = nullptr;
    
    
    double LastFireTime = 0;
};
