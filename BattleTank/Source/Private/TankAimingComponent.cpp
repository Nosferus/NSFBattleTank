// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("Тикаю . . . . . "));

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
		FiringState = EFiringState::Reloading;
	else if (IsBarrelMoving())
		FiringState = EFiringState::Aiming;
	else
		FiringState = EFiringState::Locked;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
		return false;

	FVector BarrelForward = Barrel->GetForwardVector();
	return (!AimDirection.Equals(BarrelForward, 0.1f));
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))
		return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation((FName("Projectile")));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false,
		0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	// Рассчитываем вектор запуска
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowardsAim();
	}
	else		// Если траектория не вычислена, ничего не делаем пока
	{

	}
	
}

void UTankAimingComponent::MoveBarrelTowardsAim()
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}
	//return;
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator прицеливание в %s"), *AimAsRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180.0f)
		Turret->Rotate(DeltaRotator.Yaw);
	else
		Turret->Rotate(-DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint))
		return;

	if (!(FiringState == EFiringState::Reloading))
	{
		//создаём projectile в сокете для стрельбы
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		if (!ensure(Projectile))
			return;
		///UE_LOG(LogTemp, Warning, TEXT("Ку-ку"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}