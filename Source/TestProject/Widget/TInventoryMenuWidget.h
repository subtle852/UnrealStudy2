// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCustomWidget.h"
#include "TInventoryMenuWidget.generated.h"

class UTInventoryWidget;
/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTInventoryMenuWidget : public UTCustomWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTInventoryWidget> InventoryWidget;
	
};
