// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    auto TankName = GetOwner()->GetName();
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();

    float ForwardIntention = FVector::DotProduct(TankForward, AIForwardIntention);
    float TurnIntention = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

    IntendTurn(TurnIntention);
    IntendMoveForward(ForwardIntention);

    //UE_LOG(LogTemp, Warning, TEXT("%f, %f"), TurnIntention, ForwardIntention)
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
    // TODO prevent double speed
}

/*void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if (!LeftTrack || !RightTrack) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
    // TODO prevent double speed
}*/

void UTankMovementComponent::IntendTurn(float Throw)
{
    if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
    // TODO prevent double speed
}