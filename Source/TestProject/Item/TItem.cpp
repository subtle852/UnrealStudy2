// Fill out your copyright notice in the Description page of Project Settings.


#include "TItem.h"


// Sets default values
ATItem::ATItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(GetRootComponent());

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetVisibility(false);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);

	//
	ItemType = EItemType::None;
	ItemName = EItemName::None;
	
}

// Called when the game starts or when spawned
void ATItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	WidgetComponent->SetVisibility(true);
}

void ATItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	WidgetComponent->SetVisibility(false);
}

