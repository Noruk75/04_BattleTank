// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"



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
