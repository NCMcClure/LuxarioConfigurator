// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Texture2D.h"
#include "IGShareBPL.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnShareSuccessDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnShareErrorDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnShareCancelDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnSavedDraftDelegate);

/**
* Class for content sharing.
*/
UCLASS()
class IOSGOODIES_API UIGShare : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	/**
	* Share the specified text.
	* @param message - text to be shared
	* @param posX - X position of the arrow on iPad screen. Positioning zero is at left side of the screen
	* @param posY - Y position of the arrow on iPad screen. Positioning zero is at top of the screen
	* @param onSuccessCallback - action to be performed after successful sharing
	* @param onErrorCallback - action to be performed after unsuccessful sharing
	*/
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback"))
    static void ShareText(FString message, int posX, int posY,
		const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback);
	
	/**
	 * Share the image.
	 * @param texture - UTexture2D source for image
	 * @param posX - X position of the arrow on iPad screen. Positioning zero is at left side of the screen
	 * @param posY - Y position of the arrow on iPad screen. Positioning zero is at top of the screen
	 * @param onSuccessCallback - action to be performed after successful sharing
	 * @param onErrorCallback - action to be performed after unsuccessful sharing
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback"))
	static void ShareImage(UTexture2D *texture, int posX, int posY,
        const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback);
	
	/**
	 * Share the link.
	 * @param link - link to be shared
	 * @param posX - X position of the arrow on iPad screen. Positioning zero is at left side of the screen
	 * @param posY - Y position of the arrow on iPad screen. Positioning zero is at top of the screen
	 * @param onSuccessCallback - action to be performed after successful sharing
	 * @param onErrorCallback - action to be performed after unsuccessful sharing
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback"))
	static void ShareLink(FString link, int posX, int posY,
        const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback);
	
	/**
	* Share the specified text with image attachment.
	* @param message - text to be shared
	* @param texture - UTexture2D source for image
	* @param posX - X position of the arrow on iPad screen. Positioning zero is at left side of the screen
	* @param posY - Y position of the arrow on iPad screen. Positioning zero is at top of the screen
	* @param onSuccessCallback - action to be performed after successful sharing
	* @param onErrorCallback - action to be performed after unsuccessful sharing
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback"))
	static void ShareTextWithImage(FString message, UTexture2D *texture, int posX, int posY,
		const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback);
	
	/**
	* Share the specified text with link.
	* @param message - text to be shared
	* @param link - link to be shared
	* @param posX - X position of the arrow on iPad screen. Positioning zero is at left side of the screen
	* @param posY - Y position of the arrow on iPad screen. Positioning zero is at top of the screen
	* @param onSuccessCallback - action to be performed after successful sharing
	* @param onErrorCallback - action to be performed after unsuccessful sharing
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback"))
	static void ShareTextWithLink(FString message, FString link, int posX, int posY,
		const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback);
	
	/**
	 * Share the specified text with link and image.
	 * @param message - text to be shared
	 * @param texture - UTexture2D source for image
	 * @param link - link to be shared
	 * @param posX - X position of the arrow on iPad screen. Positioning zero is at left side of the screen
	 * @param posY - Y position of the arrow on iPad screen. Positioning zero is at top of the screen
	 * @param onSuccessCallback - action to be performed after successful sharing
	 * @param onErrorCallback - action to be performed after unsuccessful sharing
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback"))
	static void ShareTextWithImageAndLink(FString message, UTexture2D *texture, FString link, int posX, int posY,
        const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback);
	
	/**
	* Send text message with action callbacks.
	* @param phoneNumber - phone number of the recepient
	* @param msgText - text of the message
	* @param onSuccessCallback - action to be performed after successful sending
	* @param onErrorCallback - action to be performed after unsuccessful sending
	* @param onCancelCallback - action to be performed after cancellation
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback, onCancelCallback"))
	static void SendSms(FString phoneNumber, FString msgText,
		const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback, const FOnShareCancelDelegate &onCancelCallback);
	
	/**
	* Send text message via default SMS app on the device.
	* @param phoneNumber - phone number of the recepient
	* @param msgText - text of the message
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void SendSMSViaDefaultApp(FString phoneNumber, FString msgText);
	
	/**
	* Send e-mail via default mailing app on the device.
	* @param subject - subject of the message
	* @param body - text of the message
	* @param recipients - array of recipients addresses
	* @param cc - array of cc addresses (CC stands for Carbon Copy)
	* @param bcc - array of bcc addresses (BCC stands for Blind Carbon Copy)
	* @note Bcc recipients are invisible to all the other recipients of the message including other bcc recipients.
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void SendEmailViaDefaultApp(FString subject, FString body,
		TArray<FString> recipients, TArray<FString> cc, TArray<FString> bcc);
	
	/**
	* Send e-mail.
	* @param subject - subject of the message
	* @param body - text of the message
	* @param texture - UTexture2D source for image attachment
	* @param recipients - array of recipients addresses
	* @param cc - array of cc addresses (CC stands for Carbon Copy)
	* @param bcc - array of bcc addresses (BCC stands for Blind Carbon Copy)
	* @param onSuccessCallback - action to be performed after successful sending
	* @param onErrorCallback - action to be performed after unsuccessful sending
	* @param onCancelDelegate - action to be performed after sharing via email cancelled and draft was deleted
	* @param onSavedDraftCallback - action to be performed after sharing via email cancelled and draft was saved
	* @note Bcc recipients are invisible to all the other recipients of the message including other bcc recipients.
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback, onCancelDelegate, onSavedDraftCallback"))
	static void SendEmail(FString subject, FString body, UTexture2D *texture,
		TArray<FString> recipients, TArray<FString> cc, TArray<FString> bcc,
		const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback,
		const FOnShareCancelDelegate &onCancelDelegate, const FOnSavedDraftDelegate &onSavedDraftCallback);
	
	/**
	 * Check whether the device supports sending e-mails.
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static bool CanSendEmail();
	
	/**
	 * Check whether the device supports sending SMS.
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static bool CanSendSMS();

private:

	static FOnShareSuccessDelegate OnShareSuccessDelegate;
	static FOnShareErrorDelegate OnShareErrorDelegate;
	static FOnShareCancelDelegate OnShareCancelDelegate;
	static FOnSavedDraftDelegate OnSavedDraftDelegate;
};
