// Fill out your copyright notice in the Description page of Project Settings.


#include "TQuickSlotSystem.h"
#include "TInventorySystemComponent.h"

// Sets default values for this component's properties
UTQuickSlotSystem::UTQuickSlotSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTQuickSlotSystem::BeginPlay()
{
	Super::BeginPlay();


	QuickSlots.Reserve(QuickSlotSize);
	QuickSlots.AddDefaulted(QuickSlotSize);
	
}


// Called every frame
void UTQuickSlotSystem::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTQuickSlotSystem::AddtoQuickSlot(UTInventorySystemComponent* InInventorySystemComponent,
	int32 InInventoryItemIndex, int32 InTargetQuickSlotIndex)
{
	const TArray<FSlot>& Temp =  InInventorySystemComponent->GetSlots();
	QuickSlots[InTargetQuickSlotIndex] = Temp[InInventoryItemIndex];
	
	OnQuickSlotUpdated.Broadcast(this);
}

