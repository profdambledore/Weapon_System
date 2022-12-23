// Fill out your copyright notice in the Description page of Project Settings.


#include "BurstTrigger.h"

void ABurstTrigger::StartFire(bool bCantFire)
{
	bool bHit;
	bCanFire = bCantFire;
	if (bCantFire == true && bInBurst == false) {
		if (CurrentMagazine > 0) {
			BurstShotsRemain = BurstShots - 1;
			bHit = FireBullet();
			// VisRecoil
			// ActualRecoil
			UE_LOG(LogTemp, Warning, TEXT("%f"), 60.0f / Stats.Frame.Imapct.RateOfFire)
			GetWorldTimerManager().SetTimer(BurstTimerHandle, this, &ABurstTrigger::ContinueFire, InBurstDelay, true);
		}
		else {
			GetCanReload();
		}
	}
	else {
		GetWorldTimerManager().ClearTimer(BurstTimerHandle);
	}
}

void ABurstTrigger::ContinueFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Continue Fire"))
	bool bHit;
	if (CurrentMagazine > 0) {
		bHit = FireBullet();
		// VisRecoil
		// ActualRecoil
		UE_LOG(LogTemp, Warning, TEXT("Continue Fire"));
		if (--BurstShotsRemain <= 0) {
			GetWorldTimerManager().ClearTimer(BurstTimerHandle);
		}
	}
	else {
		GetCanReload();
	}
}