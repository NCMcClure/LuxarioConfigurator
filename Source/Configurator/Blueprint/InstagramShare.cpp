//
//  InstagramShare.m
//  Configurator
//
//  Created by user922247 on 6/25/20.
//  Copyright © 2020 Epic Games, Inc. All rights reserved.
//

#if PLATFORM_IOS
#import <Foundation/Foundation.h>

#import "InstagramShare.h"


@implementation InstagramSharing
+ (id) sharedData
    {
        static InstagramSharing *singletonInstance = nil;
        static dispatch_once_t onceToken;

        dispatch_once(&onceToken, ^{
            if(!singletonInstance) {
                singletonInstance = [[InstagramSharing alloc] init];
            }
        });

        return singletonInstance;
    }

-(NSString*) getFilePath:(NSString *)fileName{
        //    NSString *searchFilename = @"hello.pdf"; // name of the PDF you are searching for

        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        NSDirectoryEnumerator *direnum = [[NSFileManager defaultManager] enumeratorAtPath:documentsDirectory];

        NSString *documentsSubpath;
        while (documentsSubpath = [direnum nextObject])
        {
            if (![documentsSubpath.lastPathComponent isEqual:fileName]) {
                continue;
            }

            NSLog(@"found %@", documentsSubpath);
        }
        return documentsSubpath;
    }

-(void)instaGramWallPost:(NSString *)imgPath inView:(UIView *)view
    {
        NSURL* myURL = [NSURL URLWithString : [NSString stringWithFormat : @"file://%@", imgPath] ];

        NSData * imageData = [[NSData alloc] initWithContentsOfURL:myURL];
        UIImage *imgShare = [[UIImage alloc] initWithData:imageData];

        NSURL *instagramURL = [NSURL URLWithString:@"instagram://app"];

        if([[UIApplication sharedApplication] canOpenURL:instagramURL]) //check for App is install or not
        {
            UIImage *imageToUse = imgShare;
            NSString *documentDirectory=[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
            NSString *saveImagePath=[documentDirectory stringByAppendingPathComponent:@"Image.igo"];
            imageData=UIImagePNGRepresentation(imageToUse);
            [imageData writeToFile:saveImagePath atomically:YES];
            NSURL *imageURL=[NSURL fileURLWithPath:saveImagePath];

            NSString *path = saveImagePath;
            NSURL *url = [NSURL fileURLWithPath:path];

            self.documentController=[[UIDocumentInteractionController alloc]init];
            self.documentController = [UIDocumentInteractionController interactionControllerWithURL:imageURL];
            self.documentController.delegate = self;
            self.documentController.annotation = [NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:@"Testing"], @"InstagramCaption", nil];
            self.documentController.UTI = @"com.instagram.exclusivegram";
            [self.documentController presentOpenInMenuFromRect:CGRectMake(1, 1, 1, 1) inView:view animated:YES];
        }
        else {
            //            DisplayAlertWithTitle(@"Instagram not found", @"")
            NSLog(@"no image found");
        }
    }



@end

#endif
