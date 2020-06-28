#if PLATFORM_ANDROID

#include "InstagramShare.h"

#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"

FString GetStorageFilePath(const FString& FileName)
{
	extern FString GExternalFilePath;
	return FPaths::Combine(GExternalFilePath, FileName);
}

void PostToInstagram(const FString& Message, const FString& Path)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		const FString Type = "image/*";
		
		jstring JavaPath = Env->NewStringUTF(TCHAR_TO_UTF8(*Path));
		jstring JavaType = Env->NewStringUTF(TCHAR_TO_UTF8(*Type));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CreateInstagramIntent", "(Ljava/lang/String;Ljava/lang/String;)V", false);
		if (Method != 0)
		{
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JavaType, JavaPath);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("PostToInstagram: Couldn't find method AndroidThunkJava_CreateInstagramIntent!"));
		}
	}
}

#endif