// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponParent.h"

#include "DamageableInterface.h"
#include "DamageNumberController.h"
#include "PlayerCharacter.h"

// Sets default values
AWeaponParent::AWeaponParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Default Sub-Objects
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Magazine = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Magazine"));
}

// Called when the game starts or when spawned
void AWeaponParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeaponParent::SetupWeapon(FName NewID, FWeaponStats NewStats, FWeaponVisual NewVisual)
{
	// Set the stats and magazine
	Stats = NewStats;
	CurrentMagazine = Stats.Magazine;

	// Set the visuals of the weapon
	Body->SetSkeletalMesh(NewVisual.BodyMesh);
	Magazine->SetSkeletalMesh(NewVisual.MagazineMesh);

	return true;
}

float AWeaponParent::GetDamageFromRange(float TraceDistance)
{
	float dist = Stats.Frame.Range.Dropoff->GetFloatValue(Stats.Range) * 1000;
	if (TraceDistance <= dist) {
		return Stats.Frame.Imapct.Damage;
	}
	else if (TraceDistance <= dist + Stats.Frame.Range.EndDist) {
		return (FMath::Lerp(Stats.Frame.Imapct.Damage, Stats.Frame.Imapct.DropoffDamage, (TraceDistance - dist) / Stats.Frame.Range.EndDist));
	}
	else {
		return Stats.Frame.Imapct.DropoffDamage;
	}
}

bool AWeaponParent::FireBullet()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing Bullet"))
	// Trace Properties
	FHitResult hitResult(ForceInit);
	FVector start = Player->FirstPersonCamera->GetComponentLocation();
	FVector end = start + (Player->FirstPersonCamera->GetForwardVector() * 20000);

	FCollisionQueryParams traceParams = FCollisionQueryParams();
	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;

	bool bhitsomething;
	// Complete Trace
	bhitsomething = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		start,
		end,
		ECC_GameTraceChannel1,
		traceParams
	);

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,
			UKismetStringLibrary::Conv_NameToString(hitResult.BoneName));
	}

	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 2.0f, 0, 4.0f);
	CurrentMagazine--;

	// Check if the target is a damageable
	bool bDead;
	IDamageableInterface* inf = Cast<IDamageableInterface>(hitResult.Actor);
	if (inf) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Damageable"));
		
		// Calculate the damage to deal
		bool bIsCrit;
		float outDMG = GetDamageFromRange(hitResult.Distance);
		if (hitResult.BoneName == FName("head")) { 
			outDMG = outDMG * Stats.Frame.Imapct.CritMulti; 
			bIsCrit = true;
		}
		else { bIsCrit = false; }

		// Damage the target
		bDead = inf->TakeAspectDamage(outDMG, EAspectType::Bullet);
		Player->DamageNumberCtrl->GetNewDamageNumber(hitResult.Location, bIsCrit, outDMG);
	};

	return false;
}

void AWeaponParent::StartFire(bool bCantFire)
{
}

void AWeaponParent::ContinueFire()
{
}

bool AWeaponParent::GetCanReload()
{
	if (ReserveAmmo == -1 || ReserveAmmo >= 1) { return true; };

	return false;
}

void AWeaponParent::RefilMagazine()
{
	if (ReserveAmmo == -1) {
		CurrentMagazine = Stats.Magazine;
	}
	else if (Stats.Magazine < CurrentMagazine + ReserveAmmo) {
		ReserveAmmo = (ReserveAmmo + CurrentMagazine) + Stats.Magazine;
		CurrentMagazine = CurrentMagazine + ReserveAmmo;
	}
	else if (Stats.Magazine > CurrentMagazine + ReserveAmmo) {
		CurrentMagazine = CurrentMagazine + ReserveAmmo;
		ReserveAmmo = 0;
	}
}

void AWeaponParent::AddToReserves(int Size)
{
	switch (Size) {
	case 0: // A finder brick
		break;

	case 1: // A normal brick
		break;

	default:
		break;
	}
}

