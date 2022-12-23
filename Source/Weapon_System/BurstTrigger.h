// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponParent.h"
#include "BurstTrigger.generated.h"

/**
 * 
 */
UCLASS()
class WEAPON_SYSTEM_API ABurstTrigger : public AWeaponParent
{
	GENERATED_BODY()

public:
	virtual void StartFire(bool bCantFire) override;
	virtual void ContinueFire() override;

	int BurstShots = 3;
	float InBurstDelay = 0.33;

	bool bBurstDelay = false;
	bool bInBurst = false;
	int BurstShotsRemain = 0;


	FTimerHandle BurstTimerHandle;
};
