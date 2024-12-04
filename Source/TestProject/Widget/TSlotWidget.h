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
	
public:
	void SetItemKey(FName InItemKey) { ItemKey = InItemKey; }
	FName GetItemKey() const { return ItemKey; }

	void SetItemAmount(int32 InItemAmount) { ItemAmount = InItemAmount; };
	int32 GetItemAmount() const { return ItemAmount; }

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
};
