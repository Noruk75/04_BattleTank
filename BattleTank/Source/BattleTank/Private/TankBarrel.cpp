// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
    auto Time = GetWorld()->GetTimeSeconds();
    //UE_LOG(LogTemp, Warning, TEXT("%f: Barrel->Elevate(): %f"), Time, RelativeSpeed);
    auto RelSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
    auto ElevationChange = RelSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    RawNewElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    SetRelativeRotation(FRotator(RawNewElevation, 0, 0));

}
