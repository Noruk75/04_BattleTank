// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked,
    OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;


// Holds Barrel's Properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    void AimAt(FVector HitLocation);
    void MoveBarrelTowards(FVector AimDirection);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Fire();

    EFiringState GetFiringState() const;

    UFUNCTION(BlueprintCallable, Category = "Setup")
    int32 GetRoundsLeft() const;

protected:

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;

    virtual void BeginPlay() override;

private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    bool IsBarrelMoving();

    // Local barrel reference for spawning projectile
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.f;

    double LastFireTime = 0;

    FVector AimDirection = FVector(0);

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 RoundsLeft = 3;
};
