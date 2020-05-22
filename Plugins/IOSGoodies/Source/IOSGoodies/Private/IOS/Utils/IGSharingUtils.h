// Copyright (c) 2018 Nineva Studios

#pragma once

#import <Foundation/Foundation.h>

#import "IGShareBPL.h"

#import "IOS/Delegates/IGMessageDelegate.h"
#import "IOS/Delegates/IGMailDelegate.h"

class IGSharingUtils
{
public:

	static void PresentShareViewWithItems(NSArray* array, int posX, int posY,
		const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback);

	static IGMessageDelegate* CreateMessageDelegate(const FOnShareSuccessDelegate &onSuccessCallback,
		const FOnShareErrorDelegate &onErrorCallback, const FOnShareCancelDelegate &onCancelCallback);

	static IGMailDelegate* CreateMailDelegate(const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback,
		const FOnShareCancelDelegate &onCancelCallback, const FOnSavedDraftDelegate &onSavedDraftCallback);
};
