// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

    if (!ensure(PlayerTank && AimingComponent)) { return; }
    // Move towards player
    MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    // fire if ready
    AimingComponent->Fire();

}


