// Fill out your copyright notice in the Description page of Project Settings.


#include "SemiAutoTrigger.h"

void ASemiAutoTrigger::StartFire(bool bCantFire)
{
	bool bHit;
	bCanFire = bCantFire;
	if (bCantFire == true) {
		if (CurrentMagazine > 0) {
			bHit = FireBullet();
			// VisRecoil
			// ActualRecoil
			UE_LOG(LogTemp, Warning, TEXT("%f"), 60.0f / Stats.Frame.Imapct.RateOfFire)
		}
		else {
			GetCanReload();
		}
	}
}

void ASemiAutoTrigger::ContinueFire()
{

}