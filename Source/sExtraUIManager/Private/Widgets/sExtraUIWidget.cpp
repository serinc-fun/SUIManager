// Copyright Serinc All Rights Reserved.
#include "sExtraUIWidget.h"

#include "sExtraUIPreset.h"

void UsExtraUIWidget::ActivateWidget_Implementation()
{
	if (!IsActive())
	{
		bIsActive = true;
		SetVisibility(ActivateVisibility);
	}
}

void UsExtraUIWidget::DeactivateWidget_Implementation()
{
	if (IsActive())
	{
		bIsActive = false;
		SetVisibility(DeactivateVisibility);
	}
}

void UsExtraUIWidget::AddWidgetToViewport(int32 ZOrder)
{
	if (IsValid(ParentPreset))
	{
		Super::AddToViewport(ZOrder);
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
