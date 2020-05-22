// Copyright (c) 2018 Nineva Studios

#pragma once

UENUM(BlueprintType)
enum class BatteryState : uint8
{
    Unknown = 0 UMETA(DisplayName = "Unknown"),
    Unplugged = 1 UMETA(DisplayName = "Unplugged"),
    Charging = 2 UMETA(DisplayName = "Charging"),
    Full = 3 UMETA(DisplayName = "Full"),
};
