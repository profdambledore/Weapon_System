// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "DamageNumber.generated.h"

class UDamageNumberWidget;

UCLASS()
class WEAPON_SYSTEM_API ADamageNumber : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageNumber();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		bool NewDamageNumber(FVector Loc, bool bNewCrit, int NewDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void TravelLineCallback(float val);

	UFUNCTION()
		void TravelLineFinishedCallback();
public:	
	// Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Core;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UWidgetComponent* Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UTimelineComponent* TravelLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCurveFloat* TimelineCurve;

	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	float Distance = 200;
	float DistX;
	float DistY;
	FVector StartLoc;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bInUse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCrit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Damage;

	UDamageNumberWidget* WidgetRef;
};
