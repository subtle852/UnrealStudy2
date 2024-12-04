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

		WrapBox->ClearChildren();

		UpdateSlots(InventorySystemComponent->GetSlots());
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("InInventorySystemComponent is INVALID!!!")));
	}
	
}

void UTInventoryWidget::UpdateSlots(const TArray<FSlot>& InSlotsArray)
{
	for (auto Element : InSlotsArray)
	{
		UTSlotWidget* SlotWidgetInstance = CreateWidget<UTSlotWidget>(this, SlotWidgetClass);
		if (IsValid(SlotWidgetInstance) == true)
		{
			SlotWidgetInstance->SetItemKey(Element.ItemName);
			SlotWidgetInstance->SetItemAmount(Element.Amount);

			WrapBox->AddChild(SlotWidgetInstance);
		}
		
	}
}

