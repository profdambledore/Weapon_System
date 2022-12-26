// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageNumberWidget.h"

void UDamageNumberWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	DamageAmount->SetText(FText::FromString(FString::FromInt(D)));
	if (bC == true) {
		DamageAmount->SetColorAndOpacity(FSlateColor(CritColour));
	}
	else if (bC == false) { 
		DamageAmount->SetColorAndOpacity(FSlateColor(DamageColour)); 
	};
}

void UDamageNumberWidget::SetNewDamage(bool bCrit, int Damage)
{
	bC = bCrit;
	D = Damage;
	SynchronizeProperties();
}
