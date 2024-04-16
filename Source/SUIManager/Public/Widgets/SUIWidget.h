// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SUIDefine.h"
#include "SUIWidget.generated.h"

class USUIPreset;

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
namespace ESUIWidgetActiveWith
{
	enum Type
	{
		None			= 0,		// Required for Engine, not used
		Without			= 1 << 0,	// Don't take any controls, only show widget
		WithInput		= 1 << 1,	// Input will be focused on widget, without showing cursor
		WithCursor		= 1 << 2	// Only for show cursor
	};
}
ENUM_CLASS_FLAGS(ESUIWidgetActiveWith::Type);
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
	
	UFUNCTION(BlueprintPure, Category = "SUI|Manager|Widget")
	FORCEINLINE bool IsActive() const { return bIsActive; }

	UFUNCTION(BlueprintPure, Category = "SUI|Manager|Widget")
	UPARAM(meta = (Bitmask, BitmaskEnum = ESUIWidgetActiveWith)) int32 GetActivateFlags() const { return ActivateFlags; }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SUI|Manager|Widget")
	void ActivateWidget();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SUI|Manager|Widget")
	void DeactivateWidget();

	virtual void RemoveFromParent() override;
	
protected:

#if !IS_SUPPORT_GVS
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;
#endif

	virtual void OnAddedToViewport(); 
	
	UFUNCTION(BlueprintNativeEvent, Category = "SUI|Manager|Widget")
	void OnWidgetStateChanged(bool bIsActivated);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = ESUIWidgetActiveWith), Category = Configuration)
	int32 ActivateFlags = ESUIWidgetActiveWith::WithCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Configuration)
	ESlateVisibility ActivateVisibility = ESlateVisibility::SelfHitTestInvisible;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Configuration)
	ESlateVisibility DeactivateVisibility = ESlateVisibility::Collapsed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Configuration)
	bool bAutoActivate = false;

	UPROPERTY(Transient, BlueprintReadOnly)
	bool bIsActive = false;

private:

	UPROPERTY(Transient)
	USUIPreset* ParentPreset;

	UPROPERTY(Transient)
	int32 TargetZOrder = 0;
	
};
