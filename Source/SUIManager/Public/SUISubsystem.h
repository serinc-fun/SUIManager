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

	UFUNCTION(BlueprintPure, Category = "SUI|Manager", DisplayName = "Get SUI Manager Subsystem", meta = (WorldContext="InWorldContext"))
	static USUIManagerSubsystem* Get(const UObject* InWorldContext);

	// UWorldSubsystem overrides begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// UWorldSubsystem overrides end
	
	UFUNCTION(BlueprintCallable, Category = "SUI|Manager")
	void DetermineInput();

	UFUNCTION(BlueprintCallable, Category = "SUI|Manager")
	void WidgetActiveStateChange(USUIWidget* InWidget, bool InState);
	
	UFUNCTION(BlueprintCallable, Category = "SUI|Manager")
	USUIPreset* AddPreset(const TSubclassOf<USUIPreset>& InPresetClass);

	UFUNCTION(BlueprintCallable, Category = "SUI|Manager")
	USUIPreset* AddPresetUnique(const TSubclassOf<USUIPreset>& InPresetClass);

	UFUNCTION(BlueprintPure, Category = "SUI|Manager")
	bool IsExistPreset(const TSubclassOf<USUIPreset>& InPresetClass) const;

	UFUNCTION(BlueprintCallable, Category = "SUI|Manager")
	void RemovePreset(USUIPreset* InPreset);
	
	UFUNCTION(BlueprintCallable, Category = "SUI|Manager")
	void RemovePresets(const TSubclassOf<USUIPreset>& InPresetClass);

	UFUNCTION(BlueprintPure, Category = "SUI|Manager")
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
