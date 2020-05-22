// Copyright (c) 2020 Nineva Studios

#include "IGIOSViewController.h"

static bool isbh = true;
static int csbs = 0;

NS_ASSUME_NONNULL_BEGIN

@implementation IOSViewController(StatusBar)

-(void)statusBarIsHidden:(bool)isHidden
{
    isbh = isHidden;
}

-(void)statusBarCurrentStyle:(int)statusBarStyle
{
    csbs = statusBarStyle;
}

- (BOOL)prefersStatusBarHidden
{
    return isbh;
}

- (UIStatusBarStyle)preferredStatusBarStyle
{
    return (UIStatusBarStyle) csbs;
}

@end

NS_ASSUME_NONNULL_END
