// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TCustomWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTCustomWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }
	FORCEINLINE AActor* GetOwningActor() const { return OwningActor; }

protected:
	// 현재 위젯을 소유하고 있는 액터 저장용 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	TObjectPtr<AActor> OwningActor;
};
