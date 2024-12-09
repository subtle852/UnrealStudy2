// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DSP/AudioDebuggingUtilities.h"
#include "Game/TPlayerController.h"
#include "Inventory/TInventorySystemComponent.h"
#include "Inventory/TQuickSlotSystem.h"
#include "Item/TItem.h"
#include "Item/TItemComponent.h"
#include "Widget/THUD.h"
#include "Widget/TInventoryMenuWidget.h"
#include "Widget/TInventoryWidget.h"


//////////////////////////////////////////////////////////////////////////
// ATestProjectCharacter

ATestProjectCharacter::ATestProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	RightWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWeapon"));
	RightWeapon->SetupAttachment(GetMesh(), FName(TEXT("RightWeapon")));

	InventorySystemComponent = CreateDefaultSubobject<UTInventorySystemComponent>(TEXT("InventorySystemComponent"));

	QuickSlotSystemComponent = CreateDefaultSubobject<UTQuickSlotSystem>(TEXT("QuickSlotSystemComponent"));
	
}

void ATestProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (ATPlayerController* PlayerController = Cast<ATPlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Initialize QuickSlot
	if (ATPlayerController* PlayerController = Cast<ATPlayerController>(Controller))
	{
		PlayerController->GetHUDWidget()->InitializeQuickSlot(QuickSlotSystemComponent);
	}
}

void ATestProjectCharacter::UpdateInventory()
{
	if (ATPlayerController* PlayerController = Cast<ATPlayerController>(Controller))
	{
		UTInventoryMenuWidget* InventoryMenuWidget = PlayerController->GetHUDWidget()->GetInventoryMenuWidget();
		if(IsValid(InventoryMenuWidget))
		{
			InventoryMenuWidget->GetInventoryWidget()->UpdateInventory(InventorySystemComponent);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATestProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATestProjectCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATestProjectCharacter::Look);

		// the Others
		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Started, this, &ATestProjectCharacter::PickUp);

		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ATestProjectCharacter::ShowOrRemoveInventory);
		
	}

}

void ATestProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATestProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATestProjectCharacter::PickUp(const FInputActionValue& Value)
{
	if(IsValid(Item) == false)
		return;
	
	UTItemComponent* ItemComponent = Cast<UTItemComponent>(Item->GetComponentByClass(UTItemComponent::StaticClass()));
	if(IsValid(ItemComponent) == false)
		return;

	auto DataTable = ItemComponent->GetItemData().DataTable;
	if (IsValid(DataTable) == false)
		return;

	FName RowName = ItemComponent->GetItemData().RowName;
	const FItemStruct* ItemRow = DataTable->FindRow<FItemStruct>(RowName, "None");

	switch (ItemRow->ItemType)
	{
	case EItemType::Weapon:
		{
			RightWeapon->SetStaticMesh(Item->GetMeshComponent()->GetStaticMesh());
			if (ATPlayerController* PlayerController = Cast<ATPlayerController>(Controller))
			{
				PlayerController->GetHUDWidget()->SetItemName(ItemRow->ItemName);
				PlayerController->GetHUDWidget()->SetItemImage(ItemRow->ItemImage);
			}
			Item->SetLifeSpan(0.01f);

			break;
		}

	case EItemType::Consumable:
		{
			ItemComponent->Interact(this);
			UpdateInventory();

			break;
		}

	default:
		break;
	}

	
}

void ATestProjectCharacter::ShowOrRemoveInventory(const FInputActionValue& Value)
{
	if (ATPlayerController* PlayerController = Cast<ATPlayerController>(Controller))
	{
		PlayerController->ShowOrRemoveInventoryInController();
	}
}




