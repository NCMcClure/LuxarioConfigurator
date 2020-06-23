// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfiguratorCheatManager.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

void UConfiguratorCheatManager::ConfiguratorShareSampleToInstagram()
{
	const FString Path = "/storage/self/primary/UE4Game/Configurator/Configurator/Content/Non-Assets/Remi.jpg";
	const FString Type = "image/*";
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		UE_LOG(LogTemp, Log, TEXT("UConfiguratorCheatManager::ConfiguratorShareSampleToInstagram: Running share sample to instagram on android."));
		// First step, we convert the FString (UE4) parameter to a JNI parameter that will hold a String
		jstring JavaPath = Env->NewStringUTF(TCHAR_TO_UTF8(*Path));
		jstring JavaType = Env->NewStringUTF(TCHAR_TO_UTF8(*Type));
		// Then we call the method, we the Java String parameter
		// 
		{
			//(Ljava/lang/String;)
			static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_HelloToast", "()V", false);
			UE_LOG(LogTemp, Log, TEXT("UConfiguratorCheatManager::ConfiguratorShareSampleToInstagram: AndroidThunkJava_CreateInstagramIntent. Method id: %d"), (int32)Method);
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
			UE_LOG(LogTemp, Log, TEXT("UConfiguratorCheatManager::ConfiguratorShareSampleToInstagram: Hello"));
		}

		return;
        static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CreateInstagramIntent", "(Ljava/lang/String; Ljava/lang/String)V", false);
		UE_LOG(LogTemp, Log, TEXT("UConfiguratorCheatManager::ConfiguratorShareSampleToInstagram: AndroidThunkJava_CreateInstagramIntent. Method id: %d"), (int32)Method);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JavaPath, JavaType);
	}
#endif
}