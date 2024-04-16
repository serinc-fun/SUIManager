// Copyright Serinc All Rights Reserved.
#include "SUIPreset.h"
#include "SUIDefine.h"
#if IS_SUPPORT_GVS
#include "Blueprint/GameViewportSubsystem.h"
#endif
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

void USUIPreset::OnInitialize()
{
#if IS_SUPPORT_GVS
	UGameViewportSubsystem::Get()->OnWidgetAdded.AddUObject(this, &USUIPreset::OnWidgetAddedToViewport);
#endif	
	
	OnInitialized();
}

void USUIPreset::OnDeinitialize()
{
	for (USUIWidget* Widget : Widgets)
	{
		Widget->RemoveFromParent();
	}

#if IS_SUPPORT_GVS
	UGameViewportSubsystem::Get()->OnWidgetAdded.RemoveAll(this);
#endif
	
	OnDeinitialized();
}

void USUIPreset::OnWidgetAddedToViewport(UWidget* InWidget, ULocalPlayer* InPlayer)
{
	if (Widgets.Contains(InWidget))
	{
		Cast<USUIWidget>(InWidget)->OnAddedToViewport();
	}
}

