// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationBigTextStyle.h"
#include "Notifications/AGNotificationManager.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif	

UAGNotificationBigTextStyle::~UAGNotificationBigTextStyle()
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

UAGNotificationBigTextStyle * UAGNotificationBigTextStyle::CreateBigTextStyle(FString bigText)
{
	UAGNotificationBigTextStyle* style = NewObject<UAGNotificationBigTextStyle>();
#if PLATFORM_ANDROID
	style->JavaObject = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "getBigTextStyle",
		"(Ljava/lang/String;)Landroid/support/v4/app/NotificationCompat$BigTextStyle;", AGArrayConvertor::GetJavaString(bigText));
#endif
	return style;
}

UAGNotificationBigTextStyle * UAGNotificationBigTextStyle::SetBigContentTitle(FString title)
{
#if PLATFORM_ANDROID
	JavaObject = AGMethodCallUtils::CallObjectMethod(JavaObject, "setBigContentTitle",
		"(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$BigTextStyle;", AGArrayConvertor::GetJavaString(title));
#endif

	return this;
}

UAGNotificationBigTextStyle * UAGNotificationBigTextStyle::SetSummaryText(FString summary)
{
#if PLATFORM_ANDROID
	JavaObject = AGMethodCallUtils::CallObjectMethod(JavaObject, "setSummaryText",
		"(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$BigTextStyle;", AGArrayConvertor::GetJavaString(summary));
#endif

	return this;
}
