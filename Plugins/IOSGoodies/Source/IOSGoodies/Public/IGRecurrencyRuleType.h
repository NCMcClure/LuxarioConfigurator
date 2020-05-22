// Copyright (c) 2019 Nineva Studios

#pragma once

UENUM(BlueprintType)
enum RecurrencyRuleType
{
    Daily = 0 UMETA(DisplayName = "Daily"),
    Weekly = 1 UMETA(DisplayName = "Weekly"),
    Monthly = 2 UMETA(DisplayName = "Monthly"),
    Yearly = 3 UMETA(DisplayName = "Yearly")
};
