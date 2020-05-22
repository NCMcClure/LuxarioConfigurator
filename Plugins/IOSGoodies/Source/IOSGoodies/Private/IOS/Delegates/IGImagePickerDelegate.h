// Copyright (c) 2019 Nineva Studios

#pragma once

#import <Foundation/Foundation.h>

@interface IGImagePickerDelegate : NSObject <UIImagePickerControllerDelegate, UINavigationControllerDelegate> {
}

@property (nonatomic, copy) void (^imagePicked)(NSDictionary<NSString *, id> *info);

@property (nonatomic, copy) void (^imagePickCancelled)();

@end
