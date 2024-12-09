// Fill out your copyright notice in the Description page of Project Settings.


#include "TQuickSlotWidget.h"

#include <string>

#include "Components/Image.h"
#include "Engine/DataTable.h"
#include "TestProject/Item/TItem.h"
#include "Components/TextBlock.h"
#include "TestProject/Inventory/TDragDropInventory.h"
#include "TestProject/Inventory/TQuickSlotSystem.h"

void UTQuickSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	bool IsFound = false;
	
	FString Path = TEXT("/Game/CustomContent/Item/DT_Item.DT_Item");
	UDataTable* ItemTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *Path));
	if (ItemTable)
	{
		// 데이터 테이블에서 RowName(ItemKey)에 해당하는 데이터를 가져오기
		const FString ContextString(TEXT("ItemTable Context"));
		const FItemStruct* ItemRow = ItemTable->FindRow<FItemStruct>(ItemKey, ContextString);
		if (ItemRow)
		{
			QuickItemImage->SetBrushFromTexture(ItemRow->ItemImage);
			QuickItemImage->SetVisibility(ESlateVisibility::Visible);
	
			++SlotIndex;
			QuickItemText->SetText(FText::AsNumber(SlotIndex));
	
			IsFound = true;
		}
	}
	
	if(IsFound == false)
	{
		QuickItemImage->SetVisibility(ESlateVisibility::Hidden);
	
		++SlotIndex;
		QuickItemText->SetText(FText::AsNumber(SlotIndex));
	}
	
}

bool UTQuickSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	bool Return = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UTDragDropInventory* DragDropInventory = Cast<UTDragDropInventory>(InOperation);
	if(IsValid(DragDropInventory))
	{
		QuickSlotSystem->AddtoQuickSlot(DragDropInventory->GetInventorySystemComponent() ,DragDropInventory->GetContextIndex(), --SlotIndex);

		return true;
	}
	
	return Return;
}
