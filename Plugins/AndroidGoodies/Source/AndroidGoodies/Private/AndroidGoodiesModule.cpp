// Copyright (c) 2018 Nineva Studios

#include "IAndroidGoodiesModule.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "AndroidGoodiesSettings.h"

#define LOCTEXT_NAMESPACE "AndroidGoodies"

class FAndroidGoodiesModule : public IAndroidGoodiesModule
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	UAndroidGoodiesSettings* AndroidGoodiesSettings;
};

IMPLEMENT_MODULE(FAndroidGoodiesModule, AndroidGoodies)

void FAndroidGoodiesModule::StartupModule()
{
	AndroidGoodiesSettings = NewObject<UAndroidGoodiesSettings>(GetTransientPackage(), "AndroidGoodiesSettings", RF_Standalone);
	AndroidGoodiesSettings->AddToRoot();

	// Register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Android Goodies",
			LOCTEXT("RuntimeSettingsName", "Android Goodies"),
			LOCTEXT("RuntimeSettingsDescription", "Configure Android Goodies"),
			AndroidGoodiesSettings);
	}
}

void FAndroidGoodiesModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Android Goodies");
	}

	if (!GExitPurge)
	{
		// If we're in exit purge, this object has already been destroyed
		AndroidGoodiesSettings->RemoveFromRoot();
	}
	else
	{
		AndroidGoodiesSettings = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE
