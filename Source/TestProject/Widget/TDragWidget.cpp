// Fill out your copyright notice in the Description page of Project Settings.


#include "TDragWidget.h"

#include "Components/Image.h"
#include "Engine/DataTable.h"
#include "TestProject/Item/TItem.h"

void UTDragWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	FString Path = TEXT("/Game/CustomContent/Item/DT_Item.DT_Item");
	UDataTable* ItemTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *Path));
	if (ItemTable)
	{
		// 데이터 테이블에서 RowName(ItemKey)에 해당하는 데이터를 가져오기
		const FString ContextString(TEXT("ItemTable Context"));
		const FItemStruct* ItemRow = ItemTable->FindRow<FItemStruct>(ItemKey, ContextString);
		if (ItemRow)
		{
			DragImage->SetBrushFromTexture(ItemRow->ItemImage);
		}
	}
}
