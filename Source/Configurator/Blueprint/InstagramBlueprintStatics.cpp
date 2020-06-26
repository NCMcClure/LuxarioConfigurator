// Fill out your copyright notice in the Description page of Project Settings.

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "InstagramBlueprintStatics.h"
#include "Configurator/Utils/StbImageWrite.h"

#if PLATFORM_ANDROID
#include "Configurator/Utils/Android/InstagramShare.h"
#elif PLATFORM_IOS
#include "Configurator/Utils/iOS/InstagramShare.h"
#endif

#include "Engine/Texture2D.h"

void UInstagramBlueprintStatics::ShareToInstagram(class UTexture2D* Texture)
{
	if (!Texture || !IsValid(Texture))
	{
		UE_LOG(LogTemp, Warning, TEXT("UInstagramBlueprintStatics::ShareToInstagram: Invalid texture."));
		return;
	}

	FString TexturePath = TEXT("InstaOut.jpeg");
	
#if PLATFORM_ANDROID || PLATFORM_IOS
	TexturePath = GetStorageFilePath(TexturePath);
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
					const int32 index = Y * Width + X;
					Pixels[index] = FormatedImageData[index];

					OrderedPixelData[4 * index + 0] = Pixels[index].R;
					OrderedPixelData[4 * index + 1] = Pixels[index].G;
					OrderedPixelData[4 * index + 2] = Pixels[index].B;
					OrderedPixelData[4 * index + 3] = Pixels[index].A;
				}
			}

			Texture->PlatformData->Mips[0].BulkData.Unlock();

			stbi_write_jpg(TCHAR_TO_UTF8(*TexturePath), Width, Height, 4, OrderedPixelData, 100);
			const FString Type = "image/*";

#if PLATFORM_ANDROID || PLATFORM_IOS
			PostToInstagram("Checkout my new custom mold!", TexturePath);
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
