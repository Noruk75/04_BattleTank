// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

    UE_LOG(LogTemp, Warning, TEXT("CARA: Tank Aiming Component Constructor"));
}


void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    if (!Barrel || !Turret) { return; }

    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    // Calculate the out launch velocity
    
    FCollisionResponseParams CollisionResponseParam;
    TArray<AActor*> ActorsToIgnore;
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace, CollisionResponseParam, ActorsToIgnore, false);
    if (bHaveAimSolution) {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
        //auto Time = GetWorld()->GetTimeSeconds();
        //UE_LOG(LogTemp, Warning, TEXT("%f aim solution found"), Time);
    }
    // No aim solution found
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    if (!Barrel || !Turret) { return; }
    // animate the barrel to allign along the connecting turret socket to the barrel end socket.
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Rotate(DeltaRotator.Yaw);

}