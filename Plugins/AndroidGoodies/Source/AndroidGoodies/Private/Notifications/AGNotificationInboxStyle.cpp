// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationInboxStyle.h"
#include "Notifications/AGNotificationManager.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif	

UAGNotificationInboxStyle::~UAGNotificationInboxStyle()
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => UAGNotificationInboxStyle::~UAGNotificationInboxStyle()"));
#if PLATFORM_ANDROID
	if (JavaObject)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		Env->DeleteLocalRef(JavaObject);
		JavaObject = nullptr;
	}	
#endif
}

UAGNotificationInboxStyle* UAGNotificationInboxStyle::CreateInboxStyle()
{
	UAGNotificationInboxStyle* style = NewObject<UAGNotificationInboxStyle>();
#if PLATFORM_ANDROID
	style->JavaObject = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "getInboxStyle",
		"()Landroid/support/v4/app/NotificationCompat$InboxStyle;");
#endif
	return style;
}

UAGNotificationInboxStyle * UAGNotificationInboxStyle::AddLine(FString line)
{
#if PLATFORM_ANDROID
	JavaObject = AGMethodCallUtils::CallObjectMethod(JavaObject, "addLine",
		"(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$InboxStyle;", AGArrayConvertor::GetJavaString(line));
#endif

	return this;
}

UAGNotificationInboxStyle * UAGNotificationInboxStyle::SetBigContentTitle(FString title)
{
#if PLATFORM_ANDROID
	JavaObject = AGMethodCallUtils::CallObjectMethod(JavaObject, "setBigContentTitle",
		"(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$InboxStyle;", AGArrayConvertor::GetJavaString(title));
#endif

	return this;
}

UAGNotificationInboxStyle * UAGNotificationInboxStyle::SetSummaryText(FString summary)
{
#if PLATFORM_ANDROID
	JavaObject = AGMethodCallUtils::CallObjectMethod(JavaObject, "setSummaryText",
		"(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$InboxStyle;", AGArrayConvertor::GetJavaString(summary));
#endif

	return this;
}
