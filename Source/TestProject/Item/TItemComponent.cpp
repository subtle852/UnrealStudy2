// Fill out your copyright notice in the Description page of Project Settings.


#include "TItemComponent.h"

#include "TItem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TestProject/Inventory/TInventorySystemComponent.h"


// Sets default values for this component's properties
UTItemComponent::UTItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTItemComponent::Interact(ATestProjectCharacter* PlayerCharacter)
{
	UTInventorySystemComponent* InventorySystemComponent = PlayerCharacter->GetInventorySystemComponent();
	if(IsValid(InventorySystemComponent))
	{
		InventorySystemComponent->AddItem(ItemAmount, ItemData.RowName);

		//GetOwner()->Destroy();
	}
}

