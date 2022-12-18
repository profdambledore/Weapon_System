// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponParent.h"

#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Cameras
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));

	// Setup Weapon ChildActorComponent
	KineticWeaponActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon Component"));

	// Find and store a pointer to the weapon data table
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT("/Game/Weapons/Data/WeaponTable.WeaponTable"));
	if (DTObject.Succeeded()) { WeaponDataTable = DTObject.Object; }

	CurrentWeapons.SetNum(3);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Axis Binds
	PlayerInputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &APlayerCharacter::MoveY);
	PlayerInputComponent->BindAxis("RotateX", this, &APlayerCharacter::RotateX);
	PlayerInputComponent->BindAxis("RotateY", this, &APlayerCharacter::RotateY);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);
	PlayerInputComponent->BindAction("AimDownSight", IE_Pressed, this, &APlayerCharacter::ADS);
	PlayerInputComponent->BindAction("AimDownSight", IE_Released, this, &APlayerCharacter::ADS);

}

bool APlayerCharacter::SetNeweapon(FName ID)
{
	// Find the weapons info
	FWeaponInfo* foundWeapon = WeaponDataTable->FindRow<FWeaponInfo>(ID, "", false);
	if (foundWeapon == nullptr) { return false; }

	// Set the child actor class and cast to the new class
	KineticWeaponActor->SetChildActorClass(foundWeapon->BaseStats.Frame.Class);
	AWeaponParent* nw = Cast<AWeaponParent>(KineticWeaponActor->GetChildActor());
	nw->Player = this;

	// Store the weapon at the correct index in the weapon array
	CurrentWeapons.Insert(nw, 0);

	// Finally, setup the weapon
	nw->SetupWeapon(ID, foundWeapon->BaseStats, foundWeapon->BaseVisual);

	return false;
}

void APlayerCharacter::MoveX(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (a == false)
		{
			// Move on the X axis based on the input's axis value
			AddMovementInput(GetActorForwardVector(), AxisValue, false);
		}
	}
}

void APlayerCharacter::MoveY(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (a == false)
		{
			// Move on the Y axis based on the input's axis value
			AddMovementInput(GetActorRightVector(), AxisValue, false);
		}
	}
}

void APlayerCharacter::RotateX(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (a == false)
		{
			// Rotate on the X axis based on the input's axis value
			AddControllerYawInput(AxisValue);
		}
	}
}

void APlayerCharacter::RotateY(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (a == false)
		{
			// Rotate on the Y axis based on the input's axis value
			AddControllerPitchInput(AxisValue);
		}
	}
}

void APlayerCharacter::Reload()
{
}

void APlayerCharacter::ADS()
{
}

void APlayerCharacter::FireCurrentWeapon()
{
}

// Swapping Functions
void APlayerCharacter::SwapNext()
{
	if ((CurrentWeaponIndex + 1) >= 3) {
		NewWeaponIndex = 0;
		StowCurrentWeapon();
	}
	else {
		NewWeaponIndex = CurrentWeaponIndex + 1;
		StowCurrentWeapon();
	}
}

void APlayerCharacter::SwapPrev()
{
	if ((CurrentWeaponIndex - 1) <= -1) {
		NewWeaponIndex = 2;
		StowCurrentWeapon();
	}
	else {
		NewWeaponIndex = CurrentWeaponIndex - 1;
		StowCurrentWeapon();
	}
}

void APlayerCharacter::SwapTo(int Index)
{
	if (Index != CurrentWeaponIndex) { NewWeaponIndex = Index; };	
}

void APlayerCharacter::SwapToWeapon(int Index)
{
	FAttachmentTransformRules attachRulesA(EAttachmentRule::SnapToTarget, false);
	CurrentWeapons[CurrentWeaponIndex]->AttachToComponent(GetMesh(), attachRulesA, "");

	FAttachmentTransformRules attachRulesB(EAttachmentRule::KeepRelative, false);
	CurrentWeapons[Index]->AttachToComponent(GetMesh(), attachRulesB, "");
	CurrentWeaponIndex = Index;
}