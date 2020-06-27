// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGImageSize.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGPickersBPL.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnImageReadyDelegate, UTexture2D*, texture);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnImageErrorDelegate, FString, error);

UCLASS()
class ANDROIDGOODIES_API UAGPickersBPL : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Pick image from gallery.
	* @param quality - quality of image to be picked (0 for minimum, 100 for maximum quality)
	* @param maxSize - size of the resulting image (pick smaller value to save memory)
	* @param shouldGenerateThumbnails - flag that indicates whether to generate thumbnails
	* @param onImagePickedCallback - callback function that is called when image picking completed successfully
	* @param onImagePickErrorCallback - callback function that is called when image picking from gallery resulted with an error
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void PickImageFromGallery(int quality, ImageSize maxSize, bool shouldGenerateThumbnails, 
		const FOnImageReadyDelegate& onImagePickedCallback, const FOnImageErrorDelegate& onImagePickErrorCallback);

	/**
	* Pick photo from camera.
	* @param shouldGenerateThumbnails - flag that indicates whether to generate thumbnails
	* @param onPhotoPickedCallback - callback function that is called when capturing image with camera completed successfully
	* @param onPhotoPickErrorCallback - callback function that is called when capturing image with camera resulted with an error
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void PickPhotoFromCamera(bool shouldGenerateThumbnails, const FOnImageReadyDelegate& onPhotoPickedCallback, const FOnImageErrorDelegate& onPhotoPickErrorCallback);

	/**
	* Save image to gallery.
	* @param image - image to be saved
	* @param fileName - name of the created file
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SaveImageToGallery(UTexture2D* image, FString fileName);

	/**
	* Take a screen shot of the game screen.
	* @param onScreenShotTakenCallback - callback function that is called when screen shot taking is completed successfully
	* @param onErrorCallback - callback function that is called when screen shot taking resulted with an error
	* @param showUI - whether to capture UI elements to a screen shot
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void TakeScreenShot(const FOnImageReadyDelegate& onScreenShotTakenCallback, const FOnImageErrorDelegate& onErrorCallback, bool showUI);

	// Callbacks interface methods to be called from Android
	static void OnImageReady(UTexture2D* texture);
	static void OnImageError(FString error);

private:

	static FOnImageReadyDelegate OnImageReadyDelegate;
	static FOnImageErrorDelegate OnImageErrorDelegate;	
};