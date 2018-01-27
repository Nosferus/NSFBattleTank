// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"	//ƒолжен быть в конце

//Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "firing")
	float LaunchSpeed = 8000; //80 м/с

	UPROPERTY(EditAnywhere, Category = "firing")
	float ReloadTime = 3.0f;

	//местна€ ссылка дл€ спауна Projectile
	UTankBarrel* Barrel = nullptr;  //TODO Remove

	
	double LastFireTime = 0.0f;
};
