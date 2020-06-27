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

static NSString* PlaceholderIdentifier = nil;

FString GetStorageFilePath(const FString& FileName)
{
	NSString* NsFileName = [NSString stringWithUTF8String : TCHAR_TO_ANSI(*FileName)];
	NSArray* DomainDirectories = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString* DocumentsPath = [DomainDirectories firstObject];
	NSString* OutputPath = [NSString stringWithFormat : @"%@/%@", DocumentsPath, NsFileName];
	return FString(OutputPath);
}

void IosDicInitialise()
{
	[[InstagramShare sharedInstance]handshake];
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

@synthesize dic;

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
		nativeWindow = [UIApplication sharedApplication].keyWindow;
	}

	return self;
}

-(void)handshake
{
	NSLog(@"Handshake completed!");
}

-(void)postToInstagram:(NSString*)message WithImage : (NSString*)imagePath;
{
	NSURL* appURL = [NSURL URLWithString : @"instagram://app"];
	if ([[UIApplication sharedApplication]canOpenURL:appURL] )
	{
        dispatch_async(dispatch_get_main_queue(), ^ {
            UIImage* image = [UIImage imageWithContentsOfFile : imagePath];
            __block PHAssetChangeRequest* ChangeRequest = nil;
            __block PHObjectPlaceholder* Placeholder = nil;

            [[PHPhotoLibrary sharedPhotoLibrary] performChanges:^{
                ChangeRequest = [PHAssetChangeRequest creationRequestForAssetFromImage:image];
                if (ChangeRequest != nil)
                {
                    NSLog(@"Configurator: 3");
                    Placeholder = [ChangeRequest placeholderForCreatedAsset];
                    PlaceholderIdentifier = [Placeholder localIdentifier];
                }
                else
                {
                    NSLog(@"Configurator: Change request is null");
                }
            } completionHandler:^(BOOL success, NSError *error) {
                if (PlaceholderIdentifier == nil)
                {
                    NSLog(@"Configurator: placeholderIdentifier is nil.");
                    return;
                }
                if (success) {
                    NSURL* InstagramURL = [NSURL URLWithString : [NSString stringWithFormat : @"instagram://library?LocalIdentifier=\%@", PlaceholderIdentifier] ];
                    if ([[UIApplication sharedApplication] canOpenURL:InstagramURL]) {
                        [[UIApplication sharedApplication] openURL:InstagramURL options:@{} completionHandler:nil];
                    } else {
                        NSLog(@"Instagram is not installed");
                    }
                }
                else {
                    NSLog(@"error saving in camera roll : %@",error);
                }
            }];
        });
	}
	else
	{
		NSLog(@"Instagram not installed!");
	}
}	

@end
#endif
