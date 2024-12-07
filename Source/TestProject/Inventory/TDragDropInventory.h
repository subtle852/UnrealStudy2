// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "TDragDropInventory.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTDragDropInventory : public UDragDropOperation
{
	GENERATED_BODY()

public:
	void SetInventorySystemComponent(class UTInventorySystemComponent* InInventorySystemComponent) { InventorySystemComponent = InInventorySystemComponent; }

	void SetContextIndex(int32 InContextIndex) { ContentIndex = InContextIndex; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn, AllowPrivateAccess))
	TObjectPtr<class UTInventorySystemComponent> InventorySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn, AllowPrivateAccess))
	int32 ContentIndex;
	
};
