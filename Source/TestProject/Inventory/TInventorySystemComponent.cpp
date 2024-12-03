// Fill out your copyright notice in the Description page of Project Settings.


#include "TInventorySystemComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "TestProject/Item/TItem.h"


// Sets default values for this component's properties
UTInventorySystemComponent::UTInventorySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// FSlot temp;
	// Slots.Init(temp, InventorySize);
	
	Slots.Reserve(InventorySize);
	Slots.AddDefaulted(InventorySize);
}


// Called every frame
void UTInventorySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTInventorySystemComponent::AddItem(int32 ItemAmount, FName ItemKey)
{
	AmountLeft = ItemAmount;

	while(AmountLeft > 0 && bIsAddFailed == false)
	{
		int32 index = FindSlot(ItemKey).first;
		bool bIsFound = FindSlot(ItemKey).second;
		if(bIsFound == true)// 인벤에 존재하는 아이템
		{
			IncreaseSlotStack(index);
			--AmountLeft; 
		}
		else// 인벤에 존재하지 않는 아이템
		{
			if(CheckSlotEmpty().first == true)
			{
				AddToNewSlot(ItemKey);
				--AmountLeft; 
			}
			else// 빈 공간이 없는 경우
			{
				bIsAddFailed = true;
			}
		}
	}

	// 출력용
	for (int32 Index = 0; Index < Slots.Num(); ++Index)
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Slot Index %d : %s -> %d"), Index, *Slots[Index].ItemName.ToString(), Slots[Index].Amount)
			, true// 화면에 출력 여부
			, true// 로그 출력 여부
			, FLinearColor::Blue
			, 10.f);// Duration 
	}

}

std::pair<int32, bool> UTInventorySystemComponent::FindSlot(FName ItemKey)
{
	for (int32 Index = 0; Index < Slots.Num(); ++Index)
	{
		if(Slots[Index].ItemName == ItemKey)// 동일한 아이템 키 발견
		{
			if(Slots[Index].Amount < GetStackSize(ItemKey))// StackSize가 인벤토리에 있는 개수 보다 적은 경우
			{
				return std::make_pair(Index, true);
			}
		}
	}
	
	return std::make_pair(-1, false);// 오류 코드
}

int32 UTInventorySystemComponent::GetStackSize(FName ItemKey)
{
	// 에셋 위치 하드코딩
	FString Path = TEXT("/Game/CustomContent/Item/DT_Item.DT_Item");
	UDataTable* ItemTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *Path));
	if (ItemTable)
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("DataTable successfully loaded: %s"), *ItemTable->GetName()));

		// 데이터 테이블에서 RowName(ItemKey)에 해당하는 데이터를 가져오기
		static const FString ContextString(TEXT("ItemTable Context"));
		const FItemStruct* ItemRow = ItemTable->FindRow<FItemStruct>(ItemKey, ContextString);
		if (ItemRow)
		{
			UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Row successfully loaded. StackSize: %d"), ItemRow->StackSize));
			return ItemRow->StackSize;// StackSize 반환
		}
		else
		{
			UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Failed to load Row & StackSize.")));
			return -1;// 오류 코드
		}
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, TEXT("Failed to load DataTable."));
		return -1;// 오류 코드
	}

	return -1;// 오류 코드
}

void UTInventorySystemComponent::IncreaseSlotStack(int32 Index, int32 Amount)
{
	Slots[Index].Amount += Amount;
}

std::pair<bool, int32> UTInventorySystemComponent::CheckSlotEmpty()
{
	for (int32 Index = 0; Index < Slots.Num(); ++Index)
	{
		if(Slots[Index].Amount == 0)// 슬롯의 아이템 개수가 0인 경우
		{
			return std::make_pair(true, Index);
		}
	}

	return std::make_pair(false, -1);// 슬롯의 아이템 개수가 0인 슬롯이 없는 경우
}

void UTInventorySystemComponent::AddToNewSlot(FName ItemKey, int32 Amount)
{
	int32 emptySlotIndex = CheckSlotEmpty().second;
	Slots[emptySlotIndex].ItemName = ItemKey;
	Slots[emptySlotIndex].Amount = Amount;
}

