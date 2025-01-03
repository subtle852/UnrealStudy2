// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TestProjectCharacter.generated.h"

class UTInventorySystemComponent;
class UTQuickSlotSystem;

UCLASS(config=Game)
class ATestProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PickUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InventoryAction;
	
public:
	ATestProjectCharacter();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void PickUp(const FInputActionValue& Value);

	void ShowOrRemoveInventory(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	void UpdateInventory();
	
	void InitializeQuickSlot();
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void SetItem(ATItem* InItem) { Item = InItem; }
	
	UFUNCTION(BlueprintCallable)
	ATItem* GetItem() {return Item;}
	
	UFUNCTION(BlueprintCallable)
	UTInventorySystemComponent* GetInventorySystemComponent() {return InventorySystemComponent;}
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> RightWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test", meta = (AllowPrivateAccess))
	TObjectPtr<class ATItem> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test", meta = (AllowPrivateAccess))
	TObjectPtr<UTInventorySystemComponent> InventorySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test", meta = (AllowPrivateAccess))
	TObjectPtr<UTQuickSlotSystem> QuickSlotSystemComponent;

	
};

