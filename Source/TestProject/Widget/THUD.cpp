// Fill out your copyright notice in the Description page of Project Settings.


#include "THUD.h"
#include "TInventoryMenuWidget.h"
#include "Components/WrapBox.h"
#include "TestProject/Inventory/TQuickSlotSystem.h"
#include "TQuickSlotWidget.h"
#include "TestProject/Inventory/TInventorySystemComponent.h"

void UTHUD::ShowInventoryMenu()
{
	InventoryMenuWidgetInstance = CreateWidget<UTInventoryMenuWidget>(this, InventoryMenuWidgetClass);
	if (IsValid(InventoryMenuWidgetInstance) == true)
	{
		CustomWidget = InventoryMenuWidgetInstance;
		CustomWidget->AddToViewport();
	}
}

void UTHUD::RemoveInventoryMenu()
{
	CustomWidget->RemoveFromParent();
}

void UTHUD::InitializeQuickSlot(UTQuickSlotSystem* InQuickSlotSystem)
{
	WrapBox->ClearChildren();

	if(IsValid(InQuickSlotSystem))
	{
		for (int i = 0; i < InQuickSlotSystem->GetQuickSlotSize(); ++i)
		{
			UTQuickSlotWidget* QuickSlotWidgetInstance = CreateWidget<UTQuickSlotWidget>(this, QuickSlotWidgetClass);
			if (IsValid(QuickSlotWidgetInstance) == true)
			{
				// FSlot관련 인지 못하는 문제 발생
				// 해당 원인은 UTQuickSlotSystem.h에서 FSlot을 인지하지 못해서 발생한 문제
				// 따라서, UTQuickSlotSystem.h에 FSlot이 포함된 헤더파일을 추가 해줌
				QuickSlotWidgetInstance->SetItemKey(InQuickSlotSystem->GetQuickSlots()[i].ItemName);
				QuickSlotWidgetInstance->SetSlotIndex(i);
				QuickSlotWidgetInstance->SetQuickSlotSystem(InQuickSlotSystem);

				WrapBox->AddChild(QuickSlotWidgetInstance);
				
				QuickSlotWidgetInstance->SetPadding({5.0f, 0.0f, 5.0f, 0.0f});
				
			}
		}

		InQuickSlotSystem->OnQuickSlotUpdated.RemoveAll(this);
		InQuickSlotSystem->OnQuickSlotUpdated.AddDynamic(this, &ThisClass::UpdateQuickSlot);
	}
	
}

void UTHUD::UpdateQuickSlot(UTQuickSlotSystem* InQuickSlotSystem)
{
	InitializeQuickSlot(InQuickSlotSystem);
	
}
