// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TInventorySystemComponent.h"
#include "TQuickSlotSystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuickSlotUpdated, UTQuickSlotSystem*, InQuickSlotSystem);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTPROJECT_API UTQuickSlotSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTQuickSlotSystem();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void AddtoQuickSlot(class UTInventorySystemComponent* InInventorySystemComponent, int32 InInventoryItemIndex, int32 InTargetQuickSlotIndex);
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQuickSlotUpdated OnQuickSlotUpdated;

	const TArray<FSlot>& GetQuickSlots() { return QuickSlots; }
	
	int32 GetQuickSlotSize() const { return QuickSlotSize; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<FSlot> QuickSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int32 QuickSlotSize = 5;
	
};
