// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TItem.h"
#include "TApple.generated.h"

UCLASS()
class TESTPROJECT_API ATApple : public ATItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATApple();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
