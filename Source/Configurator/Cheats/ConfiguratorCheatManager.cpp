// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfiguratorCheatManager.h"

#include "Configurator/Blueprint/InstagramBlueprintStatics.h"

#include "Engine/Texture2D.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif



void UConfiguratorCheatManager::ConfiguratorShareSampleToInstagram()
{
	if (UTexture2D* SampleInstagramTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/InstagramSample"))))
	{
		UInstagramBlueprintStatics::ShareToInstagram(SampleInstagramTexture);
	}
}

UObject* UConfiguratorCheatManager::LoadObjectFromAssetPath(TSubclassOf<UObject> ObjectClass, FName Path, bool& IsValid)
{
	IsValid = false;

	if (Path == NAME_None) return NULL;
	//~~~~~~~~~~~~~~~~~~~~~

	UObject* LoadedObj = StaticLoadObject(ObjectClass, NULL, *Path.ToString());

	IsValid = LoadedObj != nullptr;

	return LoadedObj;
}