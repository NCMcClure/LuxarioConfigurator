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

void PostToInstagram(const FString& Message, const FString& FilePath);
FString GetStorageFilePath(const FString& FileName);
bool IsInstagramInstalled();

@interface InstagramShare : NSObject
{
    NSURL* url;
}

@property (nonatomic, retain) NSURL* url;

+(InstagramShare*)sharedInstance;

-(void)handshake;
-(void)postToInstagram:(NSString*)message WithImage : (NSString*)imagePath;
@end

#endif

#endif /* InstagramShare_h */
