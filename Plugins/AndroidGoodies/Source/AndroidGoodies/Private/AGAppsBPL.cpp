// Copyright (c) 2018 Nineva Studios

#include "AGAppsBPL.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif

static const ANSICHAR* AGAppsClassName = "com/ninevastudios/androidgoodies/AGApps";

UAGApps::UAGApps(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAGApps::OpenYoutubeVideo(FString videoId)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "watchYoutubeVideo", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(videoId));

#endif
}

void UAGApps::OpenTwitterProfile(FString profileId)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "openTwitterProfile", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(profileId));

#endif
}

void UAGApps::OpenInstagramProfile(FString profileId)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "openInstagramProfile", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(profileId));

#endif
}

void UAGApps::OpenFacebookProfile(FString profileId)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "openFacebookProfile", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(profileId));

#endif
}

void UAGApps::OpenAnotherApplication(FString packageName)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "openAnotherApplication", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(packageName));

#endif
}

void UAGApps::UninstallPackage(FString packageName)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "uninstallPackage", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(packageName));

#endif
}

void UAGApps::InstallApkFromFile(FString filePath)
{
#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "installApkFromFile", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(filePath));

#endif
}

bool UAGApps::HasPhoneApp()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGAppsClassName, "hasPhoneApp", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return false;
}

void UAGApps::DialPhoneNumber(FString number)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "dialPhoneNumber", "(Landroid/app/Activity;Ljava/lang/String;)V", 
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(number));
#endif
}

void UAGApps::CallPhoneNumber(FString number)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGAppsClassName, "callPhoneNumber", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(number));
#endif
}
