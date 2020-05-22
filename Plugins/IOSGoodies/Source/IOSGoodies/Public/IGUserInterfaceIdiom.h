// Copyright (c) 2018 Nineva Studios

#pragma once

UENUM(BlueprintType)
enum UserInterfaceIdiom
{
    Unspecified = -1 UMETA(DisplayName = "Unspecified"),
    Phone = 0 UMETA(DisplayName = "Phone"),
    Pad = 1 UMETA(DisplayName = "Pad"),
    AppleTV = 2 UMETA(DisplayName = "AppleTV"),
    CarPlay = 3 UMETA(DisplayName = "CarPlay"),
};
