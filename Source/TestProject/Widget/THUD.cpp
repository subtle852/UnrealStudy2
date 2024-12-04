// Fill out your copyright notice in the Description page of Project Settings.


#include "THUD.h"
#include "TInventoryMenuWidget.h"

void UTHUD::ShowInventoryMenu()
{
	InventoryMenuWidgetInstance = CreateWidget<UTInventoryMenuWidget>(this, InventoryMenuWidgetClass);
	if (IsValid(InventoryMenuWidgetInstance) == true)
	{
		CustomWidget = InventoryMenuWidgetInstance;
		CustomWidget->AddToViewport();
	}
}

void UTHUD::RemoveInventoryMenu()
{
	CustomWidget->RemoveFromParent();
}
