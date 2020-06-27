// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGVibrationEffect.h"
#include "AGAudioAttributes.h"
#include "Enums/AGBatteryStatus.h"
#include "Enums/AGBatteryHealth.h"
#include "Enums/AGBatteryPluggedState.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGHardwareBPL.generated.h"

UCLASS()
class ANDROIDGOODIES_API UAGHardwareBPL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	* Toggle flashlight ON/OFF
	*
	* @param enable - whether to turn the flashlight ON or OFF.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void EnableFlashlight(bool enable);

	/**
	* Check whether the device has a vibrator.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasVibrator();

	/**
	* Check whether the vibrator has amplitude control.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasAmplitudeControl();

	/**
	* Vibrate constantly for the specified period of time.
	*
	* @param duration - duration in seconds.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void Vibrate(float duration);

	/**
	* Vibrate with a given pattern.
	*
	* @param pattern - an array of the floating point values that are the durations for which to turn on or off the vibrator in seconds. 
	* The first value indicates the number of seconds to wait before turning the vibrator on. The next value indicates the number of seconds 
	* for which to keep the vibrator on before turning it off. Subsequent values alternate between durations in seconds to turn the vibrator off or to turn the vibrator on.
	* @param repeatFrom - the index of the element in the intervals array, from which to repeat the sequence, or -1 for a single playback.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void VibrateWithPattern(TArray<float> pattern, int repeatFrom);

	/**
	* Check if device's OS supports new vibration effects
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool AreVibrationEffectsSupported();

	/**
	* Vibrate with custom vibration effect.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void VibrateWithEffect(UAGVibrationEffect* vibrationEffect);

	/**
	* Vibrate with custom vibration effect and audio attributes.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void VibrateWithEffectAndAttributes(UAGVibrationEffect* vibrationEffect, FAGAudioAttributes audioAttributes);

	/**
	* Cancel the current vibration.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void StopVibration();

	/**
	* The remaining battery charge time in seconds.
	* Returns -1, on OS version <28 and if something went wrong.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int ComputeRemainingChargeTime();

	/**
	* The current battery capacity (0 - 100 %). Returns -1, if something went wrong.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryCapacity();

	/**
	* The battery capacity in micro ampere-hours, as an integer.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryChargeCounter();

	/**
	* The average battery current in micro amperes, as an integer.
	* Positive values indicate net current entering the battery from a charge source,
	* negative values indicate net current discharging from the battery.
	* The time period over which the average is computed may depend on the fuel gauge hardware and its configuration.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetAverageBatteryCurrent();

	/**
	* Instantaneous battery current in micro amperes, as an integer.
	* Positive values indicate net current entering the battery from a charge source,
	* negative values indicate net current discharging from the battery.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetImmediateBatteryCurrent();

	/**
	* Battery remaining energy in nano watt-hours. -1 if not supported.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryEnergyCounter();

	/**
	* Battery charge status.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static BatteryStatus GetBatteryStatus();

	/**
	* Whether the battery is currently considered to be low,
	* that is whether an Intent.ActionBatteryLow broadcast has been sent.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool IsBatteryLow();

	/**
	* Current health constant.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static BatteryHealth GetBatteryHealth();

	/**
	* The current battery level, from 0 to Scale. -1 if something went wrong.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryLevel();

	/**
	* One of the BatteryPluggedState values indicating whether the device is plugged in to a power source.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static BatteryPluggedState GetBatteryPluggedState();

	/**
	* Whether a battery is present.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool IsBatteryPresent();

	/**
	* The maximum battery level. -1 if something went wrong.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryScale();

	/**
	* The technology of the current battery.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static FString GetBatteryTechnology();

	/**
	* The current battery temperature in the tenth parts of a Celcius degree.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryTemperature();

	/**
	* The current battery voltage level in mV.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static int GetBatteryVoltage();
};