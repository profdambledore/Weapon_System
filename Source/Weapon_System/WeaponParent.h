// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SkeletalMeshComponent.h"
#include "WeaponStatLibrary.h"

#include "WeaponParent.generated.h"

UCLASS()
class WEAPON_SYSTEM_API AWeaponParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponParent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		bool SetupWeapon(FName NewID, FWeaponStats NewStats, FWeaponVisual NewVisual);

	UFUNCTION(BlueprintCallable)
		bool FireBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Barrel;

	// Properties
	// Weapon Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		FWeaponStats Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		int CurrentMagazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
		int ReserveAmmo;

	// Player Data
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class APlayerCharacter* Player = nullptr;
};
