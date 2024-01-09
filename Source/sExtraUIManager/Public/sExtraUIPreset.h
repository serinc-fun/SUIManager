// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "sExtraUIPreset.generated.h"

class UsExtraUIWidget;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract, HideFunctions=(CreateWidget, AddToViewport))
class SEXTRAUIMANAGER_API UsExtraUIPreset : public UObject
{
	friend class UsExtraUIManagerSubsystem;
	 
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	UsExtraUIWidget* CreatePresetWidget(TSubclassOf<UsExtraUIWidget> InWidgetClass);

	UFUNCTION(BlueprintCallable)
	bool RemovePresetWidget(UsExtraUIWidget* InWidget);
	
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
	TArray<UsExtraUIWidget*> Widgets;
};
