// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"

#include "sExtraUIWidget.generated.h"

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
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "sExtraUI|Manager|Widget")
	FORCEINLINE bool IsActive() const { return bIsActive; }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "sExtraUI|Manager|Widget")
	void ActivateWidget();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "sExtraUI|Manager|Widget")
	void DeactivateWidget();
	
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

	void AddToViewport(int32 ZOrder = 0) = delete;
	bool AddToPlayerScreen(int32 ZOrder = 0) = delete;
};
