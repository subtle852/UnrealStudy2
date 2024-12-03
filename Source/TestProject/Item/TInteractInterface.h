// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestProject/TestProjectCharacter.h"
#include "UObject/Interface.h"
#include "TInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TESTPROJECT_API ITInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(ATestProjectCharacter* PlayerCharacter) = 0;
};
