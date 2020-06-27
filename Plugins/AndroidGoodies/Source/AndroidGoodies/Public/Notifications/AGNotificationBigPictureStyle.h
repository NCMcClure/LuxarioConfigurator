// Copyright (c) 2019 Nineva Studios

#pragma once

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#endif

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotificationBigPictureStyle.generated.h"

/**
* Helper class for generating large-format notifications that include a large image attachment.
* If the platform does not provide large-format notifications, this method has no effect,
* the user will always see the normal notification view.
*/
UCLASS(BlueprintType)
class UAGNotificationBigPictureStyle : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UAGNotificationBigPictureStyle();

	/**
	* Create a BigPictureStyle object with the big image.
	*
	* @param bigPicture - image to be shown in the big picture view of the notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static UAGNotificationBigPictureStyle* CreateBigPictureStyle(UTexture2D* bigPicture);

	/**
	* Override the large icon when the big notification is shown.
	*
	* @param icon - image for the large icon.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBigPictureStyle* SetBigLargeIcon(UTexture2D* icon);

	/**
	* Override the ContentTitle in the big form of the template. This defaults to the value passed to SetContentTitle().
	*
	* @param title - content title.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBigPictureStyle* SetBigContentTitle(FString title);

	/**
	* Set the first line of text after the detail section in the big form of the template.
	*
	* @param text - summary text.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBigPictureStyle* SetSummaryText(FString text);

#if PLATFORM_ANDROID
	jobject JavaObject;
#endif
};