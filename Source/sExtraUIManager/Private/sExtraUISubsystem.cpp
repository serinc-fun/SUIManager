// Copyright Serinc All Rights Reserved.
#include "sExtraUISubsystem.h"

UsExtraUIManagerSubsystem* UsExtraUIManagerSubsystem::Get(const UWorld* InWorld)
{
	if (IsValid(InWorld))
	{
		return InWorld->GetSubsystem<UsExtraUIManagerSubsystem>();
	}

	return nullptr;
}

void UsExtraUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UsExtraUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UsExtraUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (Super::ShouldCreateSubsystem(Outer))
	{
		return !IsRunningDedicatedServer();
	}

	return false;
}
