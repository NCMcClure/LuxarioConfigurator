// Copyright (c) 2018 Nineva Studios

#include "IOSGoodiesModule.h"

#define LOCTEXT_NAMESPACE "IOSGoodies"

class FIOSGoodiesModule : public IOSGoodiesModule
{
public:
    
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FIOSGoodiesModule, IOSGoodies)

void FIOSGoodiesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FIOSGoodiesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
