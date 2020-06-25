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

@interface InstagramSharing : NSObject <UIDocumentInteractionControllerDelegate>
+ (InstagramSharing*)sharedData;

@property (nonatomic, retain) UIDocumentInteractionController *documentController;

-(void)instaGramWallPost:(NSString *)imgPath inView:(UIView *)view;

@end
#endif

#endif /* InstagramShare_h */
