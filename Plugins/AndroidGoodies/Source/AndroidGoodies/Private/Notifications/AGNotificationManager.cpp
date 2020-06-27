// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationManager.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#endif	

const ANSICHAR* UAGNotificationManager::NotificationHelperClassName = "com/ninevastudios/androidgoodies/AGNotificationHelper";

void UAGNotificationManager::Notify(UAGNotification* notification, int id)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName,
		"notify", "(Landroid/app/Activity;Landroid/app/Notification;I)V", FJavaWrapper::GameActivityThis, notification->JavaNotificationObject, id);
#endif	
}

void UAGNotificationManager::CreateNotificationChannel(UAGNotificationChannel* channel)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName,
			"createNotificationChannel", "(Landroid/app/Activity;Landroid/app/NotificationChannel;)V", FJavaWrapper::GameActivityThis, channel->JavaNotificationChannelObject);
#endif	
	}
}

void UAGNotificationManager::CreateNotificationChannelGroup(UAGNotificationChannelGroup * group)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName,
			"createNotificationChannelGroup", "(Landroid/app/Activity;Landroid/app/NotificationChannelGroup;)V", FJavaWrapper::GameActivityThis, group->JavaNotificationGroupObject);
#endif	
	}
}

bool UAGNotificationManager::WasApplicationOpenViaNotification()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(NotificationHelperClassName, "wasAppOpenViaNotification", "()Z");
#endif	

	return false;
}

void UAGNotificationManager::CancelNotification(int id)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName,
		"cancelNotification", "(Landroid/app/Activity;I)V", FJavaWrapper::GameActivityThis, id);
#endif	
}

void UAGNotificationManager::CancelAllNotifications()
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName,
		"cancelAllNotifications", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif	
}

TEnumAsByte<ChannelImportance> UAGNotificationManager::GetCurrentImportance()
{
#if PLATFORM_ANDROID
	return (ChannelImportance) AGMethodCallUtils::CallStaticIntMethod(NotificationHelperClassName,
		"getCurrentImportance", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif	

	return ChannelImportance::ImportanceUnspecified;
}

TEnumAsByte<InterruptionFilter> UAGNotificationManager::GetCurrentInterruptionFilter()
{
#if PLATFORM_ANDROID
	return (InterruptionFilter) AGMethodCallUtils::CallStaticIntMethod(NotificationHelperClassName,
		"getCurrentInterruptionFilter", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif	

	return InterruptionFilter::FilterUnknown;
}

void UAGNotificationManager::SetCurrentInterruptionFilter(InterruptionFilter filter)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName,
		"setCurrentInterruptionFilter", "(Landroid/app/Activity;I)V", FJavaWrapper::GameActivityThis, (int) filter);
#endif	
}

void UAGNotificationManager::ScheduleNotification(UAGNotification * notification, int id, FTimespan notifyAfter)
{
	long whenLong = (long) FMath::RoundHalfFromZero(notifyAfter.GetTotalMilliseconds());
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Schedule Notification: Delayed Time: %d"), whenLong);
#if PLATFORM_ANDROID
	jlong whenJavaLong = static_cast<jlong>(whenLong);

	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "scheduleNotification", "(Landroid/app/Activity;Landroid/app/Notification;IJ)V", 
		FJavaWrapper::GameActivityThis, notification->JavaNotificationObject, id, whenJavaLong);
#endif	
}

void UAGNotificationManager::ScheduleRepeatingNotification(UAGNotification * notification, int id, FTimespan notifyAfter, FTimespan repeatAfter)
{
	long whenLong = (long) FMath::RoundHalfFromZero(notifyAfter.GetTotalMilliseconds());
	long repeatAfterLong = (long) FMath::RoundHalfFromZero(repeatAfter.GetTotalMilliseconds());
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Schedule Notification: Delayed Time: %d milliseconds."), whenLong);
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Schedule Notification: Repear After: %d milliseconds."), repeatAfterLong);
#if PLATFORM_ANDROID
	jlong whenJavaLong = static_cast<jlong>(whenLong);
	jlong repeatAfterJavaLong = static_cast<jlong>(repeatAfterLong);
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "scheduleRepeatingNotification", "(Landroid/app/Activity;Landroid/app/Notification;IJJ)V", 
		FJavaWrapper::GameActivityThis, notification->JavaNotificationObject, id, whenJavaLong, repeatAfterJavaLong);
#endif	
}

void UAGNotificationManager::CancelScheduledNotification(int id)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "cancelScheduledNotification", "(Landroid/app/Activity;I)V", 
		FJavaWrapper::GameActivityThis, id);
#endif	
}

FString UAGNotificationManager::GetNotificationDataForKey(FString key)
{
	FString result;

#if PLATFORM_ANDROID
	result = AGMethodCallUtils::CallStaticStringMethod(NotificationHelperClassName, "getNotificationData", "(Ljava/lang/String;)Ljava/lang/String;", 
		AGArrayConvertor::GetJavaString(key));
#endif	

	return result;
}

UAGNotificationChannel* UAGNotificationManager::GetNotificationChannel(FString channelId)
{
	UAGNotificationChannel* channel = NewObject<UAGNotificationChannel>();

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		channel->JavaNotificationChannelObject = AGMethodCallUtils::CallStaticObjectMethod(NotificationHelperClassName, "findNotificationChannel",
			"(Landroid/app/Activity;Ljava/lang/String;)Landroid/app/NotificationChannel;", 
			FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(channelId));
#endif	
	}

	return channel;
}

TArray<UAGNotificationChannel*> UAGNotificationManager::GetNotificationChannels()
{
	TArray<UAGNotificationChannel*> result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		jobjectArray javaChannels = static_cast<jobjectArray>(AGMethodCallUtils::CallStaticObjectMethod(NotificationHelperClassName, "getNotificationChannels", 
			"(Landroid/app/Activity;)[Landroid/app/NotificationChannel;", FJavaWrapper::GameActivityThis));

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		int length = Env->GetArrayLength(javaChannels);

		for (int i = 0; i < length; i++)
		{
			UAGNotificationChannel* channel = NewObject<UAGNotificationChannel>();
			channel->JavaNotificationChannelObject = Env->GetObjectArrayElement(javaChannels, i);
			result.Add(channel);
		}
#endif	
	}

	return result;
}

void UAGNotificationManager::DeleteNotificationChannel(FString channelId)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "deleteNotificationChannel",
			"(Landroid/app/Activity;Ljava/lang/String;)V", FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(channelId));
#endif	
	}
}

UAGNotificationChannelGroup * UAGNotificationManager::GetNotificationChannelGroup(FString groupId)
{
	UAGNotificationChannelGroup* group = NewObject<UAGNotificationChannelGroup>();

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
		if (UAGDeviceInfo::GetSdkInt() >= 28)
		{
#if PLATFORM_ANDROID
			group->JavaNotificationGroupObject = AGMethodCallUtils::CallStaticObjectMethod(NotificationHelperClassName, "findNotificationChannelGroup",
				"(Landroid/app/Activity;Ljava/lang/String;)Landroid/app/NotificationChannelGroup;",
				FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(groupId));
#endif	
		}
	}

	return group;
}

TArray<UAGNotificationChannelGroup*> UAGNotificationManager::GetNotificationChannelGroups()
{
	TArray<UAGNotificationChannelGroup*> result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		jobjectArray javaChannelGroups = static_cast<jobjectArray>(AGMethodCallUtils::CallStaticObjectMethod(NotificationHelperClassName, "getNotificationChannelGroups", 
			"(Landroid/app/Activity;)[Landroid/app/NotificationChannelGroup;", FJavaWrapper::GameActivityThis));

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		int length = Env->GetArrayLength(javaChannelGroups);
		
		for (int i = 0; i < length; i++)
		{
			UAGNotificationChannelGroup* group = NewObject<UAGNotificationChannelGroup>();
			group->JavaNotificationGroupObject = Env->GetObjectArrayElement(javaChannelGroups, i);
			result.Add(group);
		}
#endif	
	}

	return result;
}

void UAGNotificationManager::DeleteNotificationChannelGroup(FString groupId)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "deleteNotificationChannelGroup",
			"(Landroid/app/Activity;Ljava/lang/String;)V", FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(groupId));
#endif	
	}
}

void UAGNotificationManager::OpenNotificationChannelSettings(FString channelId)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		AGMethodCallUtils::CallStaticVoidMethod(NotificationHelperClassName, "openNotificationChannelSettings",
			"(Landroid/app/Activity;Ljava/lang/String;)V", FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(channelId));
#endif	
	}
}
