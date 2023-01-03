// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "WeaponStatLibrary.h"

#include "WeaponInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEAPON_SYSTEM_API UWeaponInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponInventory();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		TArray<FWeaponInfo>& GetBucket(EAspectType Element, EAmmoType Ammo);

	UFUNCTION(BlueprintCallable)
		bool GetSpaceInBucket(TArray<FWeaponInfo>& Bucket);

	UFUNCTION(BlueprintCallable)
		void AddToBucket(TArray<FWeaponInfo>& Bucket, FWeaponInfo Weapon);

	UFUNCTION(BlueprintCallable)
		void AddToBucketAtIndex(TArray<FWeaponInfo>& Bucket, FWeaponInfo Weapon, int Index);

	UFUNCTION(BlueprintCallable)
		void RemoveFromBucketAtIndex(TArray<FWeaponInfo>& Bucket, int Index);

	UFUNCTION(BlueprintCallable)
		void SwapFromBucket(TArray<FWeaponInfo>& Bucket, int Index);

	UFUNCTION(BlueprintCallable)
		void SwapTraitInBucket(TArray<FWeaponInfo>& Bucket, int Index);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FWeaponInfo> KineticWeaponBucket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FWeaponInfo> EnergyWeaponBucket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FWeaponInfo> HeavyWeaponBucket;
};
