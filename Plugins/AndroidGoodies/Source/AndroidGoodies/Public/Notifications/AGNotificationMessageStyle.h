// Copyright (c) 2019 Nineva Studios

#pragma once

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#endif

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotificationMessageStyle.generated.h"

/**
* Helper class for generating large-format notifications that include multiple back-and-forth messages of varying
* types between any number of people.
* This could be the user-created name of the group or, if it doesn't have a specific name, a list of the participants
* in the conversation.
* Do not set a conversation title for one-on-one chats, since platforms use the existence of this field as a hint
* that the conversation is a group.
*/
UCLASS(BlueprintType)
class UAGNotificationMessageStyle : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UAGNotificationMessageStyle();

	/**
	* Create a MessageStyle object.
	*
	* @param userDisplayName - the displayed user name.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static UAGNotificationMessageStyle* CreateMessageStyle(FString userDisplayName);

	/**
	* Add a message for display by this notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationMessageStyle* AddMessage(FString text, FDateTime timeStamp, FString sender);

	/**
	* Set the title to be displayed on this conversation.
	* This API's behavior was changed in SDK version P. If your application's target version is less than P,
	* setting a conversation title to a non-null value will make isGroupConversation() return true. 
	* In P and beyond, use SetGroupConversation() to set group conversation status.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationMessageStyle* SetConversationTitle(FString title);

	/**
	* Set whether this conversation notification represents a group.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationMessageStyle* SetGroupConversation(bool isGroupConversation);

#if PLATFORM_ANDROID
	jobject JavaObject;
#endif
};