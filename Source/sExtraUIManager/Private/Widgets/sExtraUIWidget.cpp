// Copyright Serinc All Rights Reserved.
#include "sExtraUIWidget.h"

#include "sExtraUIPreset.h"
#include "sExtraUISubsystem.h"

void UsExtraUIWidget::ActivateWidget_Implementation()
{
	if (!IsActive())
	{
		bIsActive = true;
		SetVisibility(ActivateVisibility);

		if (IsValid(ParentPreset))
		{
			UsExtraUIManagerSubsystem::Get(GetWorld())->WidgetActiveStateChange(this, true);
		}
	}
}

void UsExtraUIWidget::DeactivateWidget_Implementation()
{
	if (IsActive())
	{
		bIsActive = false;
		SetVisibility(DeactivateVisibility);

		if (IsValid(ParentPreset))
		{
			UsExtraUIManagerSubsystem::Get(GetWorld())->WidgetActiveStateChange(this, false);
		}
	}
}

void UsExtraUIWidget::RemoveFromParent()
{
	if (IsValid(ParentPreset))
	{
		ParentPreset->RemovePresetWidget(this);
	}
	
	Super::RemoveFromParent();
}

void UsExtraUIWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	TargetZOrder = ZOrder + 10;

	Super::AddToScreen(LocalPlayer, ZOrder);
}
