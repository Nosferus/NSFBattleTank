// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, category = Moving)
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditAnywhere, category = Setup)
	float TrackMaxDrivingForce = 400000.0f;	//Сила в Н при весе танка 40 т
};
