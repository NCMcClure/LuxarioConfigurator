// Copyright (c) 2019 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotification.h"
#include "AGNotificationChannel.h"
#include "AGNotificationChannelGroup.h"
#include "AGNotificationBuilder.h"
#include "Enums/AGChannelImportance.h"
#include "Enums/AGInterruptionFilter.h"
#include "AGDeviceInfoBPL.h"

#include "AGNotificationManager.generated.h"

UCLASS()
class ANDROIDGOODIES_API UAGNotificationManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public: 

	/**
	* Post a notification to be shown in the status bar, stream, etc.
	*
	* @param notification - the notification to post to the system.
	* @param id - the ID of the notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void Notify(UAGNotification* notification, int id);

	/**
	* Creates a notification channel that notifications can be posted to.
	* This can also be used to restore a deleted channel and to update an existing channel's name,
	* description, group, and/or importance. The name and description should only be changed
	* if the locale changes or in response to the user renaming this channel.
	* For example, if a user has a channel named 'John Doe' that represents messages from a 'John Doe',
	* and 'John Doe' changes his name to 'John Smith,' the channel can be renamed to match.
	* The importance of an existing channel will only be changed if the new importance is lower
	* than the current value and the user has not altered any settings on this channel.
	* The group an existing channel will only be changed if the channel does not already
	* belong to a group. All other fields are ignored for channels that already exist.
	*
	* @param channel - the channel to create. Note that the created channel may differ from this value.
	* If the provided channel is malformed, a RemoteException will be thrown.
	* This value must never be null.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void CreateNotificationChannel(UAGNotificationChannel* channel);

	/**
	* Create a group container for NotificationChannel objects. This can be used to rename an existing group.
	* Group information is only used for presentation, not for behavior. Groups are optional for channels,
	* and you can have a mix of channels that belong to groups and channels that do not.
	* For example, if your application supports multiple accounts, and those accounts will have similar channels,
	* you can create a group for each account with account specific labels instead of appending account
	* information to each channel's label.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void CreateNotificationChannelGroup(UAGNotificationChannelGroup* group);

	/**
	* Convenience property to check if the app was opened from notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static bool WasApplicationOpenViaNotification();
	
	/**
	* Cancel a previously shown notification. If it's transient, the view will be hidden.
	* If it's persistent, it will be removed from the status bar.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void CancelNotification(int id);

	/**
	* Cancel all previously shown notifications.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void CancelAllNotifications();

	/**
	* Get the user specified importance for notifications from the calling package.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static TEnumAsByte<ChannelImportance> GetCurrentImportance();

	/**
	* Get the current notification interruption filter. The interruption filter defines which notifications
	* are allowed to interrupt the user (e.g. via sound & vibration) and is applied globally.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static TEnumAsByte<InterruptionFilter> GetCurrentInterruptionFilter();

	/**
	* Set the current notification interruption filter. The interruption filter defines which notifications
	* are allowed to interrupt the user (e.g. via sound & vibration) and is applied globally.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void SetCurrentInterruptionFilter(InterruptionFilter filter);

	/**
	* Property to check if the new notification channels API is supported on the current device.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static inline bool AreNotificationChannelsSupported()
	{
		return UAGDeviceInfo::GetSdkInt() >= 26;
	}

	/**
	* Schedule a notification to be shown in the status bar, stream, etc. after the specified time.
	*
	* @param notification - the notification to post to the system.
	* @param id - the ID of the notification.
	* @param notifyAfter - timespan to pass before the actual notifying.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void ScheduleNotification(UAGNotification* notification, int id, FTimespan notifyAfter);

	/**
	* Schedule a repeating notification to be shown in the status bar, stream, etc. after the specified time.
	*
	* @param notification - the notification to post to the system.
	* @param id - the ID of the notification.
	* @param notifyAfter - timespan to pass before the actual notifying.
	* @param repeatAfter - timespan to pass before the next notifying.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void ScheduleRepeatingNotification(UAGNotification* notification, int id, FTimespan notifyAfter, FTimespan repeatAfter);

	/**
	* Cancel previously scheduled notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void CancelScheduledNotification(int id);

	/**
	* Try to retrieve extra data, provided with the NewNotificationBuilder additional data dictionary.
	* This data can only be retrived if the application was open by tapping the respective notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static FString GetNotificationDataForKey(FString key);

	/**
	* Return the notification channel settings for a given channel id.
	* The channel must belong to your package, or it will not be returned.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static UAGNotificationChannel* GetNotificationChannel(FString channelId);

	/**
	* Return all notification channels belonging to the calling package.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static TArray<UAGNotificationChannel*> GetNotificationChannels();

	/**
	* Delete the given notification channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void DeleteNotificationChannel(FString channelId);

	/**
	* Get the notification channel group settings for a given channel group id.
	* The channel group must belong to your package, or null will be returned.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static UAGNotificationChannelGroup* GetNotificationChannelGroup(FString groupId);

	/**
	* Return all notification channel groups belonging to the calling package.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static TArray<UAGNotificationChannelGroup*> GetNotificationChannelGroups();

	/**
	* Delete the given notification channel group, and all notification channels that belong to it.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void DeleteNotificationChannelGroup(FString groupId);

	/**
	* Open system settings window for the selected channel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static void OpenNotificationChannelSettings(FString channelId);

	static const ANSICHAR* NotificationHelperClassName;
};