// Copyright (c) 2019 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Texture2D.h"
#include "IGCameraFlashMode.h"
#include "IGGallerySourceType.h"
#include "IGImagePickerBPL.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnImagePickedDelegate, UTexture2D*, texture);
DECLARE_DYNAMIC_DELEGATE(FOnCancelPickDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnImageSavedDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnSaveErrorDelegate);

/**
 * Class for image saving and picking from gallery.
 */
UCLASS()
class IOSGOODIES_API UIGImagePicker : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
    /**
    * Pick photo from camera
    * @param allowEditing - flag indicating whether it is allowed to edit photo
    * @param useRearCamera - flag indicating whether to use device rear camera
    * @param flashMode - camera flash mode
    * @param onPickPhotoFromCameraCallback - callback function that is called after user picked photo from camera
    * @param onCancelCallback - callback function that is called after user cancelled photo picking
    * @param maxSize - maximum dimension size of the resulting image. Provide -1 for original size.
    */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onPickPhotoFromCameraCallback, onCancelCallback"))
	static void PickPhotoFromCamera(bool allowEditing, bool useRearCamera, CameraFlashMode flashMode,
        const FOnImagePickedDelegate &onPickPhotoFromCameraCallback, const FOnCancelPickDelegate &onCancelCallback, int maxSize = -1);
	
    /**
    * Pick image from gallery
    * @param sourceType - source from which image should be picked
    * @param allowEditing - flag indicating whether it is allowed to edit image
    * @param posX - X position of the arrow on iPad screen. Positioning zero is at left side of the screen
    * @param posY - Y position of the arrow on iPad screen. Positioning zero is at top of the screen
    * @param onPickImageFromGalleryCallback - callback function that is called after user picked image from gallery
    * @param onCancelCallback - callback function that is called after user cancelled image picking
    * @param maxSize - maximum dimension size of the resulting image. Provide -1 for original size.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onPickImageFromGalleryCallback, onCancelCallback"))
    static void PickImageFromGallery(GallerySourceType sourceType, bool allowEditing, int posX, int posY,
        const FOnImagePickedDelegate& onPickImageFromGalleryCallback, const FOnCancelPickDelegate& onCancelCallback, int maxSize = -1);
    
    /**
    * Save image to gallery
    * @param image - image that should be saved in gallery
    * @param onImageSavedCallback - callback function that is called after image saved to gallery
    * @param onSaveErrorCallback - callback function that is called if saving image to gallery resulted with an error
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onImageSavedCallback, onSaveErrorCallback"))
    static void SaveImageToGallery(UTexture2D* texture,
        const FOnImageSavedDelegate& onImageSavedCallback, const FOnSaveErrorDelegate& onSaveErrorCallback);
    
    /**
    * Delete image from gallery
    * @param sourceType - source from which image should be picked
    * @param posX - X position of the arrow on iPad screen. Positioning zero is at left side of the screen
    * @param posY - Y position of the arrow on iPad screen. Positioning zero is at top of the screen
    * @param onSuccessCallback - callback function that is called after user picked image from gallery
    * @param onCancelCallback - callback function that is called after user cancelled image picking
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onCancelCallback"))
    static void DeleteImageFromGallery(GallerySourceType sourceType, int posX, int posY,
        const FOnImageSavedDelegate& onSuccessCallback, const FOnSaveErrorDelegate& onCancelCallback);
    
    /**
    * Take screen shot of game view
    * @param onScreenShotTakenCallback - callback function that is called after screen shot was taken
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static void TakeScreenShot(const FOnImagePickedDelegate& onScreenShotTakenCallback);
    
private:
	
	static FOnImagePickedDelegate OnImagePickedDelegate;
    static FOnCancelPickDelegate OnCancelPickDelegate;
    static FOnImageSavedDelegate OnImageSavedDelegate;
    static FOnSaveErrorDelegate OnSaveErrorDelegate;
};
