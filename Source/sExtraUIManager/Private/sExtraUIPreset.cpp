// Copyright Serinc All Rights Reserved.
#include "sExtraUIPreset.h"

#include "Widgets/sExtraUIWidget.h"

UsExtraUIWidget* UsExtraUIPreset::CreatePresetWidget(TSubclassOf<UsExtraUIWidget> InWidgetClass)
{
	if (InWidgetClass)
	{
		UsExtraUIWidget* LCreatedWidget = ::CreateWidget<UsExtraUIWidget>(GetOwningPlayer(), TSubclassOf<UUserWidget>(InWidgetClass));
		if (IsValid(LCreatedWidget))
		{
			LCreatedWidget->ParentPreset = this;
			
			Widgets.Add(LCreatedWidget);
			return LCreatedWidget;
		}
	}

	return nullptr;
}

bool UsExtraUIPreset::RemovePresetWidget(UsExtraUIWidget* InWidget)
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

APlayerController* UsExtraUIPreset::GetOwningPlayer() const
{
	if (IsValid(LocalPlayer))
	{
		return LocalPlayer->GetPlayerController(GetWorld());	
	}

	return nullptr;
}

APawn* UsExtraUIPreset::GetOwningPawn() const
{
	if (IsValid(LocalPlayer))
	{
		return LocalPlayer->GetPlayerController(GetWorld())->GetPawnOrSpectator();			
	}

	return nullptr;
}

UWorld* UsExtraUIPreset::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && IsValid(LocalPlayer))
	{
		return LocalPlayer->GetWorld();
	}

	return nullptr;
}

void UsExtraUIPreset::OnDeinitialize_Implementation()
{
	
}

void UsExtraUIPreset::OnInitialize_Implementation()
{
	
}
