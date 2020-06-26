//
//  InstagramShare.m
//  Configurator
//
//  Created by user922247 on 6/25/20.
//  Copyright © 2020 Epic Games, Inc. All rights reserved.
//

#if PLATFORM_IOS
#import "InstagramShare.h"

void IosDicInitialise()
{
	[[InstagramShare sharedInstance]handshake];
}

void PostToInstagram(const char* Message, const char* ImagePath)
{
	NSString* m = [NSString stringWithUTF8String : Message];
	NSString* i = [NSString stringWithUTF8String : ImagePath];
	[[InstagramShare sharedInstance]postToInstagram:m WithImage : i];
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

		// Post
		[UIImageJPEGRepresentation(image, 1.0) writeToFile:[self photoFilePath] atomically : YES] ;
		NSURL* fileURL = [NSURL fileURLWithPath : [self photoFilePath] ];

		self.dic = [UIDocumentInteractionController interactionControllerWithURL : fileURL];
		self.dic.UTI = @"com.instagram.exclusivegram";
		self.dic.delegate = self;
		if (message)
			self.dic.annotation = [NSDictionary dictionaryWithObject : message forKey : @"InstagramCaption"];

		[self.dic presentOpenInMenuFromRect : CGRectZero inView : nativeWindow.rootViewController.view animated : YES] ;
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
