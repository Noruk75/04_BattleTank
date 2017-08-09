// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    //UE_LOG(LogTemp, Warning, TEXT("CARA: Tank Aiming Component Constructor"));
}

void UTankAimingComponent::BeginPlay()
{
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    if (RoundsLeft <= 0) {
        FiringState = EFiringState::OutOfAmmo;
    } else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
        FiringState = EFiringState::Reloading;
    } else if (IsBarrelMoving()) {
        FiringState = EFiringState::Aiming;
    } else {
        FiringState = EFiringState::Locked;
    }
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure(Barrel)) { return false; }
    return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01);
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Barrel) || !ensure(Turret)) { return; }

    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    // Calculate the out launch velocity
    
    FCollisionResponseParams CollisionResponseParam;
    TArray<AActor*> ActorsToIgnore;
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace, CollisionResponseParam, ActorsToIgnore, false);
    if (bHaveAimSolution) {
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
        //auto Time = GetWorld()->GetTimeSeconds();
        //UE_LOG(LogTemp, Warning, TEXT("%f aim solution found"), Time);
    }
    // No aim solution found
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    if (!ensure(Barrel) || !ensure(Turret)) { return; }
    // animate the barrel to allign along the connecting turret socket to the barrel end socket.
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
    //Turret->Rotate(DeltaRotator.Yaw);

    // Always rotate the shortest way, even if crossing the axis from pos-to-neg or neg-to-pos
    if (DeltaRotator.Yaw < -180) {
        Turret->Rotate(DeltaRotator.Yaw + 360);
    } else if (DeltaRotator.Yaw > 180) {
        Turret->Rotate(DeltaRotator.Yaw - 360);
    } else {
        Turret->Rotate(DeltaRotator.Yaw);
    }

    /*if (FMath::Abs(DeltaRotator.Yaw) < 180) {
        Turret->Rotate(DeltaRotator.Yaw);
    } else {
        Turret->Rotate(-DeltaRotator.Yaw);
    }*/

}


void UTankAimingComponent::Fire()
{
    if ((FiringState == EFiringState::Aiming) || (FiringState == EFiringState::Locked)) {
        // spawn a projectile at the barrel socket location
        if (!ensure(Barrel)) { return; }
        if (!ensure(ProjectileBlueprint)) { return; }
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            Barrel->GetSocketLocation(FName("Projectile")),
            Barrel->GetSocketRotation(FName("Projectile")));

        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
        RoundsLeft--;
    }
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
    return RoundsLeft;
}
