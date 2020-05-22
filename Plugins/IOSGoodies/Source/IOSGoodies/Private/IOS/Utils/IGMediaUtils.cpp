// Copyright (c) 2018 Nineva Studios

#pragma once

#include "IGMediaUtils.h"

UIImage* IGMediaUtils::ConvertTextureToImage(UTexture2D *texture)
{
	int width = texture->GetSizeX();
	int height = texture->GetSizeY();

	const FColor* FormatedImageData = reinterpret_cast<const FColor*>(texture->PlatformData->Mips[0].BulkData.LockReadOnly());

	TArray<FColor> colorArray;
	colorArray.SetNumZeroed(width*height);

	int byteArrayLength = width*height*4;

	uint8* byteArray = (uint8*)malloc(byteArrayLength);

	for (int32 X = 0; X < width; X++)
	{
		for (int32 Y = 0; Y < height; Y++)
		{
			int index = Y * width + X;
			colorArray[index] = FormatedImageData[index];

			byteArray[4 * index + 0] = colorArray[index].R;
			byteArray[4 * index + 1] = colorArray[index].G;
			byteArray[4 * index + 2] = colorArray[index].B;
			byteArray[4 * index + 3] = colorArray[index].A;
		}
	}

	texture->PlatformData->Mips[0].BulkData.Unlock();

	const int numOfComponents = 4;
	const int bitsPerComponent = 8;
	const int bitsPerPixel = numOfComponents * bitsPerComponent;
	const int bytesPerRow = numOfComponents * width;

	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

	CFDataRef dataRef = CFDataCreate(kCFAllocatorDefault, byteArray, byteArrayLength);
	CGDataProviderRef dataProviderRef = CGDataProviderCreateWithCFData(dataRef);

	CGImageRef imageRef = CGImageCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpace,
						kCGBitmapByteOrderDefault | kCGImageAlphaLast,
						dataProviderRef, NULL, true, kCGRenderingIntentDefault);

	UIImage *image = [UIImage imageWithCGImage: imageRef];

	free(byteArray);

	return image;
}

UTexture2D* IGMediaUtils::ConvertImageToTexture(UIImage *image)
{
    const int width = (int) image.size.width * image.scale;
    const int height = (int) image.size.height * image.scale;
    
    const int bitsPerPixel = 32;
    const int bitsPerComponent = 8;
    const int bytesPerPixel = bitsPerPixel / bitsPerComponent;
    const int bytesPerRow = width * bytesPerPixel;
    
    const int bufferLength = bytesPerRow * height;
    
    uint8* bitmapData = (uint8*)malloc(bufferLength);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    
    CGContextRef context = CGBitmapContextCreate(bitmapData, width, height, bitsPerComponent, bytesPerRow, colorSpace,
        kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Little);

    CGImageRef imageRef = image.CGImage;
    
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), imageRef);
    
    UTexture2D* Texture = NewObject<UTexture2D>(GetTransientPackage(), NAME_None, RF_Transient);
    
    Texture->PlatformData = new FTexturePlatformData();
    Texture->PlatformData->SizeX = width;
    Texture->PlatformData->SizeY = height;
    Texture->PlatformData->PixelFormat = PF_B8G8R8A8;
    
    FTexture2DMipMap* Mip = new FTexture2DMipMap();
    Texture->PlatformData->Mips.Add(Mip);
    
    Mip->SizeX = width;
    Mip->SizeY = height;
    Mip->BulkData.Lock(LOCK_READ_WRITE);
    uint8* TextureData = (uint8 *) Mip->BulkData.Realloc(height * width * sizeof(uint8)*4);
    FMemory::Memcpy(TextureData, bitmapData, sizeof(uint8) * height * width * 4);
    Mip->BulkData.Unlock();
    
    Texture->AddToRoot();
    Texture->UpdateResource();
    
    CGContextRelease(context);
    
    free(bitmapData);
    
    return Texture;
}
