// Copyright (c) 2019 Nineva Studios

#pragma once

#import <Foundation/Foundation.h>

typedef void(^ReceiveDictionaryDelegate)(NSDictionary<NSString *, id> *info);
typedef void(^VoidFunctionDelegate)();

class IGImagePickerUtils
{
public:
    static UIImage* GetNormalizedImageFromData(NSDictionary<NSString *, id> *info, int maxSize);
    
    static void PickImage(GallerySourceType sourceType, bool allowEditing,
                          int posX, int posY,
                          ReceiveDictionaryDelegate onReceiveDelegate,
                          VoidFunctionDelegate onCancelDelegate);
    
    static void DeleteAsset(NSDictionary<NSString *, id> *info,
                            VoidFunctionDelegate onSuccessDelegate,
                            VoidFunctionDelegate onErrorDelegate);
    static CGSize ResizeImage(CGSize originalSize, int maxSize);
};
