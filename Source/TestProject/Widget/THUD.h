// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCustomWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "THUD.generated.h"

class UTInventoryMenuWidget;
/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTHUD : public UTCustomWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ShowInventoryMenu();

	UFUNCTION(BlueprintCallable)
	void RemoveInventoryMenu();
	
	void InitializeQuickSlot(class UTQuickSlotSystem* InQuickSlotSystem);

	UFUNCTION()
	void UpdateQuickSlot(UTQuickSlotSystem* InQuickSlotSystem);


	UTInventoryMenuWidget* GetInventoryMenuWidget() const { return InventoryMenuWidgetInstance; }

	void SetItemName(FText InItemName) { ItemName->SetText(InItemName); } 

	void SetItemImage(class UTexture2D* InTexture2D) const
	{
		ItemImage->SetBrushFromTexture(InTexture2D);
		ItemImage->SetColorAndOpacity({1.0f, 1.0f, 1.0, 1.0f});
	}
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UImage> ItemImage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<UTInventoryMenuWidget> InventoryMenuWidgetInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))// 직접 설정 필요!!!!!
	TSubclassOf<UTInventoryMenuWidget> InventoryMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<UTCustomWidget> CustomWidget;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	//TObjectPtr<class UTQuickSlotWidget> QuickSlotWidgetInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))// 직접 설정 필요!!!!!
	TSubclassOf<class UTQuickSlotWidget> QuickSlotWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UWrapBox> WrapBox;
	
};
