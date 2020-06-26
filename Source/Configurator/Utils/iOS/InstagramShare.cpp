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
		// Image
		UIImage* image = [UIImage imageWithContentsOfFile : imagePath];
        
//////////////////////////////////////////////////
    __block PHAssetChangeRequest *_mChangeRequest = nil;
    __block PHObjectPlaceholder *placeholder;

    [[PHPhotoLibrary sharedPhotoLibrary] performChanges:^{
        _mChangeRequest = [PHAssetChangeRequest creationRequestForAssetFromImage:image];
        placeholder = _mChangeRequest.placeholderForCreatedAsset;
    } completionHandler:^(BOOL success, NSError *error) {
        if (success) {
            NSURL *instagramURL = [NSURL URLWithString:[NSString stringWithFormat:@"instagram://library?LocalIdentifier=\%@", [placeholder localIdentifier]]];

            if ([[UIApplication sharedApplication] canOpenURL:instagramURL]) {
                [[UIApplication sharedApplication] openURL:instagramURL options:@{} completionHandler:nil];
            } else {
                NSLog(@"Instagram is not installed");
            }
        }
        else {
            NSLog(@"error saving in camera roll : %@",error);
			        }
    }];
        
        return;
///////////////////////////////////////////////////////
		// Post
		[UIImageJPEGRepresentation(image, 1.0) writeToFile:[self photoFilePath] atomically : YES] ;
		NSURL* fileURL = [NSURL fileURLWithPath : [self photoFilePath] ];

		self.dic = [UIDocumentInteractionController interactionControllerWithURL : fileURL];
		self.dic.UTI = @"com.instagram.photo";
		self.dic.delegate = self;
		if (message)
			self.dic.annotation = [NSDictionary dictionaryWithObject : message forKey : @"InstagramCaption"];

		dispatch_async(dispatch_get_main_queue(), ^ {
			[self.dic presentOpenInMenuFromRect : CGRectZero inView : nativeWindow.rootViewController.view animated : YES] ;
		});
	}
	else
	{
		NSLog(@"Instagram not installed!");
	}
}

-(NSString*)photoFilePath
{
	return[NSString stringWithFormat : @"%@/%@", [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"], @"tempinstgramphoto.ig"];
}

-(UIDocumentInteractionController*)setupControllerWithURL:(NSURL*)fileURL usingDelegate : (id<UIDocumentInteractionControllerDelegate>)interactionDelegate
{
	UIDocumentInteractionController* interactionController = [UIDocumentInteractionController interactionControllerWithURL : fileURL];
	interactionController.delegate = interactionDelegate;
	return interactionController;
}

@end
#endif
