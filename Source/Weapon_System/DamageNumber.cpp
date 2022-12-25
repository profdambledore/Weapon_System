// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageNumber.h"

// Sets default values
ADamageNumber::ADamageNumber()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Core = CreateDefaultSubobject<USceneComponent>(TEXT("Core"));

	// Find the Widget for the DamageNumber
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(Core);
	static ConstructorHelpers::FClassFinder<UUserWidget> FoundWidget(TEXT(""));
	if (FoundWidget.Succeeded())
	{
		//Widget->SetWidgetClass(FoundWidget.Class);
	}

	// Find the curve for the timeline
	static ConstructorHelpers::FObjectFinder<UCurveFloat>CurveObj(TEXT(""));
	if (CurveObj.Succeeded()) { TimelineCurve = CurveObj.Object; };

	TravelLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("Traveline"));
	TravelLine->SetPropertySetObject(this);
	TravelLine->SetLooping(false);
	TravelLine->SetPlaybackPosition(0.0f, false);

	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	// Bind timeline functions
	onTimelineCallback.BindUFunction(this, FName{ TEXT("TravelLineCallback") });
	onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TravelLineFinishedCallback") });
}

// Called when the game starts or when spawned
void ADamageNumber::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageNumber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Set the widget to look at the player if its active
	if (bInUse) {
		FRotator playerRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
		playerRot = FRotator(0.0f, playerRot.Yaw, 0.0f);
		SetActorRotation(playerRot);
	}

}

bool ADamageNumber::NewDamageNumber(FVector Loc, bool bNewCrit, int NewDamage)
{
	// Set this damage numbers location
	SetActorLocation(Loc);
	StartLoc = Loc;

	bInUse = true;

	// Update the info for the widget
	Damage = NewDamage;
	bCrit = bNewCrit;

	// Call widget updater

	// Choose a random diretction to move in
	float randomDir = FMath::FRandRange(-180, 179);
	Core->SetWorldRotation(FRotator(0.0f, randomDir, 0.0f));

	return true;
}

void ADamageNumber::TravelLineCallback(float val)
{
	FMath::Lerp(StartLoc, FVector(StartLoc.X + Distance, StartLoc.Y, StartLoc.Z), val);
}

void ADamageNumber::TravelLineFinishedCallback()
{
	bInUse = false;
	SetActorLocation(FVector(0.0F, 0.0F, 0.0F));
}

