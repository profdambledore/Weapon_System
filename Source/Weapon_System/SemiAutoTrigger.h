// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponParent.h"
#include "SemiAutoTrigger.generated.h"

/**
 * 
 */
UCLASS()
class WEAPON_SYSTEM_API ASemiAutoTrigger : public AWeaponParent
{
	GENERATED_BODY()

public:
	virtual void StartFire(bool bCantFire) override;
	virtual void ContinueFire() override;
	
};
