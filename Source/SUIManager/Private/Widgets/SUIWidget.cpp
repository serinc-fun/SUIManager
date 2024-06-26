﻿// Copyright Serinc All Rights Reserved.
#include "Widgets/SUIWidget.h"

#include "SUIPreset.h"
#include "SUISubsystem.h"


void USUIWidget::ActivateWidget_Implementation()
{
	if (!IsActive())
	{
		bIsActive = true;
		SetVisibility(ActivateVisibility);

		if (IsValid(ParentPreset))
		{
			USUIManagerSubsystem::Get(GetWorld())->WidgetActiveStateChange(this, true);
		}
	}
}

void USUIWidget::DeactivateWidget_Implementation()
{
	if (IsActive())
	{
		bIsActive = false;
		SetVisibility(DeactivateVisibility);

		if (IsValid(ParentPreset))
		{
			USUIManagerSubsystem::Get(GetWorld())->WidgetActiveStateChange(this, false);
		}
	}
}

void USUIWidget::RemoveFromParent()
{
	if (IsValid(ParentPreset))
	{
		ParentPreset->RemovePresetWidget(this);
	}
	
	Super::RemoveFromParent();
}

void USUIWidget::OnAddedToViewport()
{
	if (bAutoActivate)
	{
		ActivateWidget();
	}
}

void USUIWidget::OnWidgetStateChanged_Implementation(bool bIsActivated)
{
	
}

#if !IS_SUPPORT_GVS
void USUIWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	TargetZOrder = ZOrder + 10;

	Super::AddToScreen(LocalPlayer, ZOrder);
}
#endif
