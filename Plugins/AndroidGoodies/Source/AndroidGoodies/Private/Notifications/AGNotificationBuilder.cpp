// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationBuilder.h"
#include "Notifications/AGNotificationManager.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#include "Android/Utils/AGMediaUtils.h"
#endif	

static FString GetCategoryString(NotificationCategory category)
{
	FString categoryString;
	switch (category)
	{
	case CategoryAlarm:
		categoryString = "alarm";
		break;
	case CategoryCall:
		categoryString = "call";
		break;
	case CategoryEmail:
		categoryString = "email";
		break;
	case CategoryError:
		categoryString = "error";
		break;
	case CategoryEvent:
		categoryString = "event";
		break;
	case CategoryMessage:
		categoryString = "msg";
		break;
	case CategoryNavigation:
		categoryString = "navigation";
		break;
	case CategoryProgress:
		categoryString = "progress";
		break;
	case CategoryPromo:
		categoryString = "promo";
		break;
	case CategoryRecommendation:
		categoryString = "recommendation";
		break;
	case CategoryReminder:
		categoryString = "reminder";
		break;
	case CategoryService:
		categoryString = "service";
		break;
	case CategorySocial:
		categoryString = "social";
		break;
	case CategoryStatus:
		categoryString = "status";
		break;
	case CategorySystem:
		categoryString = "system";
		break;
	case CategoryTransport:
		categoryString = "transport";
		break;
	default:
		break;
	}

	return categoryString;
}

UAGNotificationBuilder::~UAGNotificationBuilder()
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => UAGNotificationBuilder::~UAGNotificationBuilder()"));

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteLocalRef(javaBuilder);
	javaBuilder = nullptr;
#endif
}

UAGNotificationBuilder* UAGNotificationBuilder::NewNotificationBuilder(FString channelId, TMap<FString, FString> additionalData)
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => UAGNotificationBuilder::InitializeWithChannel()"));

	TArray<FString> keys;
	TArray<FString> result;

	if (additionalData.Num() > 0)
	{
		int count = additionalData.GetKeys(keys);
		
		for (int i = 0; i < count; i++)
		{
			FString key = keys[i];
			result.Add(key);
			result.Add(additionalData[key]);
		}
	}

	UAGNotificationBuilder* builder = NewObject<UAGNotificationBuilder>();	

#if PLATFORM_ANDROID
	result.Add("AndroidGoodies");
	result.Add("Best Plugin Ever :)");

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jobjectArray stringArray = AGArrayConvertor::ConvertToJStringArray(result);

	builder->javaBuilder = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "getNotificationBuilder",
		"(Landroid/app/Activity;Ljava/lang/String;[Ljava/lang/String;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(channelId), stringArray);
#endif	

	return builder;
}

UAGNotification* UAGNotificationBuilder::Build()
{
	UAGNotification* notification = NewObject<UAGNotification>();
#if PLATFORM_ANDROID
	jobject jnotification = AGMethodCallUtils::CallObjectMethod(javaBuilder, "build", "()Landroid/app/Notification;");
	notification->Init(jnotification);
#endif
	return notification;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetTitle(FString title)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setContentTitle", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		AGArrayConvertor::GetJavaString(title));
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetText(FString text)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setContentText", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;",
		AGArrayConvertor::GetJavaString(text));
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetSmallIcon(FString fileName)
{
#if PLATFORM_ANDROID
	int resourceId = AGMethodCallUtils::CallStaticIntMethod(UAGNotificationManager::NotificationHelperClassName, "getIconId", "(Landroid/app/Activity;Ljava/lang/String;)I", 
		FJavaWrapper::GameActivityThis, AGArrayConvertor::GetJavaString(fileName));

	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Icon ID: %d. This value should NOT be 0."), resourceId);

	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setSmallIcon", "(I)Landroid/support/v4/app/NotificationCompat$Builder;", resourceId);
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetAutoCancel(bool autoCancel)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setAutoCancel", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;", autoCancel);
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetBadgeIconType(NotificationBadgeIconType badgeIconType)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setBadgeIconType", "(I)Landroid/support/v4/app/NotificationCompat$Builder;", (int) badgeIconType);
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetCategory(NotificationCategory category)
{
	FString categoryString = GetCategoryString(category);

	if (categoryString.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("ANDROIDGOODIES => UAGNotificationBuilder::SetCategory() - Category is wrong."));
		return this;
	}

#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setCategory", "(Ljava/lang/String;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		AGArrayConvertor::GetJavaString(categoryString));
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetColor(FColor color)
{
	uint32 colorInt = color.ToPackedARGB();

#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "setNotificationColor",
		"(Landroid/support/v4/app/NotificationCompat$Builder;I)Landroid/support/v4/app/NotificationCompat$Builder;", 
		javaBuilder, colorInt);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetColorized(bool colorized)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setColorized", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;", colorized);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetContentInfo(FString text)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setContentInfo", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;",
		AGArrayConvertor::GetJavaString(text));
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetDefaults(FAGNotificationDefaults defaults)
{
	int flagsInt = 0;
	if (defaults.Lights)
	{
		flagsInt = flagsInt | 4;
	}
	if (defaults.Sound)
	{
		flagsInt = flagsInt | 1;
	}
	if (defaults.Vibrate)
	{
		flagsInt = flagsInt | 2;
	}

#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setDefaults", "(I)Landroid/support/v4/app/NotificationCompat$Builder;", flagsInt);
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetGroup(FString groupKey)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setGroup", "(Ljava/lang/String;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		AGArrayConvertor::GetJavaString(groupKey));
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetGroupAlertBehaviour(NotificationGroupAlert behaviour)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setGroupAlertBehavior", "(I)Landroid/support/v4/app/NotificationCompat$Builder;", behaviour);
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetGroupSummary(bool summary)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setGroupSummary", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;", summary);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetLargeIcon(UTexture2D * icon)
{
#if PLATFORM_ANDROID
	TArray<uint8> byteArray = AGMediaUtils::ByteArrayFromTexture(icon);
	jbyteArray javaArray = AGArrayConvertor::ConvertToJByteArray(byteArray);

	javaBuilder = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "setNotificationLargeIcon",
		"(Landroid/support/v4/app/NotificationCompat$Builder;[BII)Landroid/support/v4/app/NotificationCompat$Builder;", 
		javaBuilder, javaArray, icon->GetSizeX(), icon->GetSizeY());
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetLights(FColor color, int inMilliSeconds, int outMilliSeconds)
{
	uint32 colorInt = color.ToPackedARGB();

#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setLights", "(III)Landroid/support/v4/app/NotificationCompat$Builder;", colorInt, inMilliSeconds, outMilliSeconds);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetLocalOnly(bool localOnly)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setLocalOnly", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;", localOnly);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetNumber(int number)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setNumber", "(I)Landroid/support/v4/app/NotificationCompat$Builder;", number);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetOngoing(bool ongoing)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setOngoing", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;", ongoing);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetAlertOnce(bool alertOnce)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setOnlyAlertOnce", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;", alertOnce);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetPriority(NotificationPriority priority)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setPriority", "(I)Landroid/support/v4/app/NotificationCompat$Builder;", (int) priority);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetProgress(int current, int max, bool indeterminate)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setProgress", "(IIZ)Landroid/support/v4/app/NotificationCompat$Builder;", max, current, indeterminate);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetPublicVersion(UAGNotification * notification)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setPublicVersion", "(Landroid/app/Notification;)Landroid/support/v4/app/NotificationCompat$Builder;",
		notification->JavaNotificationObject);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetShortcutId(FString id)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setShortcutId", "(Ljava/lang/String;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		AGArrayConvertor::GetJavaString(id));
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetShowWhen(bool showWhen)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setShowWhen", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;", showWhen);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetSortKey(FString key)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setSortKey", "(Ljava/lang/String;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		AGArrayConvertor::GetJavaString(key));
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetSound(FString path)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "setNotificationSound",
		"(Landroid/support/v4/app/NotificationCompat$Builder;Ljava/lang/String;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		javaBuilder, AGArrayConvertor::GetJavaString(path));
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetSubText(FString text)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setSubText", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		AGArrayConvertor::GetJavaString(text));
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetTicker(FString text)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setTicker", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		AGArrayConvertor::GetJavaString(text));
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetTimeoutAfter(int milliSeconds)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setTimeoutAfter", "(J)Landroid/support/v4/app/NotificationCompat$Builder;", 
		static_cast<jlong>((long) milliSeconds));
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetUsesChronometer(bool usesChronometer)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setUsesChronometer", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;", usesChronometer);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetVibrate(TArray<float> pattern)
{
	TArray<long> longArray;
	for (int i = 0; i < pattern.Num(); i++)
	{
		longArray.Add((long) FMath::RoundHalfFromZero(pattern[i] * 1000));
	}
#if PLATFORM_ANDROID
	jlongArray jLongArray = AGArrayConvertor::ConvertToJLongArray(longArray);
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setVibrate", "([J)Landroid/support/v4/app/NotificationCompat$Builder;", jLongArray);
#endif

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetVisibility(NotificationVisibility visibility)
{
#if PLATFORM_ANDROID
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setVisibility", "(I)Landroid/support/v4/app/NotificationCompat$Builder;", (int) visibility);
#endif	

	return this;
}

UAGNotificationBuilder* UAGNotificationBuilder::SetWhen(FDateTime dateTime)
{
	auto dateLong = dateTime.ToUnixTimestamp() * 1000;

#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setWhen", "(J)Landroid/support/v4/app/NotificationCompat$Builder;", 
		static_cast<jlong>(dateLong));
#endif

	return this;
}

UAGNotificationBuilder * UAGNotificationBuilder::SetBigTextStyle(UAGNotificationBigTextStyle * style)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setStyle", "(Landroid/support/v4/app/NotificationCompat$Style;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		style->JavaObject);
#endif

	return this;
}

UAGNotificationBuilder * UAGNotificationBuilder::SetMessagingStyle(UAGNotificationMessageStyle * style)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setStyle", "(Landroid/support/v4/app/NotificationCompat$Style;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		style->JavaObject);
#endif

	return this;
}

UAGNotificationBuilder * UAGNotificationBuilder::SetBigPictureStyle(UAGNotificationBigPictureStyle * style)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setStyle", "(Landroid/support/v4/app/NotificationCompat$Style;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		style->JavaObject);
#endif

	return this;
}

UAGNotificationBuilder * UAGNotificationBuilder::SetInboxStyle(UAGNotificationInboxStyle * style)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallObjectMethod(javaBuilder, "setStyle", "(Landroid/support/v4/app/NotificationCompat$Style;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		style->JavaObject);
#endif

	return this;
}

UAGNotificationBuilder * UAGNotificationBuilder::AddOpenUrlAction(FString iconName, FString title, FString url)
{
#if PLATFORM_ANDROID 
	javaBuilder = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName, "addOpenUrlAction",
		"(Landroid/app/Activity;Landroid/support/v4/app/NotificationCompat$Builder;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Landroid/support/v4/app/NotificationCompat$Builder;", 
		FJavaWrapper::GameActivityThis, javaBuilder, AGArrayConvertor::GetJavaString(iconName), AGArrayConvertor::GetJavaString(title), AGArrayConvertor::GetJavaString(url));
#endif

	return this;
}
