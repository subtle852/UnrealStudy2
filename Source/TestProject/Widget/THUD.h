// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCustomWidget.h"
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
	
};
