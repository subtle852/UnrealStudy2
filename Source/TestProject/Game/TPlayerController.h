// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPlayerController.generated.h"

class UTHUD;

/**
 * 
 */
UCLASS()
class TESTPROJECT_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable)
		UTHUD* GetHUDWidget() const { return HUDWidgetInstance; };

    protected:
    	ATPlayerController();
    	virtual void BeginPlay() override;

    private:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ATPlayerController, meta = (AllowPrivateAccess))
    	TObjectPtr<UTHUD> HUDWidgetInstance;
    
    	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ATPlayerController, meta = (AllowPrivateAccess))
    	TSubclassOf<UTHUD> HUDWidgetClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ATPlayerController, meta = (AllowPrivateAccess))
		uint8 bIsInventoryOpen : 1;
	
};
