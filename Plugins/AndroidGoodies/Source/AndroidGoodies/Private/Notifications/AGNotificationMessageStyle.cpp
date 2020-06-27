// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationMessageStyle.h"
#include "Notifications/AGNotificationManager.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif	

UAGNotificationMessageStyle::~UAGNotificationMessageStyle()
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => UAGNotificationBigTextStyle::~UAGNotificationBigTextStyle()"));
#if PLATFORM_ANDROID
	if (JavaObject)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		Env->DeleteLocalRef(JavaObject);
		JavaObject = nullptr;
	}	
#endif
}

UAGNotificationMessageStyle * UAGNotificationMessageStyle::CreateMessageStyle(FString userDisplayName)
{
	UAGNotificationMessageStyle* style = NewObject<UAGNotificationMessageStyle>();
#if PLATFORM_ANDROID
	style->JavaObject = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "getMessagingStyle",
		"(Ljava/lang/String;)Landroid/support/v4/app/NotificationCompat$MessagingStyle;", AGArrayConvertor::GetJavaString(userDisplayName));
#endif
	return style;
}

UAGNotificationMessageStyle * UAGNotificationMessageStyle::AddMessage(FString text, FDateTime timeStamp, FString sender)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Add Message -> TimeStamp: %s"), *(timeStamp.ToString()));
	long dateLong = timeStamp.ToUnixTimestamp() * 1000;
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Add Message -> TimeStamp: %d"), dateLong);

#if PLATFORM_ANDROID
	JavaObject = AGMethodCallUtils::CallObjectMethod(JavaObject, "addMessage", "(Ljava/lang/CharSequence;JLjava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$MessagingStyle;", 
		AGArrayConvertor::GetJavaString(text), static_cast<jlong>(dateLong), AGArrayConvertor::GetJavaString(sender));
#endif

	return this;
}

UAGNotificationMessageStyle * UAGNotificationMessageStyle::SetConversationTitle(FString title)
{
#if PLATFORM_ANDROID
	JavaObject = AGMethodCallUtils::CallObjectMethod(JavaObject, "setConversationTitle", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$MessagingStyle;", 
		AGArrayConvertor::GetJavaString(title));
#endif

	return this;
}

UAGNotificationMessageStyle * UAGNotificationMessageStyle::SetGroupConversation(bool isGroupConversation)
{
#if PLATFORM_ANDROID
	JavaObject = AGMethodCallUtils::CallObjectMethod(JavaObject, "setGroupConversation", "(Z)Landroid/support/v4/app/NotificationCompat$MessagingStyle;", 
		isGroupConversation);
#endif

	return this;
}
