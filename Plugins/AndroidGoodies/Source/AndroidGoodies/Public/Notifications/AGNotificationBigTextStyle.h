// Copyright (c) 2019 Nineva Studios

#pragma once

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#endif

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotificationBigTextStyle.generated.h"

/**
* Helper class for generating large-format notifications that include a lot of text.
* If the platform does not provide large-format notifications, this method has no effect.
* The user will always see the normal notification view.
*/

UCLASS(BlueprintType)
class UAGNotificationBigTextStyle : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UAGNotificationBigTextStyle();

	/**
	* Create a BigTextStyle object with the big text.
	*
	* @param bigText - the longer text to be displayed in the big form of the template in place of the content text.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static UAGNotificationBigTextStyle* CreateBigTextStyle(FString bigText);

	/**
	* Override the ContentTitle in the big form of the template. This defaults to the value passed to SetContentTitle().
	*
	* @param title - content title.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBigTextStyle* SetBigContentTitle(FString title);

	/**
	* Set the first line of text after the detail section in the big form of the template.
	*
	* @param text - summary text.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBigTextStyle* SetSummaryText(FString summary);

#if PLATFORM_ANDROID
	jobject JavaObject;
#endif
};

