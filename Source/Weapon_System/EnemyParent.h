// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "DamageableInterface.h"

#include "EnemyParent.generated.h"

UCLASS()
class WEAPON_SYSTEM_API AEnemyParent : public ACharacter, public IDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyParent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual bool TakeAspectDamage(float Damage, EAspectType Type) override;

	// Properties
	// Health
	float MaxHealth;

	float CurrentHealth;

};
