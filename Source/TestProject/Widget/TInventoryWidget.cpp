// Fill out your copyright notice in the Description page of Project Settings.


#include "TInventoryWidget.h"

#include "TSlotWidget.h"
#include "Components/WrapBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TestProject/Inventory/TInventorySystemComponent.h"

void UTInventoryWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (InventorySystemComponent)
	{
		UpdateSlots(InventorySystemComponent->GetSlots());
	}
}

void UTInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UTInventoryWidget::UpdateInventory(UTInventorySystemComponent* InInventorySystemComponent)
{
	if(InInventorySystemComponent)
	{
		InventorySystemComponent = InInventorySystemComponent;
		
		UpdateSlots(InventorySystemComponent->GetSlots());
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("InInventorySystemComponent is INVALID!!!")));
	}
	
}

void UTInventoryWidget::UpdateSlots(const TArray<FSlot>& InSlotsArray)
{
	InventorySystemComponent->OnInventoryUpdated.RemoveAll(this);
	InventorySystemComponent->OnInventoryUpdated.AddDynamic(this, &ThisClass::UpdateInventoryDrop);

	WrapBox->ClearChildren();
	
	for (int i = 0; i < InSlotsArray.Max(); ++i)
	{
		SlotWidgetInstance = CreateWidget<UTSlotWidget>(this, SlotWidgetClass);
		if (IsValid(SlotWidgetInstance) == true)
		{
			SlotWidgetInstance->SetItemKey(InSlotsArray[i].ItemName);
			SlotWidgetInstance->SetItemAmount(InSlotsArray[i].Amount);
			SlotWidgetInstance->SetInventorySystem(InventorySystemComponent);
			SlotWidgetInstance->SetContentIndex(i);

			WrapBox->AddChild(SlotWidgetInstance);
		}
	}

}

void UTInventoryWidget::UpdateInventoryDrop()
{
	if(InventorySystemComponent)
	{
		UpdateSlots(InventorySystemComponent->GetSlots());
	}
}

