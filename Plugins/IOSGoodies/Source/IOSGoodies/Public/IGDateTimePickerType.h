// Copyright (c) 2018 Nineva Studios

#pragma once

UENUM(BlueprintType)
enum DateTimePickerType
{
	/** Picker for selecting date. */
	DatePicker = 0 UMETA(DisplayName = "Date"),
	/** Picker for selecting time. */
	TimePicker = 1 UMETA(DisplayName = "Time"),
	/** Picker for selecting date and time. */
	DateTimePicker = 2 UMETA(DisplayName = "DateTime"),
	/** Picker for setting up countdown timer. */
	CountdownTimer = 3 UMETA(DisplayName = "CountdownTimer"),
};
