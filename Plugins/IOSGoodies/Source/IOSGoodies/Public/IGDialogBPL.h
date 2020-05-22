// Copyright (c) 2018 Nineva Studios

#pragma once

#include "IGStatusBarStyle.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IGDialogBPL.generated.h"

//TODO: consider option of using single delegate type here

DECLARE_DYNAMIC_DELEGATE(FOnConfirmButtonClickedDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnCancelButtonClickedDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnFirstOptionButtonClickedDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnSecondOptionButtonClickedDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnDestructiveButtonClickedDelegate);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnActionButtonClickedDelegate, int, index);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnConfirmInputButtonClickedDelegate, FString, result);

UCLASS()
class IOSGOODIES_API UIGDialogBPL : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Show the default iOS dialog with single confirmation button.
	* @param title - message title text to be displayed in dialog
	* @param message - message text to be displayed in dialog
	* @param confirmButtonText - text displayed in dialogs confirmation button
	* @param onConfirmButtonClickedCallback - callback function that is called after user clicked confirmation button
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onConfirmButtonClickedCallback"))
	static void ShowSingleButtonDialog(FString title, FString message, FString confirmButtonText,
		const FOnConfirmButtonClickedDelegate &onConfirmButtonClickedCallback);

	/**
	* Show the default iOS dialog with confirmation and cancellation buttons (e.g. Yes/No, Ok/Cancel).
	* @param title - message title text to be displayed in dialog
	* @param message - message text to be displayed in dialog
	* @param confirmButtonText - text displayed in dialogs confirmation button
	* @param cancelButtonText - text displayed in dialogs cancellation button
	* @param onConfirmButtonClickedCallback - callback function that is called after user clicked confirmation button
	* @param onCancelButtonClickedCallback - callback function that is called after user clicked cancellation button
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onConfirmButtonClickedCallback, onCancelButtonClickedCallback"))
	static void
	ShowTwoButtonsDialog(FString title, FString message, FString confirmButtonText, FString cancelButtonText,
		const FOnConfirmButtonClickedDelegate &onConfirmButtonClickedCallback,
		const FOnCancelButtonClickedDelegate &onCancelButtonClickedCallback);

	/**
	* Show the default iOS chooser dialog with two option buttons and cancellation button.
	* @param title - message title text to be displayed in dialog
	* @param message - message text to be displayed in dialog
	* @param firstOptionButtonText - text displayed in dialogs first option button
	* @param secondOptionButtonText - text displayed in dialogs second option button
	* @param cancelButtonText - text displayed in dialogs cancellation button
	* @param onFirstOptionButtonClickedCallback - callback function that is called after user clicked first option button
	* @param onSecondOptionButtonClickedCallback - callback function that is called after user clicked second option button
	* @param onCancelButtonClickedCallback - callback function that is called after user clicked cancellation button
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onFirstOptionButtonClickedCallback, onSecondOptionButtonClickedCallback, onCancelButtonClickedCallback"))
	static void ShowThreeButtonsDialog(FString title, FString message,
		FString firstOptionButtonText, FString secondOptionButtonText,
		FString cancelButtonText,
		const FOnFirstOptionButtonClickedDelegate &onFirstOptionButtonClickedCallback,
		const FOnSecondOptionButtonClickedDelegate &onSecondOptionButtonClickedCallback,
		const FOnCancelButtonClickedDelegate &onCancelButtonClickedCallback);

	/**
	* Show the default iOS action sheet dialog.
	* @param title - action sheet title text to be displayed
	* @param cancelButtonText - text displayed in cancellation button
	* @param actionButtonsTexts - array of action sheet buttons names
	* @param posX - X position of the arrow on iPad screen. Positioning zero is at left side of the screen
	* @param posY - Y position of the arrow on iPad screen. Positioning zero is at top of the screen
	* @param onCancelButtonClickedCallback - callback function that is called after user clicked cancellation button
	* @param actionButtonCallback - callback function that is called after user clicked one of action buttons
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onCancelButtonClickedCallback, actionButtonCallback"))
	static void ShowActionSheetSimpleDialog(FString title, FString cancelButtonText,
		TArray<FString> actionButtonsTexts, int posX, int posY,
		const FOnCancelButtonClickedDelegate &onCancelButtonClickedCallback,
		const FOnActionButtonClickedDelegate &actionButtonCallback);

	/**
	* Show the default iOS action sheet dialog with destructive button.
	* @param title - action sheet title text to be displayed
	* @param cancelButtonText - text displayed in cancellation button
	* @param destructiveButtonText - text displayed in destructive button
	* @param actionButtonsTexts - array of action sheet buttons names
	* @param posX - X position of the arrow on iPad screen. Positioning zero is at left side of the screen
	* @param posY - Y position of the arrow on iPad screen. Positioning zero is at top of the screen
	* @param onCancelButtonClickedCallback - callback function that is called after user clicked cancellation button
	* @param onDestructiveButtonClickedCallback - callback function that is called after user clicked destructive button
	* @param actionButtonCallback - callback function that is called after user clicked one of action buttons
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onCancelButtonClickedCallback, onDestructiveButtonClickedCallback, actionButtonCallback"))
	static void ShowActionSheetComplexDialog(FString title, FString cancelButtonText, FString destructiveButtonText,
		TArray<FString> actionButtonsTexts, int posX, int posY,
		const FOnCancelButtonClickedDelegate &onCancelButtonClickedCallback,
		const FOnDestructiveButtonClickedDelegate &onDestructiveButtonClickedCallback,
		const FOnActionButtonClickedDelegate &actionButtonCallback);
	
	/**
	 * Show the native loading screen, blocking any user interface interactions until dismissed.
	 */
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies")
	static void ShowLoadingDialog();
	
	/**
	* Dismiss the native loading screen.
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies")
	static void DismissLoadingDialog();
	
	/**
	* Show the native dialog with an input field and two buttons (confirm and cancel).
	* @param title - dialog title text to be displayed
	* @param text - dialog text body
	* @param inputPlaceholderText - text to be displayed in the input field before user starts typing
	* @param buttonOkTitle - text to be displayed on the confirmation button
	* @param buttonCancelTitle - text to be displayed on the cancellation button
	* @param onConfirmInputButtonClickedCallback - callback function that is called after user clicked confirmation button
	* @param onCancelButtonClickedCallback - callback function that is called after user clicked cancellation button
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onConfirmInputButtonClickedCallback, onCancelButtonClickedCallback"))
	static void ShowInputFieldDialog(FString title, FString text, FString inputPlaceholderText, FString buttonOkTitle, FString buttonCancelTitle,
		const FOnConfirmInputButtonClickedDelegate &onConfirmInputButtonClickedCallback,
		const FOnCancelButtonClickedDelegate &onCancelButtonClickedCallback);

    UFUNCTION(BlueprintCallable, Category = "IOSGoodies")
    static void ToggleStatusBar(bool statusBarHidden, StatusBarStyle statusBarStyle);

//public:
//    static bool IsHidden;
//    static StatusBarStyle CurrentBarStyle;
    
private:
	static FOnConfirmButtonClickedDelegate OnConfirmButtonClickedDelegate;
	static FOnCancelButtonClickedDelegate OnCancelButtonClickedDelegate;
	static FOnFirstOptionButtonClickedDelegate OnFirstOptionButtonClickedDelegate;
	static FOnSecondOptionButtonClickedDelegate OnSecondOptionButtonClickedDelegate;
	static FOnDestructiveButtonClickedDelegate OnDestructiveButtonClickedDelegate;
	static FOnActionButtonClickedDelegate OnActionButtonClickedDelegate;
	static FOnConfirmInputButtonClickedDelegate OnConfirmInputButtonClickedDelegate;
};
