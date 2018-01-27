// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// ��� ������������� �������� ���������, �.�. ��� ����������� ��� ��������
//	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
//	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("NSF C++: ���� %s ������"), *TankName);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //���������� ��� ����, ����� ������������ BeginPlay � BP
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("NSF C++: ���� %s ����� ����"), *TankName);
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) return;
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	if (Barrel && IsReloaded)
	{
		//������ projectile � ������ ��� ��������
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
