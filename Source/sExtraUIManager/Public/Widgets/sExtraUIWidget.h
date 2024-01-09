// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"

#include "sExtraUIWidget.generated.h"

class UsExtraUIPreset;
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
UCLASS(Abstract, HideFunctions=(AddToViewport))
class SEXTRAUIMANAGER_API UsExtraUIWidget : public UUserWidget
{
	friend class UsExtraUIPreset;
	
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "sExtraUI|Manager|Widget")
	virtual void AddWidgetToViewport(int32 ZOrder = 0);
	
	UFUNCTION(BlueprintPure, Category = "sExtraUI|Manager|Widget")
	FORCEINLINE bool IsActive() const { return bIsActive; }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "sExtraUI|Manager|Widget")
	void ActivateWidget();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "sExtraUI|Manager|Widget")
	void DeactivateWidget();

	virtual void RemoveFromParent() override;
	
protected:

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
	UsExtraUIPreset* ParentPreset;
	
	void AddToViewport(int32 ZOrder = 0) = delete;
	bool AddToPlayerScreen(int32 ZOrder = 0) = delete;
};
