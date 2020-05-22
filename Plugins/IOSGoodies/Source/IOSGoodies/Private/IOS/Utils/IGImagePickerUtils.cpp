// Copyright (c) 2019 Nineva Studios

#include "IGImagePickerUtils.h"

#import <Foundation/Foundation.h>
#import <Photos/Photos.h>

UIImage* IGImagePickerUtils::GetNormalizedImageFromData(NSDictionary<NSString *, id> *info, int maxSize) {
    UIImage *img = [info valueForKey:UIImagePickerControllerEditedImage];
    if (img == nil) {
        img = [info valueForKey:UIImagePickerControllerOriginalImage];
    }
    if (img.imageOrientation != UIImageOrientationUp) {
        CGSize newSize = ResizeImage(img.size, maxSize);
        UIGraphicsBeginImageContextWithOptions(newSize, NO, img.scale);
        [img drawInRect:(CGRect) {{0, 0}, newSize}];
        img = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
    }
    return img;
}

void IGImagePickerUtils::PickImage(GallerySourceType sourceType, bool allowEditing, int posX, int posY,
               ReceiveDictionaryDelegate onReceiveDelegate, VoidFunctionDelegate onCancelDelegate) {
    dispatch_async(dispatch_get_main_queue(), ^{
        UIImagePickerControllerSourceType pickerSourceType;
        switch (sourceType) {
            case GallerySourceType::PhotoLibrary:
                pickerSourceType = UIImagePickerControllerSourceTypePhotoLibrary;
                break;
            case GallerySourceType::PhotoAlbum:
                pickerSourceType = UIImagePickerControllerSourceTypeSavedPhotosAlbum;
                break;
            default:
                pickerSourceType = UIImagePickerControllerSourceTypePhotoLibrary;
                break;
        }
        
        if ([UIImagePickerController isSourceTypeAvailable:pickerSourceType])
        {
            IGImagePickerController *pickerView = [[IGImagePickerController alloc] init];
            pickerView.modalPresentationStyle = UIModalPresentationCurrentContext;
            pickerView.sourceType = pickerSourceType;
            pickerView.allowsEditing = allowEditing;
            pickerView.mediaTypes = @[@"public.image"];
            
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
            {
                pickerView.modalPresentationStyle = UIModalPresentationPopover;
                UIPopoverPresentationController *presentationController = [pickerView popoverPresentationController];
                presentationController.permittedArrowDirections = UIPopoverArrowDirectionAny;
                presentationController.sourceView = [IOSAppDelegate GetDelegate].RootView;
            }
            
            IGImagePickerDelegate* imagePickerDelegate = [[IGImagePickerDelegate alloc] init];
            imagePickerDelegate.imagePicked = ^(NSDictionary<NSString *, id> *info) {
                [pickerView dismissViewControllerAnimated:NO completion:nil];
                onReceiveDelegate(info);
            };
            imagePickerDelegate.imagePickCancelled = ^() {
                [pickerView dismissViewControllerAnimated:YES completion:nil];
                onCancelDelegate();
            };
            pickerView.delegate = imagePickerDelegate;
            
            IGCommonUtils::ConfigureControllerForIPad(pickerView, posX, posY);
            
            [[IOSAppDelegate GetDelegate].IOSController presentViewController:pickerView animated:YES completion:nil];
        } else {
            NSLog(@"Picking image from gallery not available on current device");
        }
    });
}

void IGImagePickerUtils::DeleteAsset(NSDictionary<NSString *, id> *info, VoidFunctionDelegate onSuccessDelegate, VoidFunctionDelegate onErrorDelegate) {
    PHAsset* asset = [info valueForKey:UIImagePickerControllerPHAsset];
    NSArray *arrDelete = [[NSArray alloc] initWithObjects:asset, nil];
    [[PHPhotoLibrary sharedPhotoLibrary] performChanges:^{
        BOOL req = [asset canPerformEditOperation:PHAssetEditOperationDelete];
        if (req) {
            [PHAssetChangeRequest deleteAssets:arrDelete];
        }
    } completionHandler:^(BOOL success, NSError *error) {
        if (success) {
            onSuccessDelegate();
        } else {
            onErrorDelegate();
        }
    }];
}

CGSize IGImagePickerUtils::ResizeImage(CGSize originalSize, int maxSize) {
    if (maxSize <= 0) {
        return originalSize;
    }
    CGFloat height = originalSize.height;
    CGFloat width = originalSize.width;
    
    bool shouldResize = width > maxSize || height > maxSize;
    if (!shouldResize) {
        return originalSize;
    }
    
    float decreaseRatio = fmax(height, width) / maxSize;
    CGSize newSize = CGSizeMake(height / decreaseRatio, width / decreaseRatio);
    NSLog(@"New Size: %f x %f", newSize.width, newSize.height);
    return newSize;
}
