// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "IGUserInterfaceIdiom.h"
#include "IGBatteryState.h"
#include "IGDeviceInfoBPL.generated.h"

/**
* Class to get device properties. Properties are obtained from UIDevice class
* See: https://developer.apple.com/reference/uikit/uidevice for more documentation.
*/
UCLASS()
class IOSGOODIES_API UIGDeviceInfo : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    
    /**
    * A Boolean value indicating whether multitasking is supported on the current device.
    *
    * @return - true if multitasking is supported; otherwise, false.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static bool IsMultitaskingSupported();
    
    /**
    * The name identifying the device.
    *
    * @return - the name identifying the device.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static FString GetName();
    
    /**
    * The name of the operating system running on the device represented by the receiver.
    *
    * @return - the name of the operating system running on the device represented by the receiver.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static FString GetSystemName();
    
    /**
    * The current version of the operating system.
    *
    * @return - the current version of the operating system.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static FString GetSystemVersion();
    
    /**
    * The model of the device.
    *
    * @return - the model of the device.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static FString GetModel();
    
    /**
    * The model of the device as a localized string.
    *
    * @return - the model of the device as a localized string.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static FString GetLocalizedModel();
    
    /**
    * The style of interface to use on the current device.
    *
    * @return - the style of interface to use on the current device.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static UserInterfaceIdiom GetUserInterfaceIdiom();
    
    /**
    * The alphanumeric string that uniquely identifies a device to the app’s vendor.
    *
    * @return - the alphanumeric string that uniquely identifies a device to the app’s vendor.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static FString GetUUID();
    
    /**
    * Change battery monitoring status.
    *
    * @param - true for enabling, false for disabling.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static void SetBatteryMonitoringEnabled(bool enabled);
    
    /**
    * A boolean value indicating whether battery monitoring is enabled (true) or not (false).
    *
    * @return - a boolean value indicating whether battery monitoring is enabled (true) or not (false).
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static bool IsBatteryMonitoringEnabled();
    
    /**
    * The battery charge level for the device.
    *
    * @return - the battery charge level for the device (0-100).
    * Returns -100, if battery monitoring is disabled, or a system error occurred.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static float GetBatteryLevel();
    
    /**
    * The battery state of the device.
    *
    * @return - the battery state of the device.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static BatteryState GetBatteryState();
    
    /**
    * Change proximity sensor monitoring status.
    *
    * @param - true for enabling, false for disabling.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static void SetProximityMonitoringEnabled(bool enabled);
    
    /**
    * A boolean value indicating whether proximity monitoring is enabled (true) or not (false).
    *
    * @return - a boolean value indicating whether proximity monitoring is enabled (true) or not (false).
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static bool IsProximityMonitoringEnabled();
    
    /**
    * A Boolean value indicating whether the proximity sensor is close to the user (true) or not (false).
    *
    * @return - a Boolean value indicating whether the proximity sensor is close to the user (true) or not (false).
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static bool ProximityState();
};
