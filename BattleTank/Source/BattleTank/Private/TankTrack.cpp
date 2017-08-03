// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
    
}

void UTankTrack::BeginPlay()
{
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::ApplySidewaysForce()
{
    // Work out the required accelleration this frame to correct
    auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

    // Calculate and apply sideways force (F = m a)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // two tracks

    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
    
}

void UTankTrack::DrivingTrack()
{
    //TODO clamp actual throttle value so player can't over drive
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpluse, const FHitResult& Hit)
{
    DrivingTrack();
    ApplySidewaysForce();
    CurrentThrottle = 0.f;
}
