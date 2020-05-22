// Copyright (c) 2018 Nineva Studios

#include "IGDeviceInfoBPL.h"

bool UIGDeviceInfo::IsMultitaskingSupported() {
    bool result = false;
#if PLATFORM_IOS
    result = [[UIDevice currentDevice] isMultitaskingSupported];
#endif
    return result;
}

FString UIGDeviceInfo::GetName() {
	FString result = FString(TEXT(""));
#if PLATFORM_IOS
    NSString *name = [[UIDevice currentDevice] name];
	result = FString(name);
#endif
    return result;
}

FString UIGDeviceInfo::GetSystemName() {
	FString result = FString(TEXT(""));
#if PLATFORM_IOS
    NSString *systemName = [[UIDevice currentDevice] systemName];
	result = FString(systemName);
#endif
    return result;
}

FString UIGDeviceInfo::GetSystemVersion() {
	FString result = FString(TEXT(""));
#if PLATFORM_IOS
    NSString *systemVersion = [[UIDevice currentDevice] systemVersion];
	result = FString(systemVersion);
#endif
    return result;
}

FString UIGDeviceInfo::GetModel() {
	FString result = FString(TEXT(""));
#if PLATFORM_IOS
    NSString *model = [[UIDevice currentDevice] model];
	result = FString(model);
#endif
    return result;
}

FString UIGDeviceInfo::GetLocalizedModel() {
	FString result = FString(TEXT(""));
#if PLATFORM_IOS
    NSString *localizedModel = [[UIDevice currentDevice] localizedModel];
	result = FString(localizedModel);
#endif
    return result;
}

UserInterfaceIdiom UIGDeviceInfo::GetUserInterfaceIdiom() {
    UserInterfaceIdiom idiom = UserInterfaceIdiom(Unspecified);
#if PLATFORM_IOS
    int result = [[UIDevice currentDevice] userInterfaceIdiom];
    idiom = (UserInterfaceIdiom) result;
#endif
    return idiom;
}

FString UIGDeviceInfo::GetUUID() {
	FString result = FString(TEXT(""));
#if PLATFORM_IOS
    NSString *UUIDString = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
	result = FString(UUIDString);
#endif
    return result;
}

void UIGDeviceInfo::SetBatteryMonitoringEnabled(bool enabled) {
#if PLATFORM_IOS
    [[UIDevice currentDevice] setBatteryMonitoringEnabled:enabled];
#endif
}

bool UIGDeviceInfo::IsBatteryMonitoringEnabled() {
    bool result = false;
#if PLATFORM_IOS
    result = [[UIDevice currentDevice] isBatteryMonitoringEnabled];
#endif
    return result;
}

float UIGDeviceInfo::GetBatteryLevel() {
    float result = 0;
#if PLATFORM_IOS
    result = (float) [[UIDevice currentDevice] batteryLevel] * 100;
#endif
    return result;
}

BatteryState UIGDeviceInfo::GetBatteryState() {
    BatteryState state = BatteryState::Unknown;
#if PLATFORM_IOS
    int result = [[UIDevice currentDevice] batteryState];
    state = static_cast<BatteryState>(result);
#endif
    return state;
}

void UIGDeviceInfo::SetProximityMonitoringEnabled(bool enabled) {
#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^
    {
        [[UIDevice currentDevice] setProximityMonitoringEnabled:enabled];
    });
#endif
}

bool UIGDeviceInfo::IsProximityMonitoringEnabled() {
    bool result = false;
#if PLATFORM_IOS
    result = [[UIDevice currentDevice] isProximityMonitoringEnabled];
#endif
    return result;
}

bool UIGDeviceInfo::ProximityState() {
    bool result = false;
#if PLATFORM_IOS
    result = [[UIDevice currentDevice] proximityState];
#endif
    return result;
}
