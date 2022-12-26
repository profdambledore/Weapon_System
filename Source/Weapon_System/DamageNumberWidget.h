// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"

#include "DamageNumberWidget.generated.h"

/**
 * 
 */
UCLASS()
class WEAPON_SYSTEM_API UDamageNumberWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void SynchronizeProperties() override;

	void SetNewDamage(bool bCrit, int Damage);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* DamageAmount = nullptr;

	int D = 100;
	bool bC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
		FLinearColor CritColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
		FLinearColor DamageColour;
};
