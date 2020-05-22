// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "IGDateTimePickerBPL.generated.h"

DECLARE_DYNAMIC_DELEGATE_FiveParams(FOnDateTimeSetDelegate, int, Year, int, Month, int, Day, int, Hour, int, Minute);
DECLARE_DYNAMIC_DELEGATE(FOnDateTimeCancelDelegate);

UCLASS()
class IOSGOODIES_API UIGDateTimePickerBPL : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Show the default iOS date picker.
	* @param initialDate - initial date value for date picker dialog
	* @param onDateSetCallback - callback function that is called when user is done setting a new date and date picker dialog has closed
	* @param onCancelCallback - callback function that is called when user cancelled date picker dialog
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onDateSetCallback, onCancelCallback"))
	static void ShowDatePicker(FDateTime initialDate, const FOnDateTimeSetDelegate& onDateSetCallback, const FOnDateTimeCancelDelegate& onCancelCallback);

	/**
	* Show the default iOS date picker, but with limited date range.
	* @param initialDate - initial date value for date picker dialog
	* @param fromDate - minimum value in date picker dialog that can be selected
	* @param toDate - maximum value in date picker dialog that can be selected
	* @param onDateSetCallback - callback function that is called when user is done setting a new date and date picker dialog has closed
	* @param onCancelCallback - callback function that is called when user cancelled date picker dialog
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onDateTimeSetCallback, onCancelCallback"))
	static void ShowDatePickerWithLimits(FDateTime initialDate, FDateTime fromDate, FDateTime toDate,
		const FOnDateTimeSetDelegate& onDateSetCallback, const FOnDateTimeCancelDelegate& onCancelCallback);

	/**
	* Show the default iOS time picker.
	* @param hour - initial hour value for time picker dialog
	* @param minute - initial minute value for time picker dialog
	* @param onTimeSetCallback - callback function that is called when user is done setting a new time and time picker dialog has closed
	* @param onCancelCallback - callback function that is called when user cancelled time picker dialog
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onTimeSetCallback, onCancelCallback"))
	static void ShowTimePicker(int hour, int minute, const FOnDateTimeSetDelegate& onTimeSetCallback, const FOnDateTimeCancelDelegate& onCancelCallback);

	/**
	* Show the default iOS time picker, but with limited time range.
	* @param hour - initial hour value for time picker dialog
	* @param minute - initial minute value for time picker dialog
	* @param fromHour - minimum time hour value in time picker dialog that can be selected
	* @param fromMinute - minimum time minute value in time picker dialog that can be selected
	* @param toHour - maximum time hour value in time picker dialog that can be selected
	* @param toMinute - maximum time minute value in time picker dialog that can be selected
	* @param onTimeSetCallback - callback function that is called when user is done setting a new time and time picker dialog has closed
	* @param onCancelCallback - callback function that is called when user cancelled time picker dialog
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onTimeSetCallback, onCancelCallback"))
	static void ShowTimePickerWithLimits(int hour, int minute, int fromHour, int fromMinute, int toHour, int toMinute,
		const FOnDateTimeSetDelegate& onTimeSetCallback, const FOnDateTimeCancelDelegate& onCancelCallback);

	/**
	* Show the default iOS date and time picker.
	* @param initialDate - initial date value for date and time picker dialog
	* @param hour - initial hour value for date and time picker dialog
	* @param minute - initial minute value for date and time picker dialog
	* @param onTimeSetCallback - callback function that is called when user is done setting a new date and time and time picker dialog has closed
	* @param onCancelCallback - callback function that is called when user cancelled date and time picker dialog
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onDateTimeSetCallback, onCancelCallback"))
	static void ShowDateTimePicker(FDateTime initialDate, int hour, int minute,
		const FOnDateTimeSetDelegate& onDateTimeSetCallback, const FOnDateTimeCancelDelegate& onCancelCallback);

	/**
	* Show the default iOS date and time picker, but with limited date and time range.
	* @param initialDate - initial date value for date and time picker dialog
	* @param fromDate - minimum date value in date and time picker dialog that can be selected
	* @param toDate - maximum date value in date and time picker dialog that can be selected
	* @param hour - initial hour value for date and time picker dialog
	* @param minute - initial minute value for date and time picker dialog
	* @param fromHour - minimum time hour value in date and time picker dialog that can be selected
	* @param fromMinute - minimum time minute value in date and time picker dialog that can be selected
	* @param toHour - maximum time hour value in date and time picker dialog that can be selected
	* @param toMinute - maximum time minute value in date and time picker dialog that can be selected
	* @param onDateTimeSetCallback - callback function that is called when user is done setting a new date and time and time picker dialog has closed
	* @param onCancelCallback - callback function that is called when user cancelled date and time picker dialog
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onDateTimeSetCallback, onCancelCallback"))
	static void ShowDateTimePickerWithLimits(FDateTime initialDate, FDateTime fromDate, FDateTime toDate,
		int hour, int minute, int fromHour, int fromMinute, int toHour, int toMinute,
		const FOnDateTimeSetDelegate& onDateTimeSetCallback, const FOnDateTimeCancelDelegate& onCancelCallback);

	/**
	* Show the default iOS countdown timer.
	* @param hour - initial hour value for countdown timer dialog
	* @param minute - initial minute value for countdown timer dialog
	* @param onTimeSetCallback - callback function that is called when user is done setting a time and countdown timer dialog has closed
	* @param onCancelCallback - callback function that is called when user cancelled countdown timer  dialog
	* @note This function only displays dialog with countdown timer picker style, no actual timer is set up
	*/
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies", meta = (AutoCreateRefTerm = "onTimerSetCallback, onCancelCallback"))
	static void ShowCoundownTimer(int hour, int minute, const FOnDateTimeSetDelegate& onTimerSetCallback, const FOnDateTimeCancelDelegate& onCancelCallback);

private:

	static FOnDateTimeSetDelegate OnDateTimeSetDelegate;
	static FOnDateTimeCancelDelegate OnCancelDelegate;
};
