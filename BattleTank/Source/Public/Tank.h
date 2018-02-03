// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"	//Должен быть в конце

//Forward Declarations


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

protected:

private:
	// Sets default values for this pawn's properties
	ATank();
	
	UPROPERTY(EditAnywhere, category = "Setup")
	int32 MaxHealth = 100;
	UPROPERTY(VisibleAnywhere, category = "Info")
	int32 CurrentHealth;

	// Called when the game starts or when spawned
///	virtual void BeginPlay() override;

};
