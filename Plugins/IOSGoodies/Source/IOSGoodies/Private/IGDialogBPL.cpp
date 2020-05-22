// Copyright (c) 2018 Nineva Studios

#include "IGDialogBPL.h"
#include "Runtime/Core/Public/Async/Async.h"

#if PLATFORM_IOS
#include "Utils/IGCommonUtils.h"
#include "IOS/IOSAppDelegate.h"
#import "IGIOSViewController.h"
#import <UIKit/UIKit.h>
#endif

FOnConfirmButtonClickedDelegate UIGDialogBPL::OnConfirmButtonClickedDelegate;
FOnCancelButtonClickedDelegate UIGDialogBPL::OnCancelButtonClickedDelegate;
FOnFirstOptionButtonClickedDelegate UIGDialogBPL::OnFirstOptionButtonClickedDelegate;
FOnSecondOptionButtonClickedDelegate UIGDialogBPL::OnSecondOptionButtonClickedDelegate;
FOnDestructiveButtonClickedDelegate UIGDialogBPL::OnDestructiveButtonClickedDelegate;
FOnActionButtonClickedDelegate UIGDialogBPL::OnActionButtonClickedDelegate;
FOnConfirmInputButtonClickedDelegate UIGDialogBPL::OnConfirmInputButtonClickedDelegate;

//StatusBarStyle UIGDialogBPL::CurrentBarStyle;
//bool UIGDialogBPL::IsHidden;

UIGDialogBPL::UIGDialogBPL(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}
#if PLATFORM_IOS
UIActivityIndicatorView *loadingDialog;
UIView *coverView;
#endif

void UIGDialogBPL::ShowSingleButtonDialog(FString title, FString message, FString confirmButtonText,
	const FOnConfirmButtonClickedDelegate &onConfirmButtonClickedCallback)
{
	OnConfirmButtonClickedDelegate = onConfirmButtonClickedCallback;

#if PLATFORM_IOS
	NSString *titleStr = title.GetNSString();
	NSString *messageStr = message.GetNSString();
	NSString *confirmButtonTextStr = confirmButtonText.GetNSString();

	dispatch_async(dispatch_get_main_queue(), ^
	{
		UIAlertController *singleButtonDialog = [UIAlertController
													alertControllerWithTitle:titleStr
													message:messageStr
													preferredStyle:UIAlertControllerStyleAlert];

		UIAlertAction *confirmAction = [UIAlertAction
										actionWithTitle:confirmButtonTextStr
										style:UIAlertActionStyleDefault
										handler: ^(UIAlertAction *action) {
                                            AsyncTask(ENamedThreads::GameThread, [=]() {
                                                OnConfirmButtonClickedDelegate.ExecuteIfBound();
                                            });
										}];

		[singleButtonDialog addAction:confirmAction];

		[[IOSAppDelegate GetDelegate].IOSController presentViewController:singleButtonDialog animated:true completion:nil];
	});
#endif
}


void UIGDialogBPL::ShowTwoButtonsDialog(FString title, FString message, FString confirmButtonText, FString cancelButtonText,
	const FOnConfirmButtonClickedDelegate &onConfirmButtonClickedCallback,
	const FOnCancelButtonClickedDelegate &onCancelButtonClickedCallback)
{
	OnConfirmButtonClickedDelegate = onConfirmButtonClickedCallback;
	OnCancelButtonClickedDelegate = onCancelButtonClickedCallback;

#if PLATFORM_IOS
	NSString *titleStr = title.GetNSString();
	NSString *messageStr = message.GetNSString();
	NSString *confirmButtonTextStr = confirmButtonText.GetNSString();
	NSString *cancelButtonTextStr = cancelButtonText.GetNSString();

	dispatch_async(dispatch_get_main_queue(), ^
	{
		UIAlertController *twoButtonsDialog = [UIAlertController
												alertControllerWithTitle:titleStr
												message:messageStr
												preferredStyle:UIAlertControllerStyleAlert];

		UIAlertAction *confirmAction = [UIAlertAction
										actionWithTitle:confirmButtonTextStr
										style:UIAlertActionStyleDefault
										handler: ^(UIAlertAction *action) {
                                            AsyncTask(ENamedThreads::GameThread, [=]() {
                                                OnConfirmButtonClickedDelegate.ExecuteIfBound();
                                            });
										}];

		UIAlertAction *cancelAction = [UIAlertAction
										actionWithTitle:cancelButtonTextStr
										style:UIAlertActionStyleDefault
										handler: ^(UIAlertAction *action) {
                                            AsyncTask(ENamedThreads::GameThread, [=]() {
                                                OnCancelButtonClickedDelegate.ExecuteIfBound();
                                            });
										}];

		[twoButtonsDialog addAction:confirmAction];
		[twoButtonsDialog addAction:cancelAction];

		[[IOSAppDelegate GetDelegate].IOSController presentViewController:twoButtonsDialog animated:true completion:nil];
	});
#endif
}

void UIGDialogBPL::ShowThreeButtonsDialog(FString title, FString message,
	FString firstOptionButtonText, FString secondOptionButtonText,
	FString cancelButtonText,
	const FOnFirstOptionButtonClickedDelegate &onFirstOptionButtonClickedCallback,
	const FOnSecondOptionButtonClickedDelegate &onSecondOptionButtonClickedCallback,
	const FOnCancelButtonClickedDelegate &onCancelButtonClickedCallback)
{
	OnFirstOptionButtonClickedDelegate = onFirstOptionButtonClickedCallback;
	OnSecondOptionButtonClickedDelegate = onSecondOptionButtonClickedCallback;
	OnCancelButtonClickedDelegate = onCancelButtonClickedCallback;

#if PLATFORM_IOS
	NSString *titleStr = title.GetNSString();
	NSString *messageStr = message.GetNSString();
	NSString *firstOptionButtonTextStr = firstOptionButtonText.GetNSString();
	NSString *secondOptionButtonTextStr = secondOptionButtonText.GetNSString();
	NSString *cancelButtonTextStr = cancelButtonText.GetNSString();

	dispatch_async(dispatch_get_main_queue(), ^
	{
		UIAlertController *threeButtonsDialog = [UIAlertController
												alertControllerWithTitle:titleStr
												message:messageStr
												preferredStyle:UIAlertControllerStyleAlert];

		UIAlertAction *firstOptionAction = [UIAlertAction
										   actionWithTitle:firstOptionButtonTextStr
										   style:UIAlertActionStyleDefault
										   handler: ^(UIAlertAction *action) {
                                               AsyncTask(ENamedThreads::GameThread, [=]() {
                                                   OnFirstOptionButtonClickedDelegate.ExecuteIfBound();
                                               });
										   }];

		UIAlertAction *secondOptionAction = [UIAlertAction
											actionWithTitle:secondOptionButtonTextStr
											style:UIAlertActionStyleDefault
											handler: ^(UIAlertAction *action) {
                                                AsyncTask(ENamedThreads::GameThread, [=]() {
                                                    OnSecondOptionButtonClickedDelegate.ExecuteIfBound();
                                                });
											}];

		UIAlertAction *cancelAction = [UIAlertAction
									  actionWithTitle:cancelButtonTextStr
									  style:UIAlertActionStyleDefault
									  handler: ^(UIAlertAction *action) {
                                          AsyncTask(ENamedThreads::GameThread, [=]() {
                                              OnCancelButtonClickedDelegate.ExecuteIfBound();
                                          });
									  }];

		[threeButtonsDialog addAction:firstOptionAction];
		[threeButtonsDialog addAction:secondOptionAction];
		[threeButtonsDialog addAction:cancelAction];

		[[IOSAppDelegate GetDelegate].IOSController presentViewController:threeButtonsDialog animated:true completion:nil];
	});
#endif
}

void UIGDialogBPL::ShowActionSheetSimpleDialog(FString title, FString cancelButtonText,
	TArray<FString> actionButtonsTexts, int posX, int posY,
	const FOnCancelButtonClickedDelegate &onCancelButtonClickedCallback,
	const FOnActionButtonClickedDelegate &actionButtonCallback)
{
	OnActionButtonClickedDelegate = actionButtonCallback;
	OnCancelButtonClickedDelegate = onCancelButtonClickedCallback;

#if PLATFORM_IOS
	NSString *titleStr = title.GetNSString();
	NSString *cancelButtonTextStr = cancelButtonText.GetNSString();

	dispatch_async(dispatch_get_main_queue(), ^
	{
		UIAlertController *actionSheetDialog = [UIAlertController
												alertControllerWithTitle:titleStr
												message:nil
												preferredStyle:UIAlertControllerStyleActionSheet];
		
		actionSheetDialog = (UIAlertController*) IGCommonUtils::ConfigureControllerForIPad((UIViewController*) actionSheetDialog, posX, posY);

		for(int i = 0; i < actionButtonsTexts.Num(); i++)
		{
			NSString *actionButtonsTextStr = actionButtonsTexts[i].GetNSString();

			UIAlertAction *buttonAction = [UIAlertAction
						actionWithTitle:actionButtonsTextStr
						style:UIAlertActionStyleDefault
						handler: ^(UIAlertAction *action) {
                            AsyncTask(ENamedThreads::GameThread, [=]() {
                                OnActionButtonClickedDelegate.ExecuteIfBound(i);
                            });
						}];

			[actionSheetDialog addAction:buttonAction];
		}

		UIAlertAction *cancelAction = [UIAlertAction
					actionWithTitle:cancelButtonTextStr
					style:UIAlertActionStyleDefault
					handler: ^(UIAlertAction *action) {
                        AsyncTask(ENamedThreads::GameThread, [=]() {
                            OnCancelButtonClickedDelegate.ExecuteIfBound();
                        });
					}];

		[actionSheetDialog addAction:cancelAction];

		[[IOSAppDelegate GetDelegate].IOSController presentViewController:actionSheetDialog animated:true completion:nil];
	});
#endif
}

void UIGDialogBPL::ShowActionSheetComplexDialog(FString title, FString cancelButtonText, FString destructiveButtonText,
	TArray<FString> actionButtonsTexts, int posX, int posY,
	const FOnCancelButtonClickedDelegate &onCancelButtonClickedCallback,
	const FOnDestructiveButtonClickedDelegate &onDestructiveButtonClickedCallback,
	const FOnActionButtonClickedDelegate &actionButtonCallback)
{
	OnCancelButtonClickedDelegate = onCancelButtonClickedCallback;
	OnDestructiveButtonClickedDelegate = onDestructiveButtonClickedCallback;
	OnActionButtonClickedDelegate = actionButtonCallback;

#if PLATFORM_IOS
	NSString *titleStr = title.GetNSString();
	NSString *cancelButtonTextStr = cancelButtonText.GetNSString();
	NSString *destructiveButtonTextStr = destructiveButtonText.GetNSString();

	dispatch_async(dispatch_get_main_queue(), ^
	{
		UIAlertController *actionSheetDialog = [UIAlertController
												alertControllerWithTitle:titleStr
												message:nil
												preferredStyle:UIAlertControllerStyleActionSheet];

		actionSheetDialog = (UIAlertController*) IGCommonUtils::ConfigureControllerForIPad((UIViewController*) actionSheetDialog, posX, posY);
		
		for(int i = 0; i < actionButtonsTexts.Num(); i++)
		{
			NSString *actionButtonsTextStr = actionButtonsTexts[i].GetNSString();

			UIAlertAction *buttonAction = [UIAlertAction
						actionWithTitle:actionButtonsTextStr
						style:UIAlertActionStyleDefault
						handler: ^(UIAlertAction *action) {
                            AsyncTask(ENamedThreads::GameThread, [=]() {
                                OnActionButtonClickedDelegate.ExecuteIfBound(i);
                            });
						}];

			[actionSheetDialog addAction:buttonAction];
		}

		UIAlertAction *cancelAction = [UIAlertAction
					actionWithTitle:cancelButtonTextStr
					style:UIAlertActionStyleDefault
					handler: ^(UIAlertAction *action) {
                        AsyncTask(ENamedThreads::GameThread, [=]() {
                            OnCancelButtonClickedDelegate.ExecuteIfBound();
                        });
					}];

		[actionSheetDialog addAction:cancelAction];

		UIAlertAction *destructiveAction = [UIAlertAction
					actionWithTitle:destructiveButtonTextStr
					style:UIAlertActionStyleDestructive
					handler: ^(UIAlertAction *action) {
                        AsyncTask(ENamedThreads::GameThread, [=]() {
                            OnDestructiveButtonClickedDelegate.ExecuteIfBound();
                        });
					}];

		[actionSheetDialog addAction:destructiveAction];

		[[IOSAppDelegate GetDelegate].IOSController presentViewController:actionSheetDialog animated:true completion:nil];
	});
#endif
}

void UIGDialogBPL::ShowLoadingDialog()
{
#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^{
		loadingDialog = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle: UIActivityIndicatorViewStyleWhiteLarge];
		loadingDialog.frame = CGRectMake(0, 0, 100, 100);
		UIView *view = [IOSAppDelegate GetDelegate].RootView;
		loadingDialog.center = view.center;
		[loadingDialog setHidden:NO];
		
		CGRect viewRect = [[UIScreen mainScreen] bounds];
		coverView = [[UIView alloc] initWithFrame:viewRect];
		coverView.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.8];
		[view addSubview:coverView];
		[view addSubview:loadingDialog];
		
		[loadingDialog bringSubviewToFront:view];
		[loadingDialog startAnimating];
	});
	
	[[UIApplication sharedApplication] beginIgnoringInteractionEvents];
#endif
}

void UIGDialogBPL::DismissLoadingDialog()
{
#if PLATFORM_IOS
	if(loadingDialog != nil) {
		dispatch_async(dispatch_get_main_queue(), ^{
			[loadingDialog stopAnimating];
			[loadingDialog setHidden:YES];
			[loadingDialog removeFromSuperview];
			if(coverView != nil)
			{
				[coverView removeFromSuperview];
			}
		});
	}
	
	[[UIApplication sharedApplication] endIgnoringInteractionEvents];
#endif
}

void UIGDialogBPL::ShowInputFieldDialog(FString title, FString text, FString inputPlaceholderText, FString buttonOkTitle, FString buttonCancelTitle,
	const FOnConfirmInputButtonClickedDelegate &onConfirmInputButtonClickedCallback,
	const FOnCancelButtonClickedDelegate &onCancelButtonClickedCallback)
{
	OnConfirmInputButtonClickedDelegate = onConfirmInputButtonClickedCallback;
	OnCancelButtonClickedDelegate = onCancelButtonClickedCallback;

#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertController *dialog = [UIAlertController alertControllerWithTitle:title.GetNSString() message:text.GetNSString() preferredStyle:UIAlertControllerStyleAlert];
        
        [dialog addTextFieldWithConfigurationHandler:^(UITextField *textField) {
            textField.placeholder = inputPlaceholderText.GetNSString();
            
            // When using plugin for iOS 13 and newer uncomment the following block of code
            
//            if (@available(iOS 13, *)) {
//                UITraitCollection* traitCol = [textField traitCollection];
//                if (traitCol.userInterfaceStyle == UIUserInterfaceStyleLight) {
//                    textField.textColor = [UIColor blackColor];
//                } else if (traitCol.userInterfaceStyle == UIUserInterfaceStyleDark) {
//                    textField.textColor = [UIColor whiteColor];
//                } else {
//                    textField.textColor = [UIColor blackColor];
//                }
//            } else {
//                textField.textColor = [UIColor blackColor];
//            }
            
            // end uncommenting here

            // When using plugin for iOS 13 and newer comment the following line of code
            textField.textColor = [UIColor blackColor];
            // end commenting here

            textField.clearButtonMode = UITextFieldViewModeWhileEditing;
            textField.borderStyle = UITextBorderStyleRoundedRect;
        }];
        
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:buttonOkTitle.GetNSString() style:UIAlertActionStyleDefault handler: ^(UIAlertAction *action) {
            AsyncTask(ENamedThreads::GameThread, [=]() {
                FString resultText =  FString(dialog.textFields[0].text);
                OnConfirmInputButtonClickedDelegate.ExecuteIfBound(resultText);
            });
        }];
        
        UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:buttonCancelTitle.GetNSString() style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnCancelButtonClickedDelegate.ExecuteIfBound();
            });
        }];
        
        [dialog addAction:okAction];
        [dialog addAction:cancelAction];
        
        [[IOSAppDelegate GetDelegate].IOSController presentViewController:dialog animated:true completion:nil];
    });
#endif
}

void UIGDialogBPL::ToggleStatusBar(bool statusBarHidden, enum StatusBarStyle statusBarStyle)
{
#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^{
        [((IOSViewController*)[IOSAppDelegate GetDelegate].IOSController) statusBarIsHidden:statusBarHidden];
        [((IOSViewController*)[IOSAppDelegate GetDelegate].IOSController) statusBarCurrentStyle:(int)statusBarStyle];
        [[IOSAppDelegate GetDelegate].IOSController setNeedsStatusBarAppearanceUpdate];
    });
#endif
    //CurrentBarStyle = statusBarStyle;
}
