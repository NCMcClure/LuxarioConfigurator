// Copyright (c) 2019 Nineva Studios

#include "IGImagePickerBPL.h"
#include "Runtime/Core/Public/Async/Async.h"

#if PLATFORM_IOS
#include "Delegates/IGImagePickerDelegate.h"
#include "Other/IGSelectorsContainer.h"
#include "Utils/IGMediaUtils.h"
#include "Utils/IGImagePickerUtils.h"
#import <Foundation/Foundation.h>
#import <Photos/Photos.h>
#endif

FOnCancelPickDelegate UIGImagePicker::OnCancelPickDelegate;
FOnImagePickedDelegate UIGImagePicker::OnImagePickedDelegate;
FOnImageSavedDelegate UIGImagePicker::OnImageSavedDelegate;
FOnSaveErrorDelegate UIGImagePicker::OnSaveErrorDelegate;

UIGImagePicker::UIGImagePicker(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UIGImagePicker::PickPhotoFromCamera(bool allowEditing, bool useRearCamera, CameraFlashMode flashMode,
    const FOnImagePickedDelegate &onPickPhotoFromCameraCallback, const FOnCancelPickDelegate &onCancelCallback, int maxSize)
{
    OnImagePickedDelegate = onPickPhotoFromCameraCallback;
    OnCancelPickDelegate = onCancelCallback;
    
#if PLATFORM_IOS
    __block int maxSizeBlock = maxSize;
    dispatch_async(dispatch_get_main_queue(), ^ {
		if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
			UIImagePickerController *pickerView = [[UIImagePickerController alloc] init];
							   
			pickerView.sourceType = UIImagePickerControllerSourceTypeCamera;
            pickerView.allowsEditing = allowEditing;
			pickerView.cameraDevice = useRearCamera ? UIImagePickerControllerCameraDeviceRear : UIImagePickerControllerCameraDeviceFront;
			pickerView.cameraFlashMode = (UIImagePickerControllerCameraFlashMode) ((int)flashMode);

			IGImagePickerDelegate* imagePickerDelegate = [[IGImagePickerDelegate alloc] init];
            imagePickerDelegate.imagePicked = ^(NSDictionary<NSString *, id> *info) {
                [pickerView dismissViewControllerAnimated:NO completion:nil];
                UIImage *img = IGImagePickerUtils::GetNormalizedImageFromData(info, maxSizeBlock);
                UTexture2D* texture = IGMediaUtils::ConvertImageToTexture(img);
                AsyncTask(ENamedThreads::GameThread, [=]() {
                    OnImagePickedDelegate.ExecuteIfBound(texture);
                });
            };
			imagePickerDelegate.imagePickCancelled = ^() {
				[pickerView dismissViewControllerAnimated:YES completion:nil];
                AsyncTask(ENamedThreads::GameThread, [=]() {
                    OnCancelPickDelegate.ExecuteIfBound();
                });
			};
			pickerView.delegate = imagePickerDelegate;
			[[IOSAppDelegate GetDelegate].IOSController presentViewController:pickerView animated:YES completion:nil];
		} else {
			NSLog(@"Picking image from camera not available on current device");
		}
	});
#endif
}

void UIGImagePicker::PickImageFromGallery(GallerySourceType sourceType, bool allowEditing, int posX, int posY,
    const FOnImagePickedDelegate& onPickImageFromGalleryCallback, const FOnCancelPickDelegate& onCancelCallback, int maxSize)
{
    OnImagePickedDelegate = onPickImageFromGalleryCallback;
    OnCancelPickDelegate = onCancelCallback;
    
#if PLATFORM_IOS
    __block int maxSizeBlock = maxSize;
    IGImagePickerUtils::PickImage(sourceType, allowEditing, posX, posY, ^(NSDictionary<NSString *, id> *info) {
        UIImage *img = IGImagePickerUtils::GetNormalizedImageFromData(info, maxSizeBlock);
        UTexture2D* texture = IGMediaUtils::ConvertImageToTexture(img);
        AsyncTask(ENamedThreads::GameThread, [=]() {
            OnImagePickedDelegate.ExecuteIfBound(texture);
        });
    }, ^{
        AsyncTask(ENamedThreads::GameThread, [=]() {
            OnCancelPickDelegate.ExecuteIfBound();
        });
    });
#endif
}

void UIGImagePicker::DeleteImageFromGallery(GallerySourceType sourceType, int posX, int posY,
        const FOnImageSavedDelegate& onSuccessCallback, const FOnSaveErrorDelegate& onCancelCallback)
{
    OnImageSavedDelegate = onSuccessCallback;
    OnSaveErrorDelegate = onCancelCallback;
    
#if PLATFORM_IOS
    IGImagePickerUtils::PickImage(sourceType, false, posX, posY, ^(NSDictionary<NSString *, id> *info) {
        PHAuthorizationStatus authStatus = [PHPhotoLibrary authorizationStatus];
        if (authStatus == PHAuthorizationStatusAuthorized)
        {
            IGImagePickerUtils::DeleteAsset(info, ^{
                AsyncTask(ENamedThreads::GameThread, [=]() {
                    OnImageSavedDelegate.ExecuteIfBound();
                });
            }, ^{
                AsyncTask(ENamedThreads::GameThread, [=]() {
                    OnSaveErrorDelegate.ExecuteIfBound();
                });
            });
        } else {
            [PHPhotoLibrary requestAuthorization:^(PHAuthorizationStatus status) {
                if (status == PHAuthorizationStatusAuthorized) {
                    IGImagePickerUtils::DeleteAsset(info, ^{
                        AsyncTask(ENamedThreads::GameThread, [=]() {
                            OnImageSavedDelegate.ExecuteIfBound();
                        });
                    }, ^{
                        AsyncTask(ENamedThreads::GameThread, [=]() {
                            OnSaveErrorDelegate.ExecuteIfBound();
                        });
                    });
                } else {
                    AsyncTask(ENamedThreads::GameThread, [=]() {
                        OnSaveErrorDelegate.ExecuteIfBound();
                    });
                }
            }];
        }
    }, ^{
        AsyncTask(ENamedThreads::GameThread, [=]() {
            OnSaveErrorDelegate.ExecuteIfBound();
        });
    });
#endif
}


void UIGImagePicker::SaveImageToGallery(UTexture2D* texture,
    const FOnImageSavedDelegate& onImageSavedCallback, const FOnSaveErrorDelegate& onSaveErrorCallback)
{
    OnImageSavedDelegate = onImageSavedCallback;
    OnSaveErrorDelegate = onSaveErrorCallback;
    
#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^ {
        UIImage *image = IGMediaUtils::ConvertTextureToImage(texture);;
        IGSelectorsContainer *selectorsContainer = [IGSelectorsContainer new];
        selectorsContainer.onImageSaved = ^{
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnImageSavedDelegate.ExecuteIfBound();
            });
        };
        selectorsContainer.onError = ^{
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnSaveErrorDelegate.ExecuteIfBound();
            });
        };
        
        UIImageWriteToSavedPhotosAlbum(image, selectorsContainer, @selector(thisImage:hasBeenSavedInPhotoAlbumWithError:usingContextInfo:), nil);
    });
#endif
}

void UIGImagePicker::TakeScreenShot(const FOnImagePickedDelegate& onScreenShotTakenCallback) {
    OnImagePickedDelegate = onScreenShotTakenCallback;
#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^{
        UIGraphicsBeginImageContextWithOptions([IOSAppDelegate GetDelegate].RootView.bounds.size, NO, 2.0f);
        [[IOSAppDelegate GetDelegate].RootView
         drawViewHierarchyInRect:[IOSAppDelegate GetDelegate].RootView.bounds
         afterScreenUpdates:YES];
    
        UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
        UTexture2D* texture = IGMediaUtils::ConvertImageToTexture(image);
        AsyncTask(ENamedThreads::GameThread, [=]() {
            OnImagePickedDelegate.ExecuteIfBound(texture);
        });
        UIGraphicsEndImageContext();
    });
#endif
}
