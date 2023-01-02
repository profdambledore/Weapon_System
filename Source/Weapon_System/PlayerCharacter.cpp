// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponParent.h"
#include "DamageNumberController.h"

#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Cameras
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetRelativeLocation(FVector(10.0f, 0.0f, 90.0f));

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));

	// Setup Weapon ChildActorComponent
	KineticWeaponActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Kinetic Weapon Component"));
	EnergyWeaponActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Energy Weapon Component"));
	HeavyWeaponActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Heavy Weapon Component"));

	ActiveWeaponLoc = CreateDefaultSubobject<USceneComponent>(TEXT("Active Weapon Location"));
	ActiveWeaponLoc->SetRelativeLocation(FVector(30.0f, 20.0f, 70.0f));

	WeaponBackL = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Back Left"));
	WeaponBackR = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Back Right"));

	// Attach the scene components to the mesh
	ActiveWeaponLoc->SetupAttachment(GetMesh());
	WeaponBackL->SetupAttachment(GetMesh());
	WeaponBackR->SetupAttachment(GetMesh());

	// Find and store a pointer to the weapon data table
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT("/Game/Weapons/Data/Weapon.Weapon"));
	if (DTObject.Succeeded()) { WeaponDataTable = DTObject.Object; }

	// Do the same for the recoil curve
	ConstructorHelpers::FObjectFinder<UCurveFloat>RDObject(TEXT("/Game/Weapons/Data/C_RecoilDirection.C_RecoilDirection"));
	if (RDObject.Succeeded()) { RecoilCurve = RDObject.Object; }

	CurrentWeapons.SetNum(3);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Attach weapons to slots
	FAttachmentTransformRules attachRules(EAttachmentRule::SnapToTarget, false);
	KineticWeaponActor->AttachToComponent(GetMesh(), attachRules, "GripPoint");
	EnergyWeaponActor->AttachToComponent(WeaponBackL, attachRules, "");
	HeavyWeaponActor->AttachToComponent(WeaponBackR, attachRules, "");

	// Find a damage number controller in the world and store it's pointer
	DamageNumberCtrl = Cast<ADamageNumberController>(UGameplayStatics::GetActorOfClass(GetWorld(), ADamageNumberController::StaticClass()));

	// Set the weapon rest location (WeaponLoc)
	WeaponLoc = ActiveWeaponLoc->GetRelativeLocation();

	SetNeweapon(FName("AR_AD_001"));
	SetNeweapon(FName("SMG_LW_001"));
	SetNeweapon(FName("SR_AD_001"));
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
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::FireCurrentWeapon);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::FireCurrentWeapon);
	PlayerInputComponent->BindAction("SwapNext", IE_Pressed, this, &APlayerCharacter::SwapNext);
	PlayerInputComponent->BindAction("SwapPrevious", IE_Pressed, this, &APlayerCharacter::SwapPrev);
}

bool APlayerCharacter::SetNeweapon(FName ID)
{
	//
	int sI;
	UChildActorComponent* cA;

	// Find the weapons info
	FWeaponInfo* foundWeapon = WeaponDataTable->FindRow<FWeaponInfo>(ID, "", false);
	if (foundWeapon == nullptr) { return false; }
	foundWeaponStat = foundWeapon->BaseStats;

	// Get the correct slot to set
	if (foundWeapon->BaseStats.Frame.Ammo == EAmmoType::Heavy){
		cA = HeavyWeaponActor;
		sI = 2;
	}
	else if (foundWeapon->BaseStats.Element != EAspectType::Bullet){
		cA = EnergyWeaponActor;
		sI = 1;
	}
	else{
		cA = KineticWeaponActor;
		sI = 0;
	}

	// Set the child actor class and cast to the new class
	cA->SetChildActorClass(foundWeaponStat.Frame.Class);
	AWeaponParent* nw = Cast<AWeaponParent>(cA->GetChildActor());
	if (nw != nullptr) { UE_LOG(LogTemp, Warning, TEXT("not null")); }
	nw->Player = this;

	// Store the weapon at the correct index in the weapon array
	CurrentWeapons.Insert(nw, sI);

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
	if (CurrentWeapons[CurrentWeaponIndex]->GetCanReload()){
		VisualReload();
	}
}

void APlayerCharacter::ADS()
{
	AimDownSight();
}

void APlayerCharacter::FireCurrentWeapon()
{
	if (bFireHeld == false) { bFireHeld = true; }
	else { bFireHeld = false; }
	if (bInReload != true && bInStowDraw != true) {
		CurrentWeapons[CurrentWeaponIndex]->StartFire(bFireHeld);
	}
}

// Swapping Functions
void APlayerCharacter::SwapNext()
{
	if ((CurrentWeaponIndex + 1) >= 3) {
		NewWeaponIndex = 0;
		StowCurrentWeapon(NewWeaponIndex);
	}
	else {
		NewWeaponIndex = CurrentWeaponIndex + 1;
		StowCurrentWeapon(NewWeaponIndex);
	}
}

void APlayerCharacter::SwapPrev()
{
	if ((CurrentWeaponIndex - 1) <= -1) {
		NewWeaponIndex = 2;
		StowCurrentWeapon(NewWeaponIndex);
	}
	else {
		NewWeaponIndex = CurrentWeaponIndex - 1;
		StowCurrentWeapon(NewWeaponIndex);
	}
}

void APlayerCharacter::SwapTo(int Index)
{
	if (Index != CurrentWeaponIndex) { NewWeaponIndex = Index; };	
}

void APlayerCharacter::SwapToWeapon(int Index)
{
	CurrentWeaponIndex = Index;

	// Make attach data
	FAttachmentTransformRules attachRules(EAttachmentRule::SnapToTarget, false);

	// Attach the new weapon to the ActiveWeapon component
	bool bfirstslot = false;
	switch (Index) {
	case 0: // Kinetic to set held
		KineticWeaponActor->AttachToComponent(GetMesh(), attachRules, "GripPoint");
		EnergyWeaponActor->AttachToComponent(WeaponBackL, attachRules, "");
		HeavyWeaponActor->AttachToComponent(WeaponBackR, attachRules, "");
		break;

	case 1: // Energy to set held
		EnergyWeaponActor->AttachToComponent(GetMesh(), attachRules, "GripPoint");
		KineticWeaponActor->AttachToComponent(WeaponBackL, attachRules, "");
		HeavyWeaponActor->AttachToComponent(WeaponBackR, attachRules, "");
		break;

	case 2: // Heavy to set held
		HeavyWeaponActor->AttachToComponent(GetMesh(), attachRules, "GripPoint");
		KineticWeaponActor->AttachToComponent(WeaponBackL, attachRules, "");
		EnergyWeaponActor->AttachToComponent(WeaponBackR, attachRules, "");
		break;

	default:
		break;
	}
}