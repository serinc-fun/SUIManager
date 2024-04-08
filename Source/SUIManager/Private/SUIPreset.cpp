// Copyright Serinc All Rights Reserved.
#include "SUIPreset.h"

#include "Widgets/SUIWidget.h"

USUIWidget* USUIPreset::CreatePresetWidget(TSubclassOf<USUIWidget> InWidgetClass)
{
	if (InWidgetClass)
	{
		USUIWidget* LCreatedWidget = ::CreateWidget<USUIWidget>(GetOwningPlayer(), TSubclassOf<UUserWidget>(InWidgetClass));
		if (IsValid(LCreatedWidget))
		{
			LCreatedWidget->ParentPreset = this;
			
			Widgets.Add(LCreatedWidget);
			return LCreatedWidget;
		}
	}

	return nullptr;
}

bool USUIPreset::RemovePresetWidget(USUIWidget* InWidget)
{
	if (IsValid(InWidget) && Widgets.Contains(InWidget))
	{
		InWidget->ParentPreset = nullptr;
		InWidget->DeactivateWidget();

		Widgets.Remove(InWidget);
		return true;
	}

	return false;
}

APlayerController* USUIPreset::GetOwningPlayer() const
{
	if (IsValid(LocalPlayer))
	{
		return LocalPlayer->GetPlayerController(GetWorld());	
	}

	return nullptr;
}

APawn* USUIPreset::GetOwningPawn() const
{
	if (IsValid(LocalPlayer))
	{
		return LocalPlayer->GetPlayerController(GetWorld())->GetPawnOrSpectator();			
	}

	return nullptr;
}

UWorld* USUIPreset::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && IsValid(LocalPlayer))
	{
		return LocalPlayer->GetWorld();
	}

	return nullptr;
}

void USUIPreset::OnDeinitialize_Implementation()
{
	
}

void USUIPreset::OnInitialize_Implementation()
{
	
}
