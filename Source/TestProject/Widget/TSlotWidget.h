// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCustomWidget.h"
#include "TSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTSlotWidget : public UTCustomWidget
{
	GENERATED_BODY()
protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
public:
	void SetItemKey(FName InItemKey) { ItemKey = InItemKey; }
	FName GetItemKey() const { return ItemKey; }

	void SetItemAmount(int32 InItemAmount) { ItemAmount = InItemAmount; };
	int32 GetItemAmount() const { return ItemAmount; }

	void SetInventorySystem(class UTInventorySystemComponent* InInventorySystem) { InventorySystemComponent = InInventorySystem; }
	UTInventorySystemComponent* GetInventorySystemComponent() const { return InventorySystemComponent; }

	void SetContentIndex(int32 InContentIndex) { ContentIndex = InContentIndex; };
	int32 GetContentIndex() const { return ContentIndex; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UImage> ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class USizeBox> ItemStackBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemStackText;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
	FName ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
	int32 ItemAmount;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UTDragWidget> DragWidgetInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))// 직접 설정 필요!!!!!
	TSubclassOf<UTDragWidget> DragWidgetClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UTInventorySystemComponent> InventorySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn, pAllowPrivateAccess))
	int32 ContentIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UTDragDropInventory> DragDropInventoryInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))// 직접 설정 필요!!!!!
	TSubclassOf<UTDragDropInventory> DragDropInventoryClass;

	
};
