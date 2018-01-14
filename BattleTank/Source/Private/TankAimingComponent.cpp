// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent *BarrelToSet)
void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel)
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation((FName("Projectile")));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	// ������������ ������ �������
	if (bHaveAimSolution)
	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//auto OurTankName = GetOwner()->GetName();
		//auto BarrelLocation = Barrel->GetComponentLocation();
	//	UE_LOG(LogTemp, Warning, TEXT("%s ������� � %s �� %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
	//	auto TankName = GetOwner()->GetName();// .ToString();
	//	UE_LOG(LogTemp, Warning, TEXT("%s : ������������ � %s"), *TankName, *AimDirection.ToString());

		MoveBarrelTowardsAim(AimDirection);

		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f:������� ��� ���� �������"), Time);

	}
	else			// ���� ���������� �� ���������, ������ �� ������ ����
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f:�� ������� ������� ��� ����"), Time);
	}
	
}

void UTankAimingComponent::MoveBarrelTowardsAim(FVector AimDirection)
{
	//return;
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();

	auto DeltaRotator = AimAsRotator - BarrelRotation;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator ������������ � %s"), *AimAsRotator.ToString());

	Barrel->Elevate(5);
}