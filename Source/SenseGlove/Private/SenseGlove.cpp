// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SenseGlove.h"

#define LOCTEXT_NAMESPACE "FSenseGloveModule"
DEFINE_LOG_CATEGORY(SenseGlove);

void FSenseGloveModule::StartupModule()
{
	UE_LOG(SenseGlove, Log, TEXT("Initialising SenseGlove Module!"));
}

void FSenseGloveModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSenseGloveModule, SenseGlove)