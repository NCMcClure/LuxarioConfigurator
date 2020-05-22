// Copyright (c) 2018 Nineva Studios

#include "IGSharingUtils.h"
#include "IOS/IOSAppDelegate.h"
#include "Runtime/Core/Public/Async/Async.h"

void IGSharingUtils::PresentShareViewWithItems(NSArray *array, int posX, int posY,
	const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback)
{
    dispatch_async(dispatch_get_main_queue(), ^{
        UIActivityViewController *activityViewController = [[UIActivityViewController alloc] initWithActivityItems:array applicationActivities:nil];
        
        activityViewController = (UIActivityViewController*) IGCommonUtils::ConfigureControllerForIPad((UIViewController*) activityViewController, posX, posY);

        UIActivityViewController *weakController = activityViewController;
        
        [activityViewController setCompletionWithItemsHandler:^(UIActivityType activityType, BOOL completed, NSArray *returnedItems, NSError *activityError) {
            AsyncTask(ENamedThreads::GameThread, [=]() {
                if (!completed) {
                    onErrorCallback.ExecuteIfBound();
                } else {
                    onSuccessCallback.ExecuteIfBound();
                }
            });

            weakController.completionWithItemsHandler = nil;
        }];
    
        [[IOSAppDelegate GetDelegate].IOSController presentViewController:activityViewController animated:true completion:nil];
    });
}

IGMessageDelegate* IGSharingUtils::CreateMessageDelegate(const FOnShareSuccessDelegate &onSuccessCallback,
	const FOnShareErrorDelegate &onErrorCallback, const FOnShareCancelDelegate &onCancelCallback)
{
	IGMessageDelegate *MessageDelegate = [[IGMessageDelegate alloc] init];

	MessageDelegate.callbackSentSuccessfully = ^{
        AsyncTask(ENamedThreads::GameThread, [=]() {
            onSuccessCallback.ExecuteIfBound();
        });
	};
	MessageDelegate.callbackCancelled = ^{
        AsyncTask(ENamedThreads::GameThread, [=]() {
            onCancelCallback.ExecuteIfBound();
        });
	};
	MessageDelegate.callbackFailed = ^{
        AsyncTask(ENamedThreads::GameThread, [=]() {
            onErrorCallback.ExecuteIfBound();
        });
	};

	return MessageDelegate;
}

IGMailDelegate* IGSharingUtils::CreateMailDelegate(const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback,
	const FOnShareCancelDelegate &onCancelCallback, const FOnSavedDraftDelegate &onSavedDraftCallback)
{
	IGMailDelegate *MailDelegate = [[IGMailDelegate alloc] init];

	MailDelegate.callbackSentSuccessfully = ^{
        AsyncTask(ENamedThreads::GameThread, [=]() {
            onSuccessCallback.ExecuteIfBound();
        });
	};
	MailDelegate.callbackCancelled = ^{
        AsyncTask(ENamedThreads::GameThread, [=]() {
            onCancelCallback.ExecuteIfBound();
        });
	};
	MailDelegate.callbackFailed = ^{
        AsyncTask(ENamedThreads::GameThread, [=]() {
            onErrorCallback.ExecuteIfBound();
        });
	};
	MailDelegate.callbackSaved = ^{
        AsyncTask(ENamedThreads::GameThread, [=]() {
            onSavedDraftCallback.ExecuteIfBound();
        });
	};

	return MailDelegate;
}
