// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "WorldSubsystem.h"
#include "sExtraUISubsystem.generated.h"

class UsExtraUIWidget;
class UsExtraUIPreset;
class UsExtraUIPresetDefault;
/**
 * 
 */
UCLASS()
class SEXTRAUIMANAGER_API UsExtraUIManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "sExtraUI|Manager", DisplayName = "Get sExtraUI Manager Subsystem")
	static UsExtraUIManagerSubsystem* Get(const UWorld* InWorld);

	// UWorldSubsystem overrides begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// UWorldSubsystem overrides end

	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	void DetermineInput();

	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	void WidgetActiveStateChange(UsExtraUIWidget* InWidget, bool InState);
	
	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	UsExtraUIPreset* AddPreset(const TSubclassOf<UsExtraUIPreset>& InPresetClass);

	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	UsExtraUIPreset* AddPresetUnique(const TSubclassOf<UsExtraUIPreset>& InPresetClass);

	UFUNCTION(BlueprintPure, Category = "sExtraUI|Manager")
	bool IsExistPreset(const TSubclassOf<UsExtraUIPreset>& InPresetClass) const;

	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	void RemovePreset(UsExtraUIPreset* InPreset);
	
	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	void RemovePresets(const TSubclassOf<UsExtraUIPreset>& InPresetClass);

	UFUNCTION(BlueprintPure, Category = "sExtraUI|Manager")
	UsExtraUIPresetDefault* GetDefaultPreset() const;

protected:

	UPROPERTY(Transient)
	TArray<UsExtraUIPreset*> Presets;

	UPROPERTY(Transient)
	mutable UsExtraUIPresetDefault* DefaultPreset;

	UPROPERTY(Transient)
	TArray<UsExtraUIWidget*> ActiveWidgets;

	TMultiMap<TSubclassOf<UsExtraUIPreset>, UsExtraUIPreset*> PresetsMultiMap;
};
