// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "tank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    if (ensure(AimingComponent)) {
        FoundAimingComponent(AimingComponent);
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller Can't find aiming component at Begin Play"))
    }
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AimTowardsCrosshair();
}



ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!ensure(GetControlledTank())) { return; }

    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation)) {
        GetControlledTank()->AimAt(HitLocation);
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

    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
        HitLocation = HitResult.Location;
        return true;
    }
    return false;
}
