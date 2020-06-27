// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationChannelGroup.h"
#include "Notifications/AGNotificationManager.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif	

UAGNotificationChannelGroup::~UAGNotificationChannelGroup()
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => UAGNotification::~UAGNotification()"));
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteLocalRef(JavaNotificationGroupObject);
	JavaNotificationGroupObject = nullptr;
#endif
}

UAGNotificationChannelGroup * UAGNotificationChannelGroup::NewNotificationChannelGroup(FString id, FString name)
{
	UAGNotificationChannelGroup* group = NewObject<UAGNotificationChannelGroup>();

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		group->JavaNotificationGroupObject = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName,
			"getNotificationChannelGroup", "(Ljava/lang/String;Ljava/lang/String;)Landroid/app/NotificationChannelGroup;",
			AGArrayConvertor::GetJavaString(id), AGArrayConvertor::GetJavaString(name));
#endif
	}

	return group;
}

FString UAGNotificationChannelGroup::GetId()
{
	FString result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationGroupObject)
		{
			result = AGMethodCallUtils::CallStringMethod(JavaNotificationGroupObject, "getId", "()Ljava/lang/String;");
		}		
#endif
	}

	return result;
}

FString UAGNotificationChannelGroup::GetName()
{
	FString result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationGroupObject)
		{
			result = AGMethodCallUtils::CallStringMethod(JavaNotificationGroupObject, "getName", "()Ljava/lang/CharSequence;");
		}			
#endif
	}

	return result;
}

FString UAGNotificationChannelGroup::GetDescription()
{
	FString result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationGroupObject)
		{
			result = AGMethodCallUtils::CallStringMethod(JavaNotificationGroupObject, "getDescription", "()Ljava/lang/String;");
		}		
#endif
	}

	return result;
}

UAGNotificationChannelGroup * UAGNotificationChannelGroup::SetDescription(FString description)
{
	if (UAGDeviceInfo::GetSdkInt() >= 28)
	{
#if PLATFORM_ANDROID
		if (JavaNotificationGroupObject)
		{
			AGMethodCallUtils::CallVoidMethod(JavaNotificationGroupObject, "setDescription", "(Ljava/lang/String;)V", AGArrayConvertor::GetJavaString(description));
		}			
#endif
	}

	return this;
}

bool UAGNotificationChannelGroup::IsBlocked()
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationGroupObject)
		{
			return AGMethodCallUtils::CallBoolMethod(JavaNotificationGroupObject, "isBlocked", "()Z");
		}		
#endif
	}

	return true;
}

TArray<UAGNotificationChannel*> UAGNotificationChannelGroup::GetChannels()
{
	TArray<UAGNotificationChannel*> result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationGroupObject)
		{
			jobject channelList = AGMethodCallUtils::CallObjectMethod(JavaNotificationGroupObject, "getChannels", "()Ljava/util/List;");

			//TODO: make util method for working with java lists?
			int count = AGMethodCallUtils::CallIntMethod(channelList, "size", "()I");
			for (int i = 0; i < count; i++)
			{
				UAGNotificationChannel* channel = NewObject<UAGNotificationChannel>();
				channel->JavaNotificationChannelObject = AGMethodCallUtils::CallObjectMethod(channelList, "get", "(I)Ljava/lang/Object;", i);
				result.Add(channel);
			}

			JNIEnv* Env = FAndroidApplication::GetJavaEnv();
			Env->DeleteLocalRef(channelList);
		}			
#endif
	}

	return result;
}
