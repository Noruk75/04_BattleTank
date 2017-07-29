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
    if (PlayerTank) {
        //TODO move towards player
        
        
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        // fire if ready
        ControlledTank->Fire();
    }
}


