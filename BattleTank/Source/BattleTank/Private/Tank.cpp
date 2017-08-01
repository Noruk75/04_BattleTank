// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    auto TankName = GetName();
    UE_LOG(LogTemp, Warning, TEXT("CARA: %s Tank Constructor"), *TankName);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    auto TankName = GetName();
    UE_LOG(LogTemp, Warning, TEXT("CARA: %s Tank Begin Play"), *TankName);
}

void ATank::Fire()
{
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
    if (Barrel && isReloaded) {
        // spawn a projectile at the barrel socket location
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            Barrel->GetSocketLocation(FName("Projectile")),
            Barrel->GetSocketRotation(FName("Projectile")));

        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
}


void ATank::AimAt(FVector HitLocation)
{
    if (TankAimingComponent) {
        TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
    }
}