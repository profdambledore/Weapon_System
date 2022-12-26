// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageNumber.h"
#include "DamageNumberController.h"

// Sets default values
ADamageNumberController::ADamageNumberController()
{

	Core = CreateDefaultSubobject<USceneComponent>(TEXT("Core"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADamageNumberController::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int i = 0; i <= DamageNumbersToSpawn; i++) {
		ADamageNumber* newNumber = GetWorld()->SpawnActor<ADamageNumber>(ADamageNumber::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);
		DamageNumbers.Add(newNumber);
	}
}

// Called every frame
void ADamageNumberController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageNumberController::GetNewDamageNumber(FVector Loc, bool bCrit, int Damage)
{
	for (int i = 0; i <= DamageNumbers.Num() -1; i++) {
		if (DamageNumbers[i]->bInUse == false){
			DamageNumbers[i]->NewDamageNumber(Loc, bCrit, Damage);
			break;
		}
	}
}

