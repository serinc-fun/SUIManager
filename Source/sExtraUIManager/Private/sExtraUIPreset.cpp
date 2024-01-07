// Copyright Serinc All Rights Reserved.
#include "sExtraUIPreset.h"

#include "sExtraUIWidget.h"
#include "Blueprint/UserWidget.h"

UsExtraUIWidget* UsExtraUIPreset::CreatePresetWidget(TSubclassOf<UsExtraUIWidget> InWidgetClass)
{
	if (InWidgetClass)
	{
		UsExtraUIWidget* LCreatedWidget = ::CreateWidget<UsExtraUIWidget>(GetOwningPlayer(), TSubclassOf<UUserWidget>(InWidgetClass));
		if (IsValid(LCreatedWidget))
		{
			Widgets.Add(LCreatedWidget);
			return LCreatedWidget;
		}
	}

	return nullptr;
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
