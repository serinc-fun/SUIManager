// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SUIPreset.generated.h"

class UWidget;
class USUIWidget;
/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class SUIMANAGER_API USUIPreset : public UObject
{
	friend class USUIManagerSubsystem;
	 
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	USUIWidget* CreatePresetWidget(TSubclassOf<USUIWidget> InWidgetClass);

	UFUNCTION(BlueprintCallable)
	bool RemovePresetWidget(USUIWidget* InWidget);
	
	UFUNCTION(BlueprintPure)
	APlayerController* GetOwningPlayer() const;

	UFUNCTION(BlueprintPure)
	APawn* GetOwningPawn() const;

	UFUNCTION(BlueprintPure)
	FORCEINLINE FName GetPresetName() const { return PresetName; }

	virtual UWorld* GetWorld() const override final;	
	
protected:

	virtual void OnInitialize();
	virtual void OnDeinitialize();

	virtual void OnWidgetAddedToViewport(UWidget* InWidget, ULocalPlayer* InPlayer);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialized();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeinitialized();
	
	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	FName PresetName;

	UPROPERTY(Transient, BlueprintReadOnly)
	ULocalPlayer* LocalPlayer;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<USUIWidget*> Widgets;
};
