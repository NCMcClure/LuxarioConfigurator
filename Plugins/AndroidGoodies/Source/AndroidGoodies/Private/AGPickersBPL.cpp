// Copyright (c) 2019 Nineva Studios

#include "AGPickersBPL.h"
#include "Async/Async.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/UnrealClient.h"
#include "AGScreenShotHelper.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMediaUtils.h"
#endif

FOnImageReadyDelegate UAGPickersBPL::OnImageReadyDelegate;
FOnImageErrorDelegate UAGPickersBPL::OnImageErrorDelegate;

#if PLATFORM_ANDROID
jbyteArray bufferRef = nullptr;
#endif

static const ANSICHAR* AGImagePickerClassName = "com/ninevastudios/androidgoodies/AGImagePicker";

UAGPickersBPL::UAGPickersBPL(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAGPickersBPL::PickImageFromGallery(int quality, ImageSize maxSize, bool shouldGenerateThumbnails, const FOnImageReadyDelegate& onImagePickedCallback, const FOnImageErrorDelegate& onImagePickErrorCallback)
{
	OnImageReadyDelegate = onImagePickedCallback;
	OnImageErrorDelegate = onImagePickErrorCallback;

#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGImagePickerClassName, "pickImage", "(Landroid/app/Activity;IIZ)V", FJavaWrapper::GameActivityThis, quality, (int) maxSize, shouldGenerateThumbnails);

#endif
}

void UAGPickersBPL::PickPhotoFromCamera(bool shouldGenerateThumbnails, const FOnImageReadyDelegate& onPhotoPickedCallback, const FOnImageErrorDelegate& onPhotoPickErrorCallback)
{
	OnImageReadyDelegate = onPhotoPickedCallback;
	OnImageErrorDelegate = onPhotoPickErrorCallback;

#if PLATFORM_ANDROID

	AGMethodCallUtils::CallStaticVoidMethod(AGImagePickerClassName, "takePhoto", "(Landroid/app/Activity;Z)V", FJavaWrapper::GameActivityThis, shouldGenerateThumbnails);

#endif
}

void UAGPickersBPL::SaveImageToGallery(UTexture2D* image, FString fileName)
{
#if PLATFORM_ANDROID

	int width = image->GetSizeX();
	int height = image->GetSizeY();

	TArray<uint8> byteArray = AGMediaUtils::ByteArrayFromTexture(image);
	jbyteArray jArray = AGArrayConvertor::ConvertToJByteArray(byteArray);

	AGMethodCallUtils::CallStaticVoidMethod(AGImagePickerClassName, "saveImageToGallery", "(Landroid/app/Activity;[BLjava/lang/String;II)V", FJavaWrapper::GameActivityThis, jArray, AGArrayConvertor::GetJavaString(fileName), width, height);

#endif
}

void UAGPickersBPL::TakeScreenShot(const FOnImageReadyDelegate& onScreenShotTakenCallback, const FOnImageErrorDelegate& onErrorCallback, bool showUI)
{
	OnImageReadyDelegate = onScreenShotTakenCallback;
	OnImageErrorDelegate = onErrorCallback;

#if PLATFORM_ANDROID

	if (!GEngine)
	{
		UAGPickersBPL::OnImageError("Default Engine was not found");
		return;
    }

	UGameViewportClient* GameViewport = GEngine->GameViewport;

	if (!GameViewport)
	{
		UAGPickersBPL::OnImageError("Default Game Viewport Client was not found");
		return;
	}

	UScreenShotHelper* Helper = NewObject<UScreenShotHelper>();
    
	GameViewport->OnScreenshotCaptured().AddUObject(Helper, &UScreenShotHelper::ProcessScreenShot);

	FScreenshotRequest::RequestScreenshot(showUI);

#endif
}

void UAGPickersBPL::OnImageReady(UTexture2D* texture)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnImageReadyDelegate.ExecuteIfBound(texture);
	});

#if PLATFORM_ANDROID
	if (bufferRef != nullptr)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		Env->DeleteGlobalRef(bufferRef);
		bufferRef = nullptr;
	}	
#endif
}

void UAGPickersBPL::OnImageError(FString error)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnImageErrorDelegate.ExecuteIfBound(error);
	});
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGImagePicker_onImageReceived(JNIEnv* env, jclass clazz, jbyteArray buffer, int width, int height)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => onImageReceived callback caught in C++!"));
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Image width: %d, height: %d"), width, height);
    
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	bufferRef = static_cast<jbyteArray>(Env->NewGlobalRef(buffer));

	AsyncTask(ENamedThreads::GameThread, [=]() {
		TArray<uint8> byteArray = AGArrayConvertor::ConvertToByteArray(bufferRef);
		UTexture2D* result = AGMediaUtils::TextureFromByteArray(byteArray, width, height);

		UAGPickersBPL::OnImageReady(result);
	});	
}

JNI_METHOD void Java_com_ninevastudios_androidgoodies_AGImagePicker_onImageReceiveError(JNIEnv* env, jclass clazz, jstring error)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => onImageReceiveError callback caught in C++!"));

	const char * UTFString = env->GetStringUTFChars(error, nullptr);
	FString result = UTF8_TO_TCHAR(UTFString);
	env->ReleaseStringUTFChars(error, UTFString);

	UAGPickersBPL::OnImageError(result);
}

#endif
