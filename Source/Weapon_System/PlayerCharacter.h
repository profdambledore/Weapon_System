// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"

#include "WeaponStatLibrary.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class WEAPON_SYSTEM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		bool SetNeweapon(FName ID);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* ThirdPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* ThirdPersonSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UChildActorComponent* KineticWeaponActor;

	// Weapon Data Table
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons")
		UDataTable* WeaponDataTable = nullptr;

	// Weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons")
		TArray <AWeaponParent*> CurrentWeapons;
};
