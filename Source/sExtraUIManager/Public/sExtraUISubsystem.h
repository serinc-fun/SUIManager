// Copyright Serinc All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "WorldSubsystem.h"
#include "sExtraUISubsystem.generated.h"

class UsExtraUIPreset;
/**
 * 
 */
UCLASS()
class SEXTRAUIMANAGER_API UsExtraUIManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	static UsExtraUIManagerSubsystem* Get(const UWorld* InWorld);
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

protected:

	UPROPERTY(Transient)
	TArray<UsExtraUIPreset*> Presets;
};
