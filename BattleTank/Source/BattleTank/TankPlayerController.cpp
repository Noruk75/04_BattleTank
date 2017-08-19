// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    FoundAimingComponent(AimingComponent);
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn) {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }

        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
    }
}

void ATankPlayerController::OnTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("Player Tank Dead"));
    StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn()) { return; }
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }

    FVector HitLocation;
    auto bGotHitLocation = GetSightRayHitLocation(HitLocation);
    if (bGotHitLocation) {
        AimingComponent->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation)
{
    //Find the crosshair position
    int32 ViewPortSizeX, ViewPortSizeY;
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);
    auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

    // "De-project" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection)) {
        return GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X, 
        ScreenLocation.Y, 
        CameraWorldLocation, 
        LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
    // Line-trace along that look direction, and see what we hit (up to a max range)
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera)) {
        HitLocation = HitResult.Location;
        return true;
    }
    return false;
}
