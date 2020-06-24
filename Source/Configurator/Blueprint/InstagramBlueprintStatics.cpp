// Fill out your copyright notice in the Description page of Project Settings.

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "InstagramBlueprintStatics.h"
#include "Configurator/Utils/StbImageWrite.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

#if PLATFORM_IOS
#import <Foundation/Foundation.h>
#endif

#include "Engine/Texture2D.h"

void UInstagramBlueprintStatics::ShareToInstagram(class UTexture2D* Texture)
{
	if (!Texture || !IsValid(Texture))
	{
		UE_LOG(LogTemp, Warning, TEXT("UInstagramBlueprintStatics::ShareToInstagram: Invalid texture."));
		return;
	}

	FString TexturePath = TEXT("InstaOut.png");
	
#if PLATFORM_ANDROID
	extern FString GExternalFilePath;
	TexturePath = FPaths::Combine(GExternalFilePath, TexturePath);
#endif

#if PLATFORM_IOS
	TexturePath = TEXT("InstaOut.ig");
#endif

	const int32 Width = Texture->GetSizeX();
	const int32 Height = Texture->GetSizeY();

	if (const FColor* FormatedImageData = reinterpret_cast<const FColor*>(Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY)))
	{
		TArray<FColor> Pixels;
		Pixels.SetNumZeroed(Width * Height);

		if (uint8* OrderedPixelData = (uint8*)FMemory::Malloc(Width * Height * 4))
		{
			for (int32 X = 0; X < Width; X++)
			{
				for (int32 Y = 0; Y < Height; Y++)
				{
					int index = Y * Width + X;
					Pixels[index] = FormatedImageData[index];

					OrderedPixelData[4 * index + 0] = Pixels[index].R;
					OrderedPixelData[4 * index + 1] = Pixels[index].G;
					OrderedPixelData[4 * index + 2] = Pixels[index].B;
					OrderedPixelData[4 * index + 3] = Pixels[index].A;
				}
			}

			Texture->PlatformData->Mips[0].BulkData.Unlock();

			stbi_write_png(TCHAR_TO_UTF8(*TexturePath), Width, Height, 4, OrderedPixelData, 4 * Width);
			const FString Type = "image/*";

#if PLATFORM_ANDROID
			if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
			{
				jstring JavaPath = Env->NewStringUTF(TCHAR_TO_UTF8(TEXT("InstaOut.png")));
				jstring JavaType = Env->NewStringUTF(TCHAR_TO_UTF8(*Type));

				static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CreateInstagramIntent", "(Ljava/lang/String;Ljava/lang/String;)V", false);
				FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JavaType, JavaPath);
			}
#endif
#if PLATFORM_IOS
			NSURL* igImageHookFile = [NSURL URLWithString : [NSString stringWithFormat : @"file://%@", @"InstaOut.ig"] ];
			UIDocumentInteractionController* _dic = [UIDocumentInteractionController interactionControllerWithURL : igImageHookFile];
			_dic.UTI = @"com.instagram.exclusivegram";

			[_dic presentOpenInMenuFromRect : rect inView : self.view animated : YES] ;
#endif
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("UInstagramBlueprintStatics::ShareToInstagram: byteArray is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UInstagramBlueprintStatics::ShareToInstagram: FormatedImageData is null"));
	}
}

