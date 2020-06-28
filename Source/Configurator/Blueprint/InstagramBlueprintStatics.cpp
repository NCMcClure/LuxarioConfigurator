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
#include "ImageUtils.h"

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

	TArray<FColor> Pixels = GetTextureColorData(Texture);

	if (uint8* OrderedPixelData = (uint8*)FMemory::Malloc(Width * Height * 4))
	{
		int32 Index = 0;
		for (const FColor& Pixel : Pixels)
		{
			OrderedPixelData[4 * Index + 0] = Pixel.R;
			OrderedPixelData[4 * Index + 1] = Pixel.G;
			OrderedPixelData[4 * Index + 2] = Pixel.B;
			OrderedPixelData[4 * Index + 3] = Pixel.A;
			Index++;
		}

		stbi_write_jpg(TCHAR_TO_UTF8(*TexturePath), Width, Height, 4, OrderedPixelData, 100);
		delete OrderedPixelData;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UInstagramBlueprintStatics::ShareToInstagram: byteArray is null"));
	}


#if PLATFORM_ANDROID || PLATFORM_IOS
	PostToInstagram("Checkout my new custom mold!", TexturePath);
#endif

}

class UTexture2D* UInstagramBlueprintStatics::CropTexture(class UTexture2D* Texture, const int32 Width, const int32 Height, int32 OffsetX, int32 OffsetY)
{
	if (!Texture)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInstagramBlueprintStatics::CropTexture: Texture is null!"));
		return nullptr;
	}

	const int32 MaxOffsetX = Texture->GetSizeX() - Width;
	const int32 MaxOffsetY = Texture->GetSizeY() - Height;

	UE_CLOG(OffsetX > MaxOffsetX || OffsetY > MaxOffsetY, LogTemp, Warning, TEXT("UInstagramBlueprintStatics::CropTexture: Rounding output texture offset to match given Width and Height. Max values allowed: %dx%d Passed values: %dx%d"), MaxOffsetX, MaxOffsetY, OffsetX, OffsetY);
	
	OffsetX = FMath::Min(OffsetX, MaxOffsetX);
	OffsetY = FMath::Min(OffsetY, MaxOffsetY);

	UTexture2D* Out = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);

	FColor* MipData = reinterpret_cast<FColor*>(Out->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	const TArray<FColor> Pixels = GetTextureColorData(Texture);

	int32 Index = 0;
	for (int32 Y = OffsetY; Y < Height; Y++)
	{
		FMemory::Memcpy(&MipData[Y * Width], &Pixels[Y * Texture->GetSizeX() + OffsetX], Width * sizeof(FColor));
	}

	Out->PlatformData->Mips[0].BulkData.Unlock();

	Out->UpdateResource();

	return Out;
}

bool UInstagramBlueprintStatics::IsInstagramAvailable()
{
#if PLATFORM_ANDROID || PLATFORM_IOS
	return IsInstagramInstalled();
#endif
	return false;
}

TArray<FColor> UInstagramBlueprintStatics::GetTextureColorData(class UTexture2D* Texture)
{
	TArray<FColor> Pixels;

	if (!Texture)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInstagramBlueprintStatics::GetTextureColorData: Texture is null!"));
		return Pixels;
	}

	if (const FColor* ImageData = reinterpret_cast<const FColor*>(Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY)))
	{
		const int32 Width = Texture->GetSizeX();
		const int32 Height = Texture->GetSizeY();

		Pixels.SetNumZeroed(Width * Height);

		for (int32 X = 0; X < Width; X++)
		{
			for (int32 Y = 0; Y < Height; Y++)
			{
				const int32 Index = Y * Width + X;
				Pixels[Index] = ImageData[Index];
			}
		}

		Texture->PlatformData->Mips[0].BulkData.Unlock();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UInstagramBlueprintStatics::ShareToInstagram: ImageData is null"));
	}

	return Pixels;
}
