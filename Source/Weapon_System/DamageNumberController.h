// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DamageNumberController.generated.h"

class ADamageNumber;

UCLASS()
class WEAPON_SYSTEM_API ADamageNumberController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageNumberController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void GetNewDamageNumber(FVector Loc, bool bCrit, int Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Core;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		TArray<ADamageNumber*> DamageNumbers;

private:
	int DamageNumbersToSpawn = 8;
};
