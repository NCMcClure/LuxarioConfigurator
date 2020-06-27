// Copyright (c) 2019 Nineva Studios

#pragma once

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#endif

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotification.h"
#include "Enums/AGNotificationBadgeIconType.h"
#include "Enums/AGNotificationCategory.h"
#include "AGNotificationDefaults.h"
#include "Enums/AGNotificationGroupAlert.h"
#include "Enums/AGNotificationPriority.h"
#include "Enums/AGNotificationVisibility.h"
#include "AGNotificationBigTextStyle.h"
#include "AGNotificationMessageStyle.h"
#include "AGNotificationBigPictureStyle.h"
#include "AGNotificationInboxStyle.h"

#include "AGNotificationBuilder.generated.h"

UCLASS(BlueprintType)
class UAGNotificationBuilder : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UAGNotificationBuilder();

	/**
	* Combine all of the options that have been set and return a new Notification object.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotification* Build();

	/**
	* Constructor.
	*
	* @param channelId - the constructed Notification will be posted on this NotificationChannel.
	* @param additionalData - custom user notification data to be later retrieved with 
	* UAGNotificationManager.GetNotificationDataForKey() if app was launched from notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications", meta = (AutoCreateRefTerm = "additionalData"))
	static UAGNotificationBuilder* NewNotificationBuilder(FString channelId, TMap<FString, FString> additionalData);
		
	/**
	* Set the title (first row) of the notification, in a standard notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetTitle(FString title);

	/**
	* Set the text (second row) of the notification, in a standard notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetText(FString text);

	/**
	* Set the small icon to use in the notification layouts.
	* Different classes of devices may return different sizes.
	* See the UX guidelines for more information on how to design these icons.
	*
	* @param fileName - the file name of the picture, copied to the android resoureces folder.
	* Please, provide the path to the folder, from which you would like to copy the images
	* to the android drawable directory, so they can then be found and used as Android drawables.
	* This can be done by changing the "Android Drawables Folder" setting in the Project Settings / Android Goodies Settings menu in the Editor.
	* Only after this you will be able to set the small icon for the notification, which is mandatory for it to work.
	* For example, if you provide the path "D:\Projects\Images", all the files from this directory will be copied 
	* to the "PROJECT_PATH\Intermediate\Android\APK\res\drawable" folder during build time. If there is a file "Icon.png" in the "D:\Projects\Images"
	* folder, you will then be able to call this method and provide "Icon" as the file name.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetSmallIcon(FString fileName);

	/**
	* Setting this flag will make it so the notification is automatically canceled when the user clicks it in the panel.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetAutoCancel(bool autoCancel);
	
	/**
	* Set which icon to display as a badge for this notification.
	* Note: This value might be ignored for launchers that don't support badge icons.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetBadgeIconType(NotificationBadgeIconType badgeIconType);

	/**
	* Set the notification category that best describes this notification. May be used by the system for ranking and filtering.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetCategory(NotificationCategory category);

	/**
	* Set notification color. The color affects small icon and application name,
	* as well as some other elements in custom notifications (progress bar, etc.).
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetColor(FColor color);

	/**
	* Set whether this notification should be colorized.
	* When set, the color set with SetColor will be used as the background color of this notification.
	* This should only be used for high priority ongoing tasks
	* like navigation, an ongoing call, or other similarly high-priority events for the user.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetColorized(bool colorized);

	/**
	* Set the large text at the right-hand side of the notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetContentInfo(FString text);

	/**
	* Set the default notification options that will be used.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetDefaults(FAGNotificationDefaults defaults);

	/**
	* Set this notification to be part of a group of notifications sharing the same key.
	* Grouped notifications may display in a cluster or stack on devices which support such rendering.
	* To make this notification the summary for its group, also call SetGroupSummary(bool).
	* A sort order can be specified for group members by using SetSortKey(string).
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetGroup(FString groupKey);

	/**
	* Sets the group alert behavior for this notification.
	* Use this method to mute this notification if alerts for this notification's group should be
	* handled by a different notification. This is only applicable for notifications that belong to a group.
	* This must be called on all notifications you want to mute.
	* For example, if you want only the summary of your group to make noise,
	* all children in the group should have the group alert behavior GroupAlertSummary.
	* The default value is GroupAlertAll.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetGroupAlertBehaviour(NotificationGroupAlert behaviour);

	/**
	* Set this notification to be the group summary for a group of notifications.
	* Grouped notifications may display in a cluster or stack on devices which support such rendering.
	* Requires a group key also be set using SetGroup(string).
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetGroupSummary(bool summary);

	/**
	* Set the large icon that is shown in the ticker and notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetLargeIcon(UTexture2D* icon);

	/**
	* Set the desired color for the indicator LED on the device, as well as the blink duty cycle (specified in milliseconds).
	* Not all devices will honor all (or even any) of these values.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetLights(FColor color, int inMilliSeconds, int outMilliSeconds);

	/**
	* Set whether or not this notification is only relevant to the current device.
	* Some notifications can be bridged to other devices for remote display.
	* This hint can be set to recommend this notification not be bridged.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetLocalOnly(bool localOnly);

	/**
	* Set the large number at the right-hand side of the notification.
	* This is equivalent to SetContentInfo, although it might show the number
	* in a different font size for readability.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetNumber(int number);

	/**
	* Set whether this is an ongoing notification.
	* Ongoing notifications differ from regular notifications in the following ways:
	* Ongoing notifications are sorted above the regular notifications in the notification panel.
	* Ongoing notifications do not have an 'X' close button, and are not affected by the "Clear all" button.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetOngoing(bool ongoing);

	/**
	* Set this flag if you would only like the sound, vibrate and ticker 
	* to be played if the notification is not already showing.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetAlertOnce(bool alertOnce);

	/**
	* Set the relative priority for this notification. Priority is an indication of how much of the user's
	* valuable attention should be consumed by this notification.
	* Low-priority notifications may be hidden from the user in certain situations,
	* while the user might be interrupted for a higher-priority notification.
	* The system sets a notification's priority based on various factors including the SetPriority value.
	* The effect may differ slightly on different platforms.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetPriority(NotificationPriority priority);

	/**
	* Set the progress this notification represents, which may be represented as a ProgressBar.
	* Use indeterminate mode for the progress bar when you do not know how long an operation will take.
	* Indeterminate mode is the default for progress bar and shows a cyclic animation without
	* a specific amount of progress indicated.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetProgress(int current, int max, bool indeterminate);

	/**
	* Supply a replacement Notification whose contents should be shown in insecure contexts
	* (i.e. atop the secure lockscreen) for the VisibilityPublic visibility.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetPublicVersion(UAGNotification* notification);

	/**
	* If this notification is duplicative of a Launcher shortcut, sets the id of the shortcut,
	* in case the Launcher wants to hide the shortcut.
	* Note: this field will be ignored by Launchers that don't support badging or shortcuts.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetShortcutId(FString id);

	/**
	* Control whether the timestamp set with SetWhen is shown in the content view.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetShowWhen(bool showWhen);

	/**
	* Set a sort key that orders this notification among other notifications from the same package.
	* This can be useful if an external sort was already applied and an app would like to preserve this.
	* Notifications will be sorted lexicographically using this value,
	* although providing different priorities in addition to providing sort key may cause this value to be ignored.
	* This sort key can also be used to order members of a notification group.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetSortKey(FString key);

	/**
	* Set the sound to play. It will play on the default stream.
	* On some platforms, a notification that is noisy is more likely to be presented as a heads-up notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetSound(FString path);

	/**
	* Set the third line of text in the platform notification template.
	* Don't use if you're also using SetProgress(int, int, bool);
	* they occupy the same location in the standard template.
	* If the platform does not provide large-format notifications,
	* this method has no effect. The third line of text only appears in expanded view.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetSubText(FString text);

	/**
	* Sets the "ticker" text which is sent to accessibility services.
	* Prior to LOLLIPOP, sets the text that is displayed in the status bar when the notification first arrives.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetTicker(FString text);

	/**
	* Specifies the time at which this notification should be canceled, if it is not already canceled.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetTimeoutAfter(int milliSeconds);

	/**
	* Show the when field as a stopwatch. Instead of presenting when as a timestamp, the notification will show
	* an automatically updating display of the minutes and seconds since when.
	* Useful when showing an elapsed time (like an ongoing phone call).
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetUsesChronometer(bool usesChronometer);

	/**
	* Set the vibration pattern to use.
	* On some platforms, a notification that vibrates is more likely to be presented as a heads-up notification.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetVibrate(TArray<float> pattern);

	/**
	* Sets visibility.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetVisibility(NotificationVisibility visibility);

	/**
	* Set the time that the event occurred. Notifications in the panel are sorted by this time.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetWhen(FDateTime dateTime);

	/**
	* Add a rich notification style to be applied at build time.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetBigTextStyle(UAGNotificationBigTextStyle* style);

	/**
	* Generate a large-format notification that include a list of (up to 5) strings.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetMessagingStyle(UAGNotificationMessageStyle* style);

	/**
	* Add a rich notification style to be applied at build time.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetBigPictureStyle(UAGNotificationBigPictureStyle* style);

	/**
	* Use this for generating large-format notifications that include multiple back-and-forth 
	* messages of varying types between any number of people.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* SetInboxStyle(UAGNotificationInboxStyle* style);

	/**
	* Add a button to notification expanded view. An URL will be open on tap.
	*
	* @param iconName - the name of the file in the drawables folder. For more info see SetSmallIcon()
	* @param title - button text
	* @param url - URL to open on tap
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationBuilder* AddOpenUrlAction(FString iconName, FString title, FString url);

private:
#if PLATFORM_ANDROID
	jobject javaBuilder;
#endif
};