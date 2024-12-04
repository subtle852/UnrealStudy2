// Fill out your copyright notice in the Description page of Project Settings.


#include "TSlotWidget.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TestProject/Item/TItem.h"

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
