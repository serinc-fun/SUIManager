// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SUIDefine.h"
#if IS_SUPPORT_GVS
#include "Blueprint/GameViewportSubsystem.h"
#endif
#include "SUISubsystem.generated.h"

class USUIWidget;
class USUIPreset;
class USUIPresetDefault;
/**
 * 
 */
UCLASS()
class SUIMANAGER_API USUIManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "sExtraUI|Manager", DisplayName = "Get sExtraUI Manager Subsystem", meta = (WorldContext="InWorldContext"))
	static USUIManagerSubsystem* Get(const UObject* InWorldContext);

	// UWorldSubsystem overrides begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// UWorldSubsystem overrides end
	
	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	void DetermineInput();

	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	void WidgetActiveStateChange(USUIWidget* InWidget, bool InState);
	
	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	USUIPreset* AddPreset(const TSubclassOf<USUIPreset>& InPresetClass);

	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	USUIPreset* AddPresetUnique(const TSubclassOf<USUIPreset>& InPresetClass);

	UFUNCTION(BlueprintPure, Category = "sExtraUI|Manager")
	bool IsExistPreset(const TSubclassOf<USUIPreset>& InPresetClass) const;

	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	void RemovePreset(USUIPreset* InPreset);
	
	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager")
	void RemovePresets(const TSubclassOf<USUIPreset>& InPresetClass);

	UFUNCTION(BlueprintPure, Category = "sExtraUI|Manager")
	USUIPresetDefault* GetDefaultPreset() const;

protected:

	UPROPERTY(Transient)
	TArray<USUIPreset*> Presets;

	UPROPERTY(Transient)
	mutable USUIPresetDefault* DefaultPreset;

	UPROPERTY(Transient)
	TArray<USUIWidget*> ActiveWidgets;

	TMultiMap<TSubclassOf<USUIPreset>, USUIPreset*> PresetsMultiMap;
};
