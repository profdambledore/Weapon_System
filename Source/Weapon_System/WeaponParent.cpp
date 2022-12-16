// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponParent.h"

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

bool AWeaponParent::FireBullet()
{
	// Trace Properties
	FHitResult hitResult(ForceInit);
	FVector start = Player->FirstPersonCamera->GetComponentLocation();
	FVector end = start + (Player->FirstPersonCamera->GetForwardVector() * 20000);

	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;

	// Complete Trace
	GetWorld()->LineTraceSingleByChannel(
		hitResult,
		start,
		end,
		ECC_EngineTraceChannel2,
		traceParams
	);


	return false;
}

