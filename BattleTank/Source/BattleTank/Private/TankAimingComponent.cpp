// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    /*auto OurTankName = GetOwner()->GetName();
    auto BarrelLocation = Barrel->GetComponentLocation();
    UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *(HitLocation.ToString()), *(BarrelLocation.ToString()));*/

    if (!Barrel) { return; }
    //UE_LOG(LogTemp, Warning, TEXT("Aiming at Barrel"));

    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    // Calculate the out launch velocity
    
    
    FCollisionResponseParams CollisionResponseParam;
    TArray<AActor*> ActorsToIgnore;
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace, CollisionResponseParam, ActorsToIgnore, true);
    if (bHaveAimSolution) {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f aim solution found"), Time);
    } else {
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f no aim solution"), Time);
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // animate the barrel to allign along the connecting turret socket to the barrel end socket.
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
}