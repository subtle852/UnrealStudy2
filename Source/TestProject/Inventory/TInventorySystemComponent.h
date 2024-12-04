// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TInventorySystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FSlot : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess))
	FName ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess))
	int32 Amount = 0;
};

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTPROJECT_API UTInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTInventorySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddItem(int32 ItemAmount, FName ItemKey);
	
	std::pair<int32, bool> FindSlot(FName ItemKey);// 인벤토리에서 해당 아이템이 존재하는지 확인
	
	int32 GetStackSize(FName ItemKey);
	
	void IncreaseSlotStack(int32 Index, int32 Amount = 1);
	
	std::pair<bool, int32> CheckSlotEmpty();
	
	void AddToNewSlot(FName ItemKey, int32 Amount = 1);


	const TArray<FSlot>& GetSlots() { return Slots; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess))
	int32 InventorySize = 16;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess))
	TArray<FSlot> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess))
	uint8 bIsAddFailed : 1;

	int32 AmountLeft;
	
	
};
