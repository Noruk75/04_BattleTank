// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "tank.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ControlledTank = Cast<ATank>(GetPawn());
    if (ensure(PlayerTank)) {
        // Move towards player
        MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius

        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        // fire if ready
        ControlledTank->Fire();
    }
}


