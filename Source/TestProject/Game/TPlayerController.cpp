// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "TestProject/Widget/THUD.h"

ATPlayerController::ATPlayerController()
{
}

void ATPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 마우스 클릭없이 바로 포커싱 되도록 하는 부분
	//FInputModeGameOnly InputModeGameOnly;
	//SetInputMode(InputModeGameOnly);

	ensureMsgf(IsValid(HUDWidgetClass), TEXT("Invalid HUDWidgetClass"));
	HUDWidgetInstance = CreateWidget<UTHUD>(this, HUDWidgetClass);
	if (IsValid(HUDWidgetInstance) == true)
	{
		HUDWidgetInstance->AddToViewport();
	}
}
