// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageNumberWidget.h"
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
	static ConstructorHelpers::FClassFinder<UUserWidget> FoundWidget(TEXT("/Game/Weapons/BP_DNW"));
	if (FoundWidget.Succeeded())
	{
		Widget->SetWidgetClass(FoundWidget.Class);
	}
	Widget->SetDrawSize(FVector2D(400.0f, 100.0f));
	Widget->SetRelativeLocation(FVector(200.0f, 50.0f, 0.0f));

	// Find the curve for the timeline
	static ConstructorHelpers::FObjectFinder<UCurveFloat>CurveObj(TEXT("/Game/Weapons/C_DNTimeline.C_DNTimeline"));
	if (CurveObj.Succeeded()) { TimelineCurve = CurveObj.Object; };

	TravelLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("Traveline"));

	// Bind timeline functions
	onTimelineCallback.BindUFunction(this, FName{ TEXT("TravelLineCallback") });
	onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TravelLineFinishedCallback") });
	TravelLine->AddInterpFloat(TimelineCurve, onTimelineCallback, FName{ TEXT("TravelLineCu") });
	TravelLine->SetTimelineFinishedFunc(onTimelineFinishedCallback);	
}

// Called when the game starts or when spawned
void ADamageNumber::BeginPlay()
{
	Super::BeginPlay();
	
	// Cast and store a pointer to the widget
	WidgetRef = Cast<UDamageNumberWidget>(Widget->GetWidget());

	TravelLine->SetPlaybackPosition(0.0f, true);
}

// Called every frame
void ADamageNumber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TravelLine->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);

	// Set the widget to look at the player if its active
	if (bInUse == true) {
		// Rotate widget to face player
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
	WidgetRef->SetNewDamage(bNewCrit, NewDamage);

	// Choose a random diretction to move in
	DistX = FMath::FRandRange((Distance * -1), Distance);
	DistY = FMath::FRandRange((Distance * -1), Distance);	

	TravelLine->PlayFromStart();

	return true;
}

void ADamageNumber::TravelLineCallback(float val)
{
	// Update World Location
	UE_LOG(LogTemp, Warning, TEXT("%f"), val);
	SetActorLocation(FMath::Lerp(StartLoc, FVector(StartLoc.X + DistX, StartLoc.Y, StartLoc.Z + DistY), val));
}

void ADamageNumber::TravelLineFinishedCallback()
{
	bInUse = false;
	SetActorLocation(FVector(0.0F, 0.0F, 0.0F));
}