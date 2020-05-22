// Copyright (c) 2019 Nineva Studios

#pragma once

#import <Foundation/Foundation.h>

@interface IGSelectorsContainer : NSObject

@property (nonatomic, copy) void (^onImageSaved)();

@property (nonatomic, copy) void (^onError)();

- (void)thisImage:(UIImage *)image hasBeenSavedInPhotoAlbumWithError:(NSError *)error usingContextInfo:(void*)ctxInfo;

@end
