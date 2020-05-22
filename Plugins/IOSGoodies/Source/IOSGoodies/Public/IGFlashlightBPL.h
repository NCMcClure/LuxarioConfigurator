// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "IGFlashlightBPL.generated.h"

/*
 * Class for flashlight functions.
 */
UCLASS()
class IOSGOODIES_API UIGFlashlight : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	/**
	 * Toggle the flashlight.
	 *
	 * @param enable - whether to enable or disable the flashlight
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void EnableFlashlight(bool enable);
	
	/**
	 * Indicate whether current device has a flashlight.
	 *
	 * @return true if the device has flashlight, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static bool DeviceHasFlashlight();
	
	/**
	 * Enable flashlight with the provided intensity.
	 *
	 * @param level - intensity of the flashlight to set. Clamped between 0 and 1
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void SetFlashlightLevel(float level);
};
