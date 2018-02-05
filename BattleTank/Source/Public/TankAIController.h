// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

//Forward Declarations
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, category = "Setup")
	float AcceptanceRadius = 8000.0f;
	
private:

	UFUNCTION()
	void OnTankDeath();

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	
	UTankAimingComponent* AimingComponent;

	//ATank* GetControlledTank() const;
	//ATank* GetPlayerTank() const;
};
