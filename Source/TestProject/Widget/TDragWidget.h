// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCustomWidget.h"
#include "TDragWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTDragWidget : public UTCustomWidget
{
	GENERATED_BODY()

public:
	void SetItemKey(FName InItemKey) { ItemKey = InItemKey; }
	
protected:
	virtual void NativePreConstruct() override;

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UImage> DragImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FName ItemKey;
};
