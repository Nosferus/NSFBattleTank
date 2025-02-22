// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//Must be the last include

//Forward Declarations
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintImplementableEvent, category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);

private:
	UFUNCTION()
	void OnTankDeath();

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3f;
	//FVector2D ScreenLocation;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;
	
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void AimTowardsCrosshair();

	//Return an out parameter, true if hit lanscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UTankAimingComponent* AimingComponent;
};
