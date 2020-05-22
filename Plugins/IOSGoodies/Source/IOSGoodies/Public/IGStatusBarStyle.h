// Copyright (c) 2018 Nineva Studios

#pragma once

#include "IGStatusBarStyle.generated.h"

UENUM(BlueprintType)
enum StatusBarStyle
{
    /** A dark status bar, intended for use on light backgrounds */
    BarStyleDefault = 0 UMETA(DisplayName = "Default style"),
    /** A light status bar, intended for use on dark backgrounds. (iOS 7.0+) */
    BarStyleLightContent = 1 UMETA(DisplayName = "Light Content Style"),
    /** A dark status bar, intended for use on light backgrounds. (iOS 13.0+) */
    BarStyleDarkContent = 3 UMETA(DisplayName = "Dark Content Style"),
};
