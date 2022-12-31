// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"
#include "Kismet/GameplayStatics.h"

#include "WeaponStatLibrary.h"

#include "PlayerCharacter.generated.h"

class ADamageNumberController;

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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void AimDownSight();

	UFUNCTION(BlueprintImplementableEvent)
		void VisualReload();

	UFUNCTION(BlueprintImplementableEvent)
		void CancelReload();

	UFUNCTION(BlueprintImplementableEvent)
		void VisualRecoil();

	UFUNCTION(BlueprintImplementableEvent)
		void SetADSSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable)
		void SwapToWeapon(int Index);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void StowCurrentWeapon(int Index);

	void Reload();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Player Movement
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void RotateX(float AxisValue);
	void RotateY(float AxisValue);

	// Player Interaction
	void ADS();
	void FireCurrentWeapon();
	void SwapNext();
	void SwapPrev();
	void SwapTo(int Index);


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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UChildActorComponent* EnergyWeaponActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UChildActorComponent* HeavyWeaponActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* ActiveWeaponLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* WeaponBackL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* WeaponBackR;

	// Weapon Data Table
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data Table")
		UDataTable* WeaponDataTable = nullptr;

	// Weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray <AWeaponParent*> CurrentWeapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		int CurrentWeaponIndex = 0;

	FWeaponStats foundWeaponStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons")
		ADamageNumberController* DamageNumberCtrl;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons")
		FVector WeaponLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Tests")
		bool bInReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Tests")
		bool bInStowDraw;

	int NewWeaponIndex;

	bool bFireHeld = false;
	bool a = false;
};
