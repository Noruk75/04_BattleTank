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

    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
    if (TankAimingComponent) {
        TankAimingComponent->SetBarrelReference(BarrelToSet);
    }
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
    if (TankAimingComponent) {
        TankAimingComponent->SetTurretReference(TurretToSet);
    }
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

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
    if (TankAimingComponent) {
        TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
    }
}