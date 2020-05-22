// Copyright (c) 2018 Nineva Studios

#pragma once

UENUM(BlueprintType)
enum NotificationType
{
	Error = 0 UMETA(DisplayName = "Error"),
	Warning = 1 UMETA(DisplayName = "Warning"),
	Success = 2 UMETA(DisplayName = "Success"),
};
