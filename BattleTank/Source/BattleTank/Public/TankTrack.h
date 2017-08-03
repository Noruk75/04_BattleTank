// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UTankTrack();

    void ApplySidewaysForce();

    virtual void BeginPlay() override;

    // Sets a throttle between -1 and +1
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);

    void DrivingTrack();
	
    // Max force per track, in neutons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 40000.f * 10.f; // Tank = 40ton, 1g accelleration (10m/s/s)

private:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpluse, const FHitResult& Hit);

    float CurrentThrottle = 0;
};
