// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/DataTable.h"
#include "Curves/CurveFloat.h"

#include "WeaponStatLibrary.generated.h"

class AWeaponParent;

UCLASS()
class WEAPON_SYSTEM_API UWeaponStatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};

UENUM()
enum EAmmoType
{
	Primary UMETA(Display Name = "Primary"),
	Special UMETA(Display Name = "Special"),
	Heavy UMETA(Display Name = "Heavy"),
};

UENUM()
enum EAspectType
{
	Bullet UMETA(Display Name = "Bullet"),
	nRG UMETA(Display Name = "nRG"),
};

UENUM()
enum EStatsType
{
	None UMETA(DisplayName = "None"),
	Dropoff UMETA(Display Name = "Dropoff"),
	Draw UMETA(Display Name = "Draw"),
	Stow UMETA(Display Name = "Stow"),
	ADS UMETA(Display Name = "ADS"),
	Reload UMETA(Display Name = "Reload"),
};

UENUM()
enum ETraitType
{
	Barrel UMETA(Display Name = "Barrel"),
};

UENUM()
enum ETriggerType
{
	Hit_Enemy_NoCrit UMETA(Display Name = "Hit_Enemy_NoCrit"),
	Hit_Enemy_Crit UMETA(Display Name = "Hit_Enemy_Crit"),
};

UENUM()
enum EWeaponType
{
	Auto_Rifle UMETA(Display Name = "Auto_Rifle"),
	SMG UMETA(Display Name = "SMG"),
	Sniper UMETA(Display Name = "Sniper"),
};

USTRUCT(BlueprintType)
struct FTriggers
{
	GENERATED_USTRUCT_BODY();

public:

};

USTRUCT(BlueprintType)
struct FImpact : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int RateOfFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Imapct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DropoffDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CritMulti;
};

USTRUCT(BlueprintType)
struct FRange : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* Dropoff;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EndDist;
};

USTRUCT(BlueprintType)
struct FWeaponFrame : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EWeaponType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AWeaponParent> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EAmmoType> Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FImpact Imapct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRange Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* Stability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* Handling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* Reserves;
};

USTRUCT(BlueprintType)
struct FWeaponStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EAspectType> Element;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWeaponFrame Frame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Stability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Handling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Recoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Zoom;
};

USTRUCT(BlueprintType)
struct FTraitStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Stability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Handling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Recoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Zoom;
};

USTRUCT(BlueprintType)
struct FTraitColumn : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
};

USTRUCT(BlueprintType)
struct FWeaponVisual : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* MagazineMesh;
};

USTRUCT(BlueprintType)
struct FWeaponInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWeaponStats BaseStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTraitColumn> BaseTraitTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWeaponVisual BaseVisual;
};

