// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationBigPictureStyle.h"
#include "Notifications/AGNotificationManager.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif	

UAGNotificationBigPictureStyle::~UAGNotificationBigPictureStyle()
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

UAGNotificationBigPictureStyle * UAGNotificationBigPictureStyle::CreateBigPictureStyle(UTexture2D * bigPicture)
{
	UAGNotificationBigPictureStyle* style = NewObject<UAGNotificationBigPictureStyle>();

#if PLATFORM_ANDROID
	TArray<uint8> byteArray = AGMediaUtils::ByteArrayFromTexture(bigPicture);
	jbyteArray javaArray = AGArrayConvertor::ConvertToJByteArray(byteArray);

	style->JavaObject = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "getBigPictureStyle",
		"([BII)Landroid/support/v4/app/NotificationCompat$BigPictureStyle;", javaArray, bigPicture->GetSizeX(), bigPicture->GetSizeY());
#endif

	return style;
}

UAGNotificationBigPictureStyle * UAGNotificationBigPictureStyle::SetBigLargeIcon(UTexture2D * icon)
{

#if PLATFORM_ANDROID
	TArray<uint8> byteArray = AGMediaUtils::ByteArrayFromTexture(icon);
	jbyteArray javaArray = AGArrayConvertor::ConvertToJByteArray(byteArray);

	JavaObject = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "setBigLargeIcon",
		"(Landroid/support/v4/app/NotificationCompat$BigPictureStyle;[BII)Landroid/support/v4/app/NotificationCompat$BigPictureStyle;", 
		JavaObject, javaArray, icon->GetSizeX(), icon->GetSizeY());
#endif	

	return this;
}

UAGNotificationBigPictureStyle * UAGNotificationBigPictureStyle::SetBigContentTitle(FString title)
{
#if PLATFORM_ANDROID
	JavaObject = AGMethodCallUtils::CallObjectMethod(JavaObject, "setBigContentTitle", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$BigPictureStyle;", 
		AGArrayConvertor::GetJavaString(title));
#endif	

	return this;
}

UAGNotificationBigPictureStyle * UAGNotificationBigPictureStyle::SetSummaryText(FString text)
{
#if PLATFORM_ANDROID
	JavaObject = AGMethodCallUtils::CallObjectMethod(JavaObject, "setSummaryText", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$BigPictureStyle;", 
		AGArrayConvertor::GetJavaString(text));
#endif	

	return this;
}
