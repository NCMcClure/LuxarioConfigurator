// Copyright (c) 2018 Nineva Studios

#pragma once

#import <Foundation/Foundation.h>
#import <MessageUI/MessageUI.h>

@interface IGMessageDelegate : NSObject <MFMessageComposeViewControllerDelegate>

@property(nonatomic, copy) void (^callbackSentSuccessfully)();

@property(nonatomic, copy) void (^callbackCancelled)();

@property(nonatomic, copy) void (^callbackFailed)();

@end
