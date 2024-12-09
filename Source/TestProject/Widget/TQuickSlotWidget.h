// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCustomWidget.h"
#include "TQuickSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTQuickSlotWidget : public UTCustomWidget
{
	GENERATED_BODY()

public:
	void SetItemKey(FName InItemKey) { ItemKey = InItemKey; }

	void SetSlotIndex(int32 InSlotIndex) { SlotIndex = InSlotIndex; }

	void SetQuickSlotSystem(class UTQuickSlotSystem* InQuickSlotSystem) { QuickSlotSystem = InQuickSlotSystem; }
	
protected:
	virtual void NativePreConstruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UImage> QuickItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> QuickItemText;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn, AllowPrivateAccess))
	FName ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn, AllowPrivateAccess))
	int32 SlotIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn, AllowPrivateAccess))
	TObjectPtr<class UTQuickSlotSystem> QuickSlotSystem;
	
};
