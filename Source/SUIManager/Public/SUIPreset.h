// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SUIPreset.generated.h"

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

	UFUNCTION(BlueprintNativeEvent)
	void OnInitialize();

	UFUNCTION(BlueprintNativeEvent)
	void OnDeinitialize();
	
	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	FName PresetName;

	UPROPERTY(Transient, BlueprintReadOnly)
	ULocalPlayer* LocalPlayer;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<USUIWidget*> Widgets;
};
