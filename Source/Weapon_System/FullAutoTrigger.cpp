// Fill out your copyright notice in the Description page of Project Settings.

#include "FullAutoTrigger.h"

#include "PlayerCharacter.h"

void AFullAutoTrigger::StartFire(bool bCantFire)
{
	bool bHit;
	bCanFire = bCantFire;
	if (bCantFire == true) {
		if (CurrentMagazine > 0) {
			bHit = FireBullet();
			// VisRecoil
			// ActualRecoil
			UE_LOG(LogTemp, Warning, TEXT("%f"), 60.0f / Stats.Frame.Imapct.RateOfFire)
			GetWorldTimerManager().SetTimer(AutoTimerHandle, this, &AFullAutoTrigger::ContinueFire, 60.0f / Stats.Frame.Imapct.RateOfFire , true);
		}
		else {
			Player->Reload();
		}
	}
	else {
		GetWorldTimerManager().ClearTimer(AutoTimerHandle);
	}
}

void AFullAutoTrigger::ContinueFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Continue Fire"))
	bool bHit;
	if (CurrentMagazine > 0) {
		bHit = FireBullet();
		// VisRecoil
		// ActualRecoil
		UE_LOG(LogTemp, Warning, TEXT("Continue Fire"))
	}
	else {
		Player->Reload();
	}
}
