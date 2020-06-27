// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotificationChannel.h"
#include "Notifications/AGNotificationManager.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#endif	

UAGNotificationChannel::~UAGNotificationChannel()
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => UAGNotification::~UAGNotification()"));
#if PLATFORM_ANDROID
	if (JavaNotificationChannelObject)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		Env->DeleteLocalRef(JavaNotificationChannelObject);
		JavaNotificationChannelObject = nullptr;
	}	
#endif
}

UAGNotificationChannel* UAGNotificationChannel::NewNotificationChannel(FString id, FString name, ChannelImportance importance)
{
	UAGNotificationChannel* channel = NewObject<UAGNotificationChannel>();

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		channel->JavaNotificationChannelObject = AGMethodCallUtils::CallStaticObjectMethod(UAGNotificationManager::NotificationHelperClassName,
			"getNotificationChannel", "(Ljava/lang/String;Ljava/lang/String;I)Landroid/app/NotificationChannel;",
			AGArrayConvertor::GetJavaString(id), AGArrayConvertor::GetJavaString(name), (int)importance);
#endif
	}

	return channel;
}

FString UAGNotificationChannel::GetId()
{
	FString result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			result =  AGMethodCallUtils::CallStringMethod(JavaNotificationChannelObject, "getId", "()Ljava/lang/String;");
		}		
#endif
	}

	return result;
}

UAGNotificationChannel * UAGNotificationChannel::SetBypassDnd(bool bypass)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			AGMethodCallUtils::CallVoidMethod(JavaNotificationChannelObject, "setBypassDnd", "(Z)V", bypass);
		}		
#endif
	}

	return this;
}

bool UAGNotificationChannel::CanBypassDnd()
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			return AGMethodCallUtils::CallBoolMethod(JavaNotificationChannelObject, "canBypassDnd", "()Z");
		}		
#endif
	}

	return false;
}

UAGNotificationChannel * UAGNotificationChannel::SetShowBadge(bool show)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			AGMethodCallUtils::CallVoidMethod(JavaNotificationChannelObject, "setShowBadge", "(Z)V", show);
		}		
#endif
	}

	return this;
}

bool UAGNotificationChannel::CanShowBadge()
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			return AGMethodCallUtils::CallBoolMethod(JavaNotificationChannelObject, "canShowBadge", "()Z");
		}		
#endif
	}

	return false;
}

UAGNotificationChannel * UAGNotificationChannel::SetEnableLights(bool enable)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			AGMethodCallUtils::CallVoidMethod(JavaNotificationChannelObject, "enableLights", "(Z)V", enable);
		}		
#endif
	}

	return this;
}

bool UAGNotificationChannel::ShouldShowLights()
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			return AGMethodCallUtils::CallBoolMethod(JavaNotificationChannelObject, "shouldShowLights", "()Z");
		}
#endif
	}

	return false;
}

UAGNotificationChannel * UAGNotificationChannel::SetEnableVibration(bool enable)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			AGMethodCallUtils::CallVoidMethod(JavaNotificationChannelObject, "enableVibration", "(Z)V", enable);
		}
#endif
	}

	return this;
}

bool UAGNotificationChannel::ShouldVibrate()
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			return AGMethodCallUtils::CallBoolMethod(JavaNotificationChannelObject, "shouldVibrate", "()Z");
		}
#endif
	}

	return false;
}

FAGAudioAttributes UAGNotificationChannel::GetAudioAttributes()
{
	FAGAudioAttributes attributes;	
	FAGAudioAttributesFlags flags;	
	
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			jobject javaAttributes = AGMethodCallUtils::CallObjectMethod(JavaNotificationChannelObject, "getAudioAttributes", "()Landroid/media/AudioAttributes;");

			attributes.ContentType = (AudioAttributesContentType) AGMethodCallUtils::CallIntMethod(javaAttributes, "getContentType", "()I");
			attributes.Usage = (AudioAttributesUsage) AGMethodCallUtils::CallIntMethod(javaAttributes, "getUsage", "()I");

			int flagsInt = AGMethodCallUtils::CallIntMethod(javaAttributes, "getFlags", "()I");
			flags.AudibilityEnforced = ((flagsInt & (1 << 0)) >> 0) == 1;
			flags.HwAvSync = ((flagsInt & (1 << 4)) >> 4) == 1;
			flags.LowLatency = ((flagsInt & (1 << 8)) >> 8) == 1;
			attributes.Flags = flags;
		}		
#endif
	}

	return attributes;
}

UAGNotificationChannel * UAGNotificationChannel::SetDescription(FString description)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			AGMethodCallUtils::CallVoidMethod(JavaNotificationChannelObject, "setDescription", "(Ljava/lang/String;)V", AGArrayConvertor::GetJavaString(description));
		}		
#endif
	}

	return this;
}

FString UAGNotificationChannel::GetDescription()
{
	FString result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			result =  AGMethodCallUtils::CallStringMethod(JavaNotificationChannelObject, "getDescription", "()Ljava/lang/String;");
		}		
#endif
	}

	return result;
}

UAGNotificationChannel* UAGNotificationChannel::SetImportance(ChannelImportance importance) 
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			AGMethodCallUtils::CallVoidMethod(JavaNotificationChannelObject, "setImportance", "(I)V", (int) importance);
		}		
#endif
	}

	return this;
}

ChannelImportance UAGNotificationChannel::GetImportance()
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			return (ChannelImportance) AGMethodCallUtils::CallIntMethod(JavaNotificationChannelObject, "getImportance", "()I");
		}		
#endif
	}

	return ChannelImportance::ImportanceDefault;
}

UAGNotificationChannel * UAGNotificationChannel::SetLightColor(FColor color)
{
	uint32 colorInt = color.ToPackedARGB();

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			AGMethodCallUtils::CallVoidMethod(JavaNotificationChannelObject, "setLightColor", "(I)V", colorInt);
		}		
#endif
	}

	return this;
}

FColor UAGNotificationChannel::GetLightColor()
{
	FColor color = FColor::Magenta;
		
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			int colorInt = AGMethodCallUtils::CallIntMethod(JavaNotificationChannelObject, "getLightColor", "()I");
			color = FColor(colorInt);
		}		
#endif
	}

	return color;
}

UAGNotificationChannel * UAGNotificationChannel::SetLockScreenVisibility(NotificationVisibility visibility)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			AGMethodCallUtils::CallVoidMethod(JavaNotificationChannelObject, "setLockscreenVisibility", "(I)V", (int) visibility);
		}		
#endif
	}

	return this;
}

NotificationVisibility UAGNotificationChannel::GetLockScreenVisibility()
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			return (NotificationVisibility) AGMethodCallUtils::CallIntMethod(JavaNotificationChannelObject, "getLockscreenVisibility", "()I");
		}		
#endif
	}

	return NotificationVisibility::VisibilityPrivate;
}

FString UAGNotificationChannel::GetName()
{
	FString result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			result =  AGMethodCallUtils::CallStringMethod(JavaNotificationChannelObject, "getName", "()Ljava/lang/CharSequence;");
		}		
#endif
	}

	return result;
}

FString UAGNotificationChannel::GetSoundPath()
{
	FString result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			jobject soundUri = AGMethodCallUtils::CallObjectMethod(JavaNotificationChannelObject, "getSound", "()Landroid/net/Uri;");
			result = AGMethodCallUtils::CallStringMethod(soundUri, "getPath", "()Ljava/lang/String;");
		}		
#endif
	}

	return result;
}

UAGNotificationChannel * UAGNotificationChannel::SetVibrationPattern(TArray<float> pattern)
{
	TArray<long> longArray;
	for (int i = 0; i < pattern.Num(); i++)
	{
		longArray.Add((long) FMath::RoundHalfFromZero(pattern[i] * 1000));
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			jlongArray jLongArray = AGArrayConvertor::ConvertToJLongArray(longArray);
			AGMethodCallUtils::CallVoidMethod(JavaNotificationChannelObject, "setVibrationPattern", "([J)V", jLongArray);
		}		
#endif
	}

	return this;
}

TArray<float> UAGNotificationChannel::GetVibrationPattern()
{
	TArray<float> result;
		
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			jlongArray javaArray = static_cast<jlongArray>(AGMethodCallUtils::CallObjectMethod(JavaNotificationChannelObject, "getVibrationPattern", "()[J"));
			TArray<long> longArray = AGArrayConvertor::ConvertToLongArray(javaArray);

			for (int i = 0; i < longArray.Num(); i++)
			{
				result.Add(((float)longArray[i]) / 1000);
			}
		}		
#endif
	}

	return result;
}

UAGNotificationChannel* UAGNotificationChannel::SetSound(FString filePath, FAGAudioAttributes attributes)
{
	int flagsInt = 0;
	if (attributes.Flags.AudibilityEnforced)
	{
		flagsInt = flagsInt | 1;
	}
	if (attributes.Flags.HwAvSync)
	{
		flagsInt = flagsInt | 16;
	}
	if (attributes.Flags.LowLatency)
	{
		flagsInt = flagsInt | 256;
	}

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			AGMethodCallUtils::CallStaticVoidMethod(UAGNotificationManager::NotificationHelperClassName,
				"setChannelSound", "(Landroid/app/NotificationChannel;Ljava/lang/String;III)V",
				JavaNotificationChannelObject, AGArrayConvertor::GetJavaString(filePath), (int) attributes.ContentType, (int) attributes.Usage, flagsInt);
		}		
#endif
	}

	return this;
}

FString UAGNotificationChannel::GetGroupId()
{
	FString result;

	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			result = AGMethodCallUtils::CallStringMethod(JavaNotificationChannelObject, "getGroup", "()Ljava/lang/String;");
		}		
#endif
	}

	return result;
}

UAGNotificationChannel * UAGNotificationChannel::SetGroup(FString groupId)
{
	if (UAGNotificationManager::AreNotificationChannelsSupported())
	{
#if PLATFORM_ANDROID
		if (JavaNotificationChannelObject)
		{
			AGMethodCallUtils::CallVoidMethod(JavaNotificationChannelObject, "setGroup", "(Ljava/lang/String;)V", AGArrayConvertor::GetJavaString(groupId));
		}		
#endif
	}

	return this;
}
