// Copyright Serinc All Rights Reserved.
#include "K2Node_CreatePresetWidget.h"

#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "SUIPreset.h"
#include "KismetNodes/SGraphNodeK2Default.h"
#include "Widgets/SUIWidget.h"

TSharedPtr<SGraphNode> UK2Node_CreatePresetWidget::CreateVisualWidget()
{
	return SNew(SGraphNodeK2Default, this);
}

void UK2Node_CreatePresetWidget::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	static const FName Create_FunctionName = GET_FUNCTION_NAME_CHECKED(USUIPreset, CreatePresetWidget);
	static const FName WidgetType_ParamName = TEXT("InWidgetClass");

	UK2Node_CreatePresetWidget* CreateWidgetNode = this;
	UEdGraphPin* SpawnNodeExec = CreateWidgetNode->GetExecPin();
	UEdGraphPin* SpawnClassPin = CreateWidgetNode->GetClassPin();
	UEdGraphPin* SpawnNodeThen = CreateWidgetNode->GetThenPin();
	UEdGraphPin* SpawnNodeResult = CreateWidgetNode->GetResultPin();

	UClass* SpawnClass = ( SpawnClassPin != NULL ) ? Cast<UClass>(SpawnClassPin->DefaultObject) : NULL;
	if ( !SpawnClassPin || ((0 == SpawnClassPin->LinkedTo.Num()) && (NULL == SpawnClass)))
	{
		CompilerContext.MessageLog.Error(*NSLOCTEXT("UK2Node_CreatePresetWidget", "CreateWidgetNodeMissingClass_Error", "Spawn node @@ must have a class specified.").ToString(), CreateWidgetNode);
		// we break exec links so this is the only error we get, don't want the CreateWidget node being considered and giving 'unexpected node' type warnings
		CreateWidgetNode->BreakAllNodeLinks();
		return;
	}
	
	//////////////////////////////////////////////////////////////////////////
	// create 'UWidgetBlueprintLibrary::Create' call node
	UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(CreateWidgetNode, SourceGraph);
	//CallCreateNode->FunctionReference.SetExternalMember(Create_FunctionName, UUIPresset::StaticClass());
	const auto LFoundFunction = USUIPreset::StaticClass()->FindFunctionByName(Create_FunctionName);
	CallCreateNode->FunctionReference.SetFromField<UFunction>(LFoundFunction, true, USUIPreset::StaticClass());
	CallCreateNode->AllocateDefaultPins();

	// store off the class to spawn before we mutate pin connections:
	UClass* ClassToSpawn = GetClassToSpawn();

	UEdGraphPin* CallCreateExec = CallCreateNode->GetExecPin();
	UEdGraphPin* CallCreateWidgetTypePin = CallCreateNode->FindPinChecked(WidgetType_ParamName);
	UEdGraphPin* CallCreateResult = CallCreateNode->GetReturnValuePin();

	// Move 'exec' connection from create widget node to 'UWidgetBlueprintLibrary::Create'
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeExec, *CallCreateExec);

	if ( SpawnClassPin->LinkedTo.Num() > 0 )
	{
		// Copy the 'blueprint' connection from the spawn node to 'UWidgetBlueprintLibrary::Create'
		CompilerContext.MovePinLinksToIntermediate(*SpawnClassPin, *CallCreateWidgetTypePin);
	}
	else
	{
		// Copy blueprint literal onto 'UWidgetBlueprintLibrary::Create' call
		CallCreateWidgetTypePin->DefaultObject = SpawnClass;
	}

	// Move result connection from spawn node to 'UWidgetBlueprintLibrary::Create'
	CallCreateResult->PinType = SpawnNodeResult->PinType; // Copy type so it uses the right actor subclass
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeResult, *CallCreateResult);

	//////////////////////////////////////////////////////////////////////////
	// create 'set var' nodes

	// Get 'result' pin from 'begin spawn', this is the actual actor we want to set properties on
	UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallCreateNode, CreateWidgetNode, CallCreateResult, ClassToSpawn);

	// Move 'then' connection from create widget node to the last 'then'
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeThen, *LastThen);

	// Break any links to the expanded node
	CreateWidgetNode->BreakAllNodeLinks();
}

FText UK2Node_CreatePresetWidget::GetBaseNodeTitle() const
{
	return NSLOCTEXT("UK2Node_CreatePresetWidget", "CreateWidget_BaseTitle", "Create Preset Widget");
}

FText UK2Node_CreatePresetWidget::GetNodeTitleFormat() const
{
	return NSLOCTEXT("UK2Node_CreatePresetWidget", "CreateWidget", "Create {ClassName} Widget for Preset");
}

UClass* UK2Node_CreatePresetWidget::GetClassPinBaseClass() const
{
	return USUIWidget::StaticClass();
}
