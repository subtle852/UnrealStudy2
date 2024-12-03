// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TInteractInterface.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TItemComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTPROJECT_API UTItemComponent : public UActorComponent, public ITInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void Interact(ATestProjectCharacter* PlayerCharacter) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemComponent", meta = (AllowPrivateAccess))
	FDataTableRowHandle ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemComponent", meta = (AllowPrivateAccess))
	int32 ItemAmount = 1;
	
};
