// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "tank.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a tank"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("AIController possesing : %s"), *(ControlledTank->GetName()));
    }

    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerTank not found"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerTank found: %s"), *(PlayerTank->GetName()));
    }

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (GetPlayerTank()) {
        //TODO move towards player
        AimTowardsPlayer();

        // fire if ready
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn) { return nullptr; }
    return Cast<ATank>(PlayerPawn);
}


void ATankAIController::AimTowardsPlayer()
{
    if (!GetControlledTank()) { return; }

    GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}


