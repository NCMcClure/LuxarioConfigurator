//
//  InstagramShare.h
//  Configurator
//
//  Created by user922247 on 6/25/20.
//  Copyright © 2020 Epic Games, Inc. All rights reserved.
//

#ifndef InstagramShare_h
#define InstagramShare_h

#if PLATFORM_IOS
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Foundation/Foundation.h>

void IosDicInitialise();
void PostToInstagram(const char*, const char*);

@interface InstagramShare : NSObject <UIDocumentInteractionControllerDelegate>
{
	UIWindow* nativeWindow;
}

@property(nonatomic, retain) UIDocumentInteractionController* dic;

+(InstagramShare*)sharedInstance;

-(void)handshake;
-(void)postToInstagram:(NSString*)message WithImage : (NSString*)imagePath;

@end
#endif

#endif /* InstagramShare_h */
