// Fill out your copyright notice in the Description page of Project Settings.


#include "TWoodStick.h"


// Sets default values
ATWoodStick::ATWoodStick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemType = EItemType::Weapon;
	ItemName = EItemName::WoodStick;
}

// Called when the game starts or when spawned
void ATWoodStick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATWoodStick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

