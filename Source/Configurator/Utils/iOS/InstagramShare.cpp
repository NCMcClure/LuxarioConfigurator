//
//  InstagramShare.m
//  Configurator
//
//  Created by user922247 on 6/25/20.
//  Copyright © 2020 Epic Games, Inc. All rights reserved.
//

#if PLATFORM_IOS
#import "InstagramShare.h"
#import <Photos/Photos.h>


FString GetStorageFilePath(const FString& FileName)
{
    NSString* NsFileName = [NSString stringWithUTF8String : TCHAR_TO_ANSI(*FileName)];
    NSArray* DomainDirectories = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString* DocumentsPath = [DomainDirectories firstObject];
    NSString* OutputPath = [NSString stringWithFormat : @"%@/%@", DocumentsPath, NsFileName];
    return FString(OutputPath);
}

bool IsInstagramInstalled()
{
    NSURL* InstaUrl = [NSURL URLWithString : @"instagram://app"];

    if ([[UIApplication sharedApplication]canOpenURL:InstaUrl])
    {
        return true;
    }
    
    return false;
}

void PostToInstagram(const FString& Message, const FString& FilePath)
{
    NSString* NsMessage = [NSString stringWithUTF8String : TCHAR_TO_ANSI(*Message)];
    NSString* NsFilePath = [NSString stringWithUTF8String : TCHAR_TO_ANSI(*FilePath)];

    static bool bIosDicInitialised = false;
    if (!bIosDicInitialised)
    {
        IosDicInitialise();
        bIosDicInitialised = true;
    }

    [[InstagramShare sharedInstance]postToInstagram:NsMessage WithImage : NsFilePath];
}

@implementation InstagramShare

@synthesize url;

static InstagramShare* sharedInstance = nil;
+(InstagramShare*)sharedInstance {
    if (!sharedInstance)
        sharedInstance = [[InstagramShare alloc]init];

    return sharedInstance;
}

-(id)init
{
    if (self = [super init])
    {
        url = nil;
    }

    return self;
}

-(void)postToInstagram:(NSString*)message WithImage : (NSString*)imagePath;
{
    static PHAssetChangeRequest* ChangeRequest = nil;
    static PHObjectPlaceholder* Placeholder = nil;
    static NSURL* InstagramURL = nil;

    void (^Post)() = ^() {
        NSURL* appURL = [NSURL URLWithString : @"instagram://app"];
        if ([[UIApplication sharedApplication]canOpenURL:appURL] )
        {
            UIImage* image = [UIImage imageWithContentsOfFile : imagePath];

            [[PHPhotoLibrary sharedPhotoLibrary] performChanges:^{
                ChangeRequest = [PHAssetChangeRequest creationRequestForAssetFromImage:image];
                if (ChangeRequest != nil)
                {
                    Placeholder = [ChangeRequest placeholderForCreatedAsset];
                    MyManager *sharedManager = [MyManager sharedManager];
                    sharedManager.url = [NSURL URLWithString : [NSString stringWithFormat : @"instagram://library?LocalIdentifier=\%@", [[Placeholder localIdentifier] substringToIndex:36]]];
                    NSLog(@"Configurator: Placeholder -> %@", Placeholder);
                    NSLog(@"Configurator: Share URL -> %@", sharedManager.url);
                }
                else
                {
                    NSLog(@"Configurator: Change request is null");
                }
            } completionHandler:^(BOOL success, NSError *error) {
                if (success) {
                    dispatch_async(dispatch_get_main_queue(), ^ {
                        MyManager *sharedManager = [MyManager sharedManager];
                        NSLog(@"Configurator: Opening url -> %@", sharedManager.url);
                        if ([[UIApplication sharedApplication] canOpenURL:sharedManager.url]) {
                            [[UIApplication sharedApplication] openURL:sharedManager.url options:@{} completionHandler:nil];
                        } else {
                            NSLog(@"Instagram is not installed");
                        }
                    });
                }
                else {
                    NSLog(@"error saving in camera roll : %@",error);
                }
            }];
        }
        else
        {
            NSLog(@"Instagram not installed!");
        }
    };
    PHAuthorizationStatus authStatus = [PHPhotoLibrary authorizationStatus];
    if (authStatus == PHAuthorizationStatusAuthorized)
    {
        NSLog(@"Configurator: Permissions already granted");
        Post();
    }
    else
    {
        NSLog(@"Configurator: Asking for permissions");
        [PHPhotoLibrary requestAuthorization:^(PHAuthorizationStatus status) {
            if (status == PHAuthorizationStatusAuthorized)
            {
                NSLog(@"Configurator: Permissions granted!");
                Post();
            }
            else
            {
                NSLog(@"Configurator: Permission denied, cannot post");
            }
        }];
    }

}

@end
#endif
