// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCustomWidget.h"
#include "Engine/DataTable.h"
#include "TInventoryWidget.generated.h"

class UTInventorySystemComponent;
struct FSlot;
/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTInventoryWidget : public UTCustomWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateInventory(UTInventorySystemComponent* InInventorySystemComponent);

	void UpdateSlots(const TArray<FSlot>& InSlotsArray);

	UFUNCTION()
	void UpdateInventoryDrop();
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UWrapBox> WrapBox;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<UTInventorySystemComponent> InventorySystemComponent;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess));
	TObjectPtr<class UTSlotWidget> SlotWidgetInstance;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess));// 직접 설정 필요!!!!!
	TSubclassOf<UTSlotWidget> SlotWidgetClass;
	
};
