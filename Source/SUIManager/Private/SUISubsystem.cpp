// Copyright Serinc All Rights Reserved.
#include "SUISubsystem.h"

#include "SUIPreset.h"
#include "SUIPresetDefault.h"
#include "Widgets/SUIWidget.h"

USUIManagerSubsystem* USUIManagerSubsystem::Get(const UObject* InWorldContext)
{
	const auto LWorld = GEngine->GetWorldFromContextObject(InWorldContext, EGetWorldErrorMode::ReturnNull);
	if (IsValid(LWorld))
	{
		return LWorld->GetSubsystem<USUIManagerSubsystem>();
	}

	return nullptr;
}

void USUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool USUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (Super::ShouldCreateSubsystem(Outer))
	{
		return !IsRunningDedicatedServer();
	}

	return false;
}

void USUIManagerSubsystem::DetermineInput()
{
	if (ActiveWidgets.Num() > 0)
	{
		ActiveWidgets.Sort([] (USUIWidget& InA, USUIWidget& InB) -> bool
		{
			return InA.TargetZOrder > InB.TargetZOrder;
		});
	
		const auto LLastActiveWidget = ActiveWidgets.Last();
		if (IsValid(LLastActiveWidget))
		{
			const auto LPlayerController = LLastActiveWidget->GetOwningPlayer();
			const auto LFlags = LLastActiveWidget->GetActivateFlags();

			if ((LFlags & EsExtraUIWidgetActiveWith::Without | EsExtraUIWidgetActiveWith::None) != 0)
			{
				LPlayerController->SetInputMode(FInputModeGameOnly().SetConsumeCaptureMouseDown(true));
				LPlayerController->SetShowMouseCursor(false);
			}

			if ((LFlags & EsExtraUIWidgetActiveWith::WithInput) != 0)
			{
				LPlayerController->SetInputMode(FInputModeUIOnly().SetWidgetToFocus(LLastActiveWidget->GetCachedWidget()));
			}

			if ((LFlags & EsExtraUIWidgetActiveWith::WithCursor) != 0)
			{
				LPlayerController->SetShowMouseCursor(true);
			}
		}
	}
	else
	{
		const auto LPlayerController = GetWorld()->GetFirstPlayerController();
		
		LPlayerController->SetInputMode(FInputModeGameOnly().SetConsumeCaptureMouseDown(true));
		LPlayerController->SetShowMouseCursor(false);
	}
}

void USUIManagerSubsystem::WidgetActiveStateChange(USUIWidget* InWidget, bool InState)
{
	if (IsValid(InWidget))
	{
		if (InState)
			ActiveWidgets.Add(InWidget);
		else
			ActiveWidgets.Remove(InWidget);

		DetermineInput();
	}
}

USUIPreset* USUIManagerSubsystem::AddPreset(const TSubclassOf<USUIPreset>& InPresetClass)
{
	const auto LPresetInstance = NewObject<USUIPreset>(this, InPresetClass);

	if (IsValid(LPresetInstance))
	{
		LPresetInstance->LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		
		Presets.Add(LPresetInstance);
		PresetsMultiMap.Add(InPresetClass, LPresetInstance);

		LPresetInstance->OnInitialize();
	}

	return LPresetInstance;
}

USUIPreset* USUIManagerSubsystem::AddPresetUnique(const TSubclassOf<USUIPreset>& InPresetClass)
{
	if (!IsExistPreset(InPresetClass))
	{
		return AddPreset(InPresetClass);
	}

	return nullptr;
}

bool USUIManagerSubsystem::IsExistPreset(const TSubclassOf<USUIPreset>& InPresetClass) const
{
	return PresetsMultiMap.Contains(InPresetClass);
}

void USUIManagerSubsystem::RemovePreset(USUIPreset* InPreset)
{
	if (IsValid(InPreset))
	{
		InPreset->OnDeinitialize();

		PresetsMultiMap.RemoveSingle(InPreset->GetClass(), InPreset);
		Presets.Remove(InPreset);
	}
}

void USUIManagerSubsystem::RemovePresets(const TSubclassOf<USUIPreset>& InPresetClass)
{
	TArray<USUIPreset*> LFoundPresets;
	PresetsMultiMap.MultiFind(InPresetClass, LFoundPresets);

	for (const auto LPreset : LFoundPresets)
	{
		if (IsValid(LPreset))
		{
			LPreset->OnDeinitialize();
		}
	}

	PresetsMultiMap.Remove(InPresetClass);
	Presets.RemoveAll([&] (const USUIPreset* InA) -> bool
	{
		return InA->GetClass()->IsChildOf(InPresetClass);
	});
}

USUIPresetDefault* USUIManagerSubsystem::GetDefaultPreset() const
{
	if (!IsValid(DefaultPreset))
	{
		DefaultPreset = NewObject<USUIPresetDefault>(const_cast<USUIManagerSubsystem*>(this));
		DefaultPreset->LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		DefaultPreset->OnInitialize();
	}

	return DefaultPreset;
}
