// Fill out your copyright notice in the Description page of Project Settings.


#include "TInventoryMenuWidget.h"

#include "TInventoryWidget.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "TestProject/TestProjectCharacter.h"
#include "TestProject/Inventory/TInventorySystemComponent.h"

void UTInventoryMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (UWorld* World = GetWorld())
	{
		ATestProjectCharacter* PlayerCharacter = Cast<ATestProjectCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
		if (PlayerCharacter)
		{
			InventoryWidget->UpdateInventory(PlayerCharacter->GetInventorySystemComponent());
		}
	}
}

void UTInventoryMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if(PlayerController && InventoryWidget)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());// 위젯 설정
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);// 마우스 잠금 설정 (필요에 따라 변경)
		InputMode.SetHideCursorDuringCapture(true);
		
		PlayerController->SetInputMode(InputMode);// 입력 모드 설정
		PlayerController->bShowMouseCursor = true;// 마우스 커서 표시
	}
	
}

void UTInventoryMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if(PlayerController)
	{
		FInputModeGameOnly InputMode;
		
		PlayerController->SetInputMode(InputMode);// 입력 모드 설정
		PlayerController->bShowMouseCursor = false;// 마우스 커서 미표시
		
	}
}
