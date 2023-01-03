// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInventory.h"

// Sets default values for this component's properties
UWeaponInventory::UWeaponInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponInventory::BeginPlay()
{
	Super::BeginPlay();

	// Limit bucket amounts
	KineticWeaponBucket.SetNum(10);
	EnergyWeaponBucket.SetNum(10);
	HeavyWeaponBucket.SetNum(10);
}


// Called every frame
void UWeaponInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FWeaponInfo>& UWeaponInventory::GetBucket(EAspectType Element, EAmmoType Ammo)
{
	if (Ammo == EAmmoType::Heavy) {
		return HeavyWeaponBucket;
	}
	else if (Element == EAspectType::Bullet) {
		return KineticWeaponBucket;
	}
	else {
		return EnergyWeaponBucket;
	}
}

bool UWeaponInventory::GetSpaceInBucket(TArray<FWeaponInfo>& Bucket)
{
	if (Bucket.Num() <= 9) { 
		return true;
	}
	else { 
		return false;
	}
}

void UWeaponInventory::AddToBucket(TArray<FWeaponInfo>& Bucket, FWeaponInfo Weapon)
{
	Bucket.Add(Weapon);
}

void UWeaponInventory::AddToBucketAtIndex(TArray<FWeaponInfo>& Bucket, FWeaponInfo Weapon, int Index)
{
	Bucket.Insert(Weapon, Index);
}

void UWeaponInventory::RemoveFromBucketAtIndex(TArray<FWeaponInfo>& Bucket, int Index)
{
	Bucket.RemoveAt(Index);
}

void UWeaponInventory::SwapFromBucket(TArray<FWeaponInfo>& Bucket, int Index)
{
	FWeaponInfo oldEquip = Bucket[0];
	Bucket[0] = Bucket[Index];
	Bucket[Index] = oldEquip;
	// Player->SetNewWeapon(Bucket[0]);
}

void UWeaponInventory::SwapTraitInBucket(TArray<FWeaponInfo>& Bucket, int Index)
{
}

