// Copyright (c) 2018 Nineva Studios

#pragma once

#import <Foundation/Foundation.h>

class IGCommonUtils
{
public:

	static void OpenUrl(NSString *link);
	static UIViewController* ConfigureControllerForIPad(UIViewController* controller, int posX, int posY);
};
