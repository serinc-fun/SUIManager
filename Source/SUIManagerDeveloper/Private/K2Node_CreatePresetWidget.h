// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "K2Node_ConstructObjectFromClass.h"
#include "K2Node_CreatePresetWidget.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UK2Node_CreatePresetWidget : public UK2Node_ConstructObjectFromClass
{
	GENERATED_BODY()

public:

	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual FText GetBaseNodeTitle() const override;
	virtual FText GetNodeTitleFormat() const override;
	virtual UClass* GetClassPinBaseClass() const override;
};
