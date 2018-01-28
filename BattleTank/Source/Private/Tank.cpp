// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
///#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// ��� ������������� �������� ���������, �.�. ��� ����������� ��� ��������
//	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
//	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //���������� ��� ����, ����� ������������ BeginPlay � BP
	//auto TankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("NSF C++: ���� %s ����� ����"), *TankName);

///	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}
/*
void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) return;
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
*/
void ATank::Fire()
{
	if (!ensure(Barrel))
		return;
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	//UE_LOG(LogTemp, Warning, TEXT("��-��"));
	if (IsReloaded)
	{
		//������ projectile � ������ ��� ��������
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
