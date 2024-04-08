﻿// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SUIDefine.h"
#include "SUIWidget.generated.h"

class USUIPreset;

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
namespace EsExtraUIWidgetActiveWith
{
	enum Type
	{
		None			= 0,		// Required for Engine, not used
		Without			= 1 << 0,	// Don't take any controls, only show widget
		WithInput		= 1 << 1,	// Input will be focused on widget, without showing cursor
		WithCursor		= 1 << 2	// Only for show cursor
	};
}
ENUM_CLASS_FLAGS(EsExtraUIWidgetActiveWith::Type);
/**
 * 
 */
UCLASS(Abstract)
class SUIMANAGER_API USUIWidget : public UUserWidget
{
	friend class USUIPreset;
	friend class USUIManagerSubsystem;
	
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "sExtraUI|Manager|Widget")
	FORCEINLINE bool IsActive() const { return bIsActive; }

	UFUNCTION(BlueprintPure, Category = "sExtraUI|Manager|Widget")
	UPARAM(meta = (Bitmask, BitmaskEnum = EsExtraUIWidgetActiveWith)) int32 GetActivateFlags() const { return ActivateFlags; }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "sExtraUI|Manager|Widget")
	void ActivateWidget();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "sExtraUI|Manager|Widget")
	void DeactivateWidget();

	virtual void RemoveFromParent() override;
	
protected:

#if !IS_SUPPORT_GVS
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;
#endif
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = EsExtraUIWidgetActiveWith), Category = Configuration)
	int32 ActivateFlags = EsExtraUIWidgetActiveWith::WithCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Configuration)
	ESlateVisibility ActivateVisibility = ESlateVisibility::SelfHitTestInvisible;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Configuration)
	ESlateVisibility DeactivateVisibility = ESlateVisibility::Collapsed;

	UPROPERTY(Transient, BlueprintReadOnly)
	bool bIsActive = false;

private:

	UPROPERTY(Transient)
	USUIPreset* ParentPreset;

	UPROPERTY(Transient)
	int32 TargetZOrder = 0;
	
};
