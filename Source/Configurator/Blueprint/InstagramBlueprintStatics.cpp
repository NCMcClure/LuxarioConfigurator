// Fill out your copyright notice in the Description page of Project Settings.

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "InstagramBlueprintStatics.h"
#include "Configurator/Utils/StbImageWrite.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

#include "Engine/Texture2D.h"
#include "Serialization/BufferArchive.h"
#include "ImageUtils.h"
#include "Engine/Engine.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "UnrealClient.h"

void CopyTextureToArray(UTexture2D* Texture, TArray<FColor>& Array, uint32& Width, uint32& Height)
{
	struct FCopyBufferData {
		UTexture2D* Texture;
		TPromise<void> Promise;
		TArray<FLinearColor> DestLinearBuffer;
		TArray<FColor> DestBuffer;
	};
	using FCommandDataPtr = TSharedPtr<FCopyBufferData, ESPMode::ThreadSafe>;
	FCommandDataPtr CommandData = MakeShared<FCopyBufferData, ESPMode::ThreadSafe>();
	CommandData->Texture = Texture;

	auto Future = CommandData->Promise.GetFuture();

	Width = CommandData->Texture->GetSizeX();
	Height = CommandData->Texture->GetSizeY();

	ENQUEUE_RENDER_COMMAND(CopyTextureToArray)(
		[CommandData, Width, Height](FRHICommandListImmediate& RHICmdList)
		{
			check(IsInRenderingThread());

			RHICmdList.SetContext(RHIGetDefaultContext());

			auto Texture2DRHI = CommandData->Texture->Resource->TextureRHI->GetTexture2D();
			uint32 DestPitch{ 0 };

			FRHIResourceCreateInfo CreateInfo;
			
			FTexture2DRHIRef Texture2DRef = RHICmdList.CreateTexture2D(Width, Height, PF_R8G8B8A8, 1, 1, ETextureCreateFlags::TexCreate_CPUReadback, CreateInfo);

			RHICmdList.CopyToResolveTarget(CommandData->Texture->Resource->TextureRHI->GetTexture2D(), Texture2DRef, FResolveParams());
			RHICmdList.ReadSurfaceData(Texture2DRHI, FIntRect(0, 0, Width, Height), CommandData->DestLinearBuffer, FReadSurfaceDataFlags());


			CommandData->Promise.SetValue();
		});


	Future.Get();

	CommandData->DestBuffer.Reserve(Width * Height);

	for (FLinearColor& Linear : CommandData->DestLinearBuffer)
	{
		CommandData->DestBuffer.Add(Linear.ToFColor(true));
	}

	Array = std::move(CommandData->DestBuffer);
}

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

	TArray<FColor> Out;
	UE_LOG(LogTemp, Log, TEXT("HELLOOOO, Exporting to %s"), *TexturePath);
	uint32 Width, Height;
	CopyTextureToArray(Texture, Out, Width, Height);
	stbi_write_png(TCHAR_TO_UTF8(*TexturePath), Width, Height, 4, Out.GetData(), Width * sizeof(FColor));
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
}

