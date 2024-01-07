// Copyright Serinc All Rights Reserved.
#include "sExtraUIWidget.h"

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
