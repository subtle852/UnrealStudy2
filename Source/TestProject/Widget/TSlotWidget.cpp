// Fill out your copyright notice in the Description page of Project Settings.


#include "TSlotWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TestProject/Item/TItem.h"
#include "TDragWidget.h"
#include "TestProject/Inventory/TDragDropInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h" 
#include "Input/Reply.h"
#include "Input/Events.h" 
#include "TestProject/Inventory/TInventorySystemComponent.h"

void UTSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	bool bIsFound = false;
	
	FString Path = TEXT("/Game/CustomContent/Item/DT_Item.DT_Item");
	UDataTable* ItemTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *Path));
	if (ItemTable)
	{
		// 데이터 테이블에서 RowName(ItemKey)에 해당하는 데이터를 가져오기
		const FString ContextString(TEXT("ItemTable Context"));
		const FItemStruct* ItemRow = ItemTable->FindRow<FItemStruct>(ItemKey, ContextString);
		if (ItemRow)
		{
			bIsFound = true;
			
			ItemImage->SetBrushFromTexture(ItemRow->ItemImage);
			
			FText ItemAmountText = FText::FromString(FString::FromInt(ItemAmount));
			ItemStackText->SetText(ItemAmountText);

			ItemImage->SetVisibility(ESlateVisibility::Visible);
			ItemStackBox->SetVisibility(ESlateVisibility::Visible);
		}
	}

	if(bIsFound == false)
	{
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
		ItemStackBox->SetVisibility(ESlateVisibility::Hidden);
		
	}
	
	
}

void UTSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ACharacter* OwningCharacter = Cast<ACharacter>(OwningActor);
	// if (IsValid(OwningCharacter) == true)
	// {
	// 	OwningCharacter->SetWidget(this);
	// }

	// SetWidget 함수 관련 로직
	// void AGMonster::SetWidget(UGWidget* InGWidget)
	// {
	// 	Super::SetWidget(InGWidget);
	//
	// 	UGW_HPBar* HPBarWidget = Cast<UGW_HPBar>(InGWidget);
	// 	if (IsValid(HPBarWidget) == true)
	// 	{
	// 		HPBarWidget->SetMaxHP(StatComponent->GetMaxHP());
	// 		HPBarWidget->InitializeHPBarWidget(StatComponent);
	// 		StatComponent->OnCurrentHPChangedDelegate.AddDynamic(HPBarWidget, &UGW_HPBar::OnCurrentHPChange);
	// 	}
	// }
	
}

FReply UTSlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	if (!ItemKey.IsNone())
	{
		if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			// DetectDragIfPressed 반환값 처리
			
			FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
			if (EventReply.NativeReply.IsEventHandled())// 이벤트 처리 여부 확인
			{
				Reply = EventReply.NativeReply;// FEventReply에서 FReply로 변환
			}
		}
	}

	return Reply;
}

void UTSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	DragWidgetInstance = CreateWidget<UTDragWidget>(this, DragWidgetClass);
	if (IsValid(DragWidgetInstance) == true)
	{
		DragWidgetInstance->SetItemKey(ItemKey);

		UTDragDropInventory* DragOperation = Cast<UTDragDropInventory>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropInventoryClass));

		if (DragOperation)
		{
			DragOperation->SetInventorySystemComponent(InventorySystemComponent);
			DragOperation->DefaultDragVisual = DragWidgetInstance;
			DragOperation->SetContextIndex(ContentIndex);

			
			// 드래그 작업 반환
			OutOperation = DragOperation;
		}
	}
	
}

bool UTSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	bool Return = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UTDragDropInventory* Operation = Cast<UTDragDropInventory>(InOperation);
	
	if(Operation->GetContextIndex() != ContentIndex
		|| Operation->GetInventorySystemComponent() != InventorySystemComponent)
	{
		InventorySystemComponent->ChangeSlot(ContentIndex, Operation->GetInventorySystemComponent(), Operation->GetContextIndex());

		return true;
	}

	return Return;
	
}
