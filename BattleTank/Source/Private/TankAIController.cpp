// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
///#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!ensure(PlayerTank))
		return;
	
	MoveToActor(PlayerTank, AcceptanceRadius);
		
	if (!ensure(AimingComponent))
		return;

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
		AimingComponent->Fire();
	
}

