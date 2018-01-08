// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

// Вызывается каждый кадр
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("TimeElapsed %i"), DeltaTime)
	AimTowardsCrosshair();
}

// Вызывается один раз в начале игры
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Not Possessing a Tank"))
	else 
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(ControlledTank->GetName()));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
		return;

	FVector HitLocation; //Out param
	GetSightRayHitLocation(HitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Находим экранные координаты прицела в пикселях и помещаем в ScreenLocation.
	//Информация о положении курсора в долях единицы содержится в переменных CrosshairXLocation и CrosshairYLocation
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
		UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *LookDirection.ToString());

	//Выполняем депроекцию положения курсора
//	FVector WorldDirection, CamWorldLocation;
//	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CamWorldLocation, WorldDirection))
//		UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *WorldDirection.ToString())
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CamWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CamWorldLocation, LookDirection);
}