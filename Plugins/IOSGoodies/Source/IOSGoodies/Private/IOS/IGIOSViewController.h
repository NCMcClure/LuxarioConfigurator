// Copyright (c) 2020 Nineva Studios

#import <Foundation/Foundation.h>
#import "IOSView.h"

NS_ASSUME_NONNULL_BEGIN

@interface IOSViewController(StatusBar)

-(void)statusBarIsHidden:(bool)isHidden;
-(void)statusBarCurrentStyle:(int)statusBarStyle;

@end

NS_ASSUME_NONNULL_END

