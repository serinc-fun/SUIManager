// Copyright Serinc All Rights Reserved.
#include "sExtraUISubsystem.h"

#include "sExtraUIPreset.h"
#include "sExtraUIPresetDefault.h"

UsExtraUIManagerSubsystem* UsExtraUIManagerSubsystem::Get(const UWorld* InWorld)
{
	if (IsValid(InWorld))
	{
		return InWorld->GetSubsystem<UsExtraUIManagerSubsystem>();
	}

	return nullptr;
}

void UsExtraUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UsExtraUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UsExtraUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (Super::ShouldCreateSubsystem(Outer))
	{
		return !IsRunningDedicatedServer();
	}

	return false;
}

UsExtraUIPreset* UsExtraUIManagerSubsystem::AddPreset(const TSubclassOf<UsExtraUIPreset>& InPresetClass)
{
	const auto LPresetInstance = NewObject<UsExtraUIPreset>(this, InPresetClass);

	if (IsValid(LPresetInstance))
	{
		LPresetInstance->LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		
		Presets.Add(LPresetInstance);
		PresetsMultiMap.Add(InPresetClass, LPresetInstance);

		LPresetInstance->OnInitialize();
	}

	return LPresetInstance;
}

UsExtraUIPreset* UsExtraUIManagerSubsystem::AddPresetUnique(const TSubclassOf<UsExtraUIPreset>& InPresetClass)
{
	if (!IsExistPreset(InPresetClass))
	{
		return AddPreset(InPresetClass);
	}

	return nullptr;
}

bool UsExtraUIManagerSubsystem::IsExistPreset(const TSubclassOf<UsExtraUIPreset>& InPresetClass) const
{
	return PresetsMultiMap.Contains(InPresetClass);
}

void UsExtraUIManagerSubsystem::RemovePreset(UsExtraUIPreset* InPreset)
{
	if (IsValid(InPreset))
	{
		InPreset->OnDeinitialize();

		PresetsMultiMap.RemoveSingle(InPreset->GetClass(), InPreset);
		Presets.Remove(InPreset);
	}
}

void UsExtraUIManagerSubsystem::RemovePresets(const TSubclassOf<UsExtraUIPreset>& InPresetClass)
{
	TArray<UsExtraUIPreset*> LFoundPresets;
	PresetsMultiMap.MultiFind(InPresetClass, LFoundPresets);

	for (const auto LPreset : LFoundPresets)
	{
		if (IsValid(LPreset))
		{
			LPreset->OnDeinitialize();
		}
	}

	PresetsMultiMap.Remove(InPresetClass);
	Presets.RemoveAll([&] (const UsExtraUIPreset* InA) -> bool
	{
		return InA->GetClass()->IsChildOf(InPresetClass);
	});
}

UsExtraUIPresetDefault* UsExtraUIManagerSubsystem::GetDefaultPreset() const
{
	if (!IsValid(DefaultPreset))
	{
		DefaultPreset = NewObject<UsExtraUIPresetDefault>(const_cast<UsExtraUIManagerSubsystem*>(this));
		DefaultPreset->LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		DefaultPreset->OnInitialize();
	}

	return DefaultPreset;
}
