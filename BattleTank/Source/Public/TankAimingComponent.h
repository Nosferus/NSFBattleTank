// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Состояние прицеливания
UENUM()
enum class EFiringState:uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};


//Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void Fire();

	EFiringState GetFiringState() const { return FiringState; }

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int GetAmmoLeft() const { return AmmoLeft; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();

	UPROPERTY(EditAnywhere, Category = "firing")
	float LaunchSpeed = 8000; //80 м/с

	void MoveBarrelTowardsAim();

	UPROPERTY(EditDefaultsOnly, category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "firing")
	float ReloadTime = 3.0f;

	double LastFireTime = 0.0f;

	int AmmoLeft = 5;

	FVector AimDirection;
};
