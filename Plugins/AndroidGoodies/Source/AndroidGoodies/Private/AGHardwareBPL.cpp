// Copyright (c) 2019 Nineva Studios

#include "AGHardwareBPL.h"
#include "AGDeviceInfoBPL.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"
#include "Android/Utils/AGArrayConvertor.h"
#endif

static const ANSICHAR* AGHardwareClassName = "com/ninevastudios/androidgoodies/AGHardware";

void UAGHardwareBPL::EnableFlashlight(bool enable)
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "enableFlashlight", "(Landroid/app/Activity;Z)V", FJavaWrapper::GameActivityThis, enable);
#endif
}

bool UAGHardwareBPL::HasVibrator()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "hasVibrator", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return false;
}

bool UAGHardwareBPL::HasAmplitudeControl()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "hasAmplitudeControl", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return false;
}

void UAGHardwareBPL::Vibrate(float duration)
{
	long durationLong = (long) FMath::RoundHalfFromZero(duration * 1000);

	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => Duration: %d"), durationLong);

#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "vibrate", "(Landroid/app/Activity;J)V", FJavaWrapper::GameActivityThis, (jlong) durationLong);
#endif
}

void UAGHardwareBPL::VibrateWithPattern(TArray<float> pattern, int repeatFrom)
{
	TArray<long> longArray;
	for (int i = 0; i < pattern.Num(); i++)
	{
		longArray.Add((long) FMath::RoundHalfFromZero(pattern[i] * 1000));
	}

#if PLATFORM_ANDROID
	jlongArray jLongArray = AGArrayConvertor::ConvertToJLongArray(longArray);
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "vibrate", "(Landroid/app/Activity;[JI)V", 
		FJavaWrapper::GameActivityThis, jLongArray, repeatFrom);
#endif
}

bool UAGHardwareBPL::AreVibrationEffectsSupported()
{
	return UAGDeviceInfo::GetSdkInt() >= 26;
}

void UAGHardwareBPL::VibrateWithEffect(UAGVibrationEffect* vibrationEffect)
{
#if PLATFORM_ANDROID
	if (!vibrationEffect->JavaObject)
	{
		UE_LOG(LogTemp, Error, TEXT("ANDROIDGOODIES => Vibration Effect was not created successfully, returning..."));
		return;
	}

	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "vibrate", "(Landroid/app/Activity;Landroid/os/VibrationEffect;)V", 
		FJavaWrapper::GameActivityThis, vibrationEffect->JavaObject);
#endif
}

void UAGHardwareBPL::VibrateWithEffectAndAttributes(UAGVibrationEffect* vibrationEffect, FAGAudioAttributes audioAttributes)
{
	int flagsInt = 0;
	if (audioAttributes.Flags.AudibilityEnforced)
	{
		flagsInt = flagsInt | 1;
	}
	if (audioAttributes.Flags.HwAvSync)
	{
		flagsInt = flagsInt | 16;
	}
	if (audioAttributes.Flags.LowLatency)
	{
		flagsInt = flagsInt | 256;
	}

	UE_LOG(LogTemp, Error, TEXT("ANDROIDGOODIES => Flags: %d"), flagsInt);

#if PLATFORM_ANDROID
	if (!vibrationEffect->JavaObject)
	{
		UE_LOG(LogTemp, Error, TEXT("ANDROIDGOODIES => Vibration Effect was not created successfully, returning..."));
		return;
	}

	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "vibrate", "(Landroid/app/Activity;Landroid/os/VibrationEffect;III)V",
		FJavaWrapper::GameActivityThis, vibrationEffect->JavaObject, flagsInt, (int) audioAttributes.Usage, (int) audioAttributes.ContentType);
#endif
}

void UAGHardwareBPL::StopVibration()
{
#if PLATFORM_ANDROID
	AGMethodCallUtils::CallStaticVoidMethod(AGHardwareClassName, "stopVibration", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

int UAGHardwareBPL::ComputeRemainingChargeTime()
{
#if PLATFORM_ANDROID
	return (int) (AGMethodCallUtils::CallStaticLongMethod(AGHardwareClassName, "computeRemainingChargeTime", "(Landroid/app/Activity;)J", FJavaWrapper::GameActivityThis) / 1000);
#endif

	return -1;
}

int UAGHardwareBPL::GetBatteryCapacity()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryCapacity", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

int UAGHardwareBPL::GetBatteryChargeCounter()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryChargeCounter", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

int UAGHardwareBPL::GetAverageBatteryCurrent()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getAverageBatteryCurrent", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

int UAGHardwareBPL::GetImmediateBatteryCurrent()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getImmediateBatteryCurrent", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

int UAGHardwareBPL::GetBatteryEnergyCounter()
{
#if PLATFORM_ANDROID
	return (int) AGMethodCallUtils::CallStaticLongMethod(AGHardwareClassName, "getBatteryEnergyCounter", "(Landroid/app/Activity;)J", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

BatteryStatus UAGHardwareBPL::GetBatteryStatus()
{
#if PLATFORM_ANDROID
	int jBatteryStatus = AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryStatus", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
	return static_cast<BatteryStatus>(jBatteryStatus - 1);
#endif

	return BatteryStatus::UnknownStatus;
}

bool UAGHardwareBPL::IsBatteryLow()
{
	if (UAGDeviceInfo::GetSdkInt() < 28)
	{
		return false;
	}

#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "isBatteryLow", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return false;
}

BatteryHealth UAGHardwareBPL::GetBatteryHealth()
{
#if PLATFORM_ANDROID
	int jBatterHealthId = AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryHealth", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
	return static_cast<BatteryHealth>(jBatterHealthId - 1);
#endif

	return BatteryHealth::UnknownHealth;
}

int UAGHardwareBPL::GetBatteryLevel()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryLevel", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

BatteryPluggedState UAGHardwareBPL::GetBatteryPluggedState()
{
#if PLATFORM_ANDROID
	return (BatteryPluggedState)AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryPluggedState", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return BatteryPluggedState::OnBattery;
}

bool UAGHardwareBPL::IsBatteryPresent()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticBoolMethod(AGHardwareClassName, "isBatteryPresent", "(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif

	return false;
}

int UAGHardwareBPL::GetBatteryScale()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryScale", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return -1;
}

FString UAGHardwareBPL::GetBatteryTechnology()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticStringMethod(AGHardwareClassName, "getBatteryTechnology", "(Landroid/app/Activity;)Ljava/lang/String;", FJavaWrapper::GameActivityThis);
#endif

	return "Unknown";
}

int UAGHardwareBPL::GetBatteryTemperature()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryTemperature", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return INT32_MIN;
}

int UAGHardwareBPL::GetBatteryVoltage()
{
#if PLATFORM_ANDROID
	return AGMethodCallUtils::CallStaticIntMethod(AGHardwareClassName, "getBatteryVoltage", "(Landroid/app/Activity;)I", FJavaWrapper::GameActivityThis);
#endif

	return 0;
}
