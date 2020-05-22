// Copyright (c) 2018 Nineva Studios

#include "IGCommonUtils.h"

void IGCommonUtils::OpenUrl(NSString *link)
{
	NSURL *url = [NSURL URLWithString:link];

	UIApplication *application = [UIApplication sharedApplication];
	dispatch_async(dispatch_get_main_queue(), ^{
		[application openURL:url options:@{} completionHandler:nil];
	});
}

UIViewController* IGCommonUtils::ConfigureControllerForIPad(UIViewController* controller, int posX, int posY)
{
	if ([controller respondsToSelector:@selector(popoverPresentationController)])
	{
		controller.popoverPresentationController.sourceView = [IOSAppDelegate GetDelegate].RootView;
		CGFloat scale = [[UIScreen mainScreen] scale];
		CGRect frame = CGRectMake(posX / scale, posY / scale, 0, 0);
		controller.popoverPresentationController.sourceRect = frame;
	}
	
	return controller;
}

