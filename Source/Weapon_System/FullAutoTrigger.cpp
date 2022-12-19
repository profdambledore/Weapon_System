// Fill out your copyright notice in the Description page of Project Settings.


#include "FullAutoTrigger.h"

void AFullAutoTrigger::StartFire(bool bCantFire)
{
	bCanFire = bCantFire;
	if (bCanFire) {
		if (CurrentMagazine > 0) {
			FireBullet();
			// VisRecoil
			// ActualRecoil
			GetWorldTimerManager().SetTimer(AutoTimerHandle, this, &AFullAutoTrigger::ContinueFire, Stats.Frame.Imapct.RateOfFire / 60, true);
		}
		else {
			GetCanReload();
		}
	}
	else {
		GetWorldTimerManager().ClearTimer(AutoTimerHandle);
	}
}

void AFullAutoTrigger::ContinueFire()
{
	if (CurrentMagazine > 0) {
		FireBullet();
		// VisRecoil
		// ActualRecoil
	}
	else {
		GetCanReload();
	}
}
