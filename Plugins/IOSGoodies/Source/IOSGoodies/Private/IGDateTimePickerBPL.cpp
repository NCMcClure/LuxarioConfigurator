// Copyright (c) 2018 Nineva Studios

#include <IOSGoodies/Public/IGDateTimePickerBPL.h>

#include "IGDateTimePickerBPL.h"
#include "IGDateTimePickerType.h"

#if PLATFORM_IOS
#import "IGDateTimePicker.h"
#include "Utils/IGConvertors.h"
#endif

FOnDateTimeSetDelegate UIGDateTimePickerBPL::OnDateTimeSetDelegate;
FOnDateTimeCancelDelegate UIGDateTimePickerBPL::OnCancelDelegate;

UIGDateTimePickerBPL::UIGDateTimePickerBPL(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UIGDateTimePickerBPL::ShowDatePicker(FDateTime initialDate, const FOnDateTimeSetDelegate &onDateSetCallback,
	const FOnDateTimeCancelDelegate &onCancelCallback)
{
	OnDateTimeSetDelegate = onDateSetCallback;
	OnCancelDelegate = onCancelCallback;

#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IGDateTimePicker* dateTimePickerController = [IGDateTimePicker alloc];
		[dateTimePickerController setCallbacks:&OnDateTimeSetDelegate onCancelDelegate:&OnCancelDelegate];
		[dateTimePickerController setInitialDateTime:IGConvertors::ConvertToNSDate(initialDate.GetYear(), initialDate.GetMonth(), initialDate.GetDay(), 0, 0)];
		[dateTimePickerController setType:DateTimePickerType::DatePicker];
		[dateTimePickerController showPicker];
	});
#endif
}

void UIGDateTimePickerBPL::ShowDatePickerWithLimits(FDateTime initialDate, FDateTime fromDate, FDateTime toDate,
	const FOnDateTimeSetDelegate &onDateSetCallback, const FOnDateTimeCancelDelegate &onCancelCallback)
{
	OnDateTimeSetDelegate = onDateSetCallback;
	OnCancelDelegate = onCancelCallback;

#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IGDateTimePicker* dateTimePickerController = [IGDateTimePicker alloc];
		[dateTimePickerController setCallbacks:&OnDateTimeSetDelegate onCancelDelegate:&OnCancelDelegate];
		[dateTimePickerController setInitialDateTime:IGConvertors::ConvertToNSDate(initialDate.GetYear(), initialDate.GetMonth(), initialDate.GetDay(), 0, 0)];
		[dateTimePickerController setDateTimeLimits:IGConvertors::ConvertToNSDate(fromDate.GetYear(), fromDate.GetMonth(), fromDate.GetDay(), 0, 0)
			maxDateTime:IGConvertors::ConvertToNSDate(toDate.GetYear(), toDate.GetMonth(), toDate.GetDay(), 0, 0)];
		[dateTimePickerController setType:DateTimePickerType::DatePicker];
		[dateTimePickerController showPicker];
	});
#endif
}

void UIGDateTimePickerBPL::ShowTimePicker(int hour, int minute, const FOnDateTimeSetDelegate& onTimeSetCallback, const FOnDateTimeCancelDelegate& onCancelCallback)
{
	OnDateTimeSetDelegate = onTimeSetCallback;
	OnCancelDelegate = onCancelCallback;

#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IGDateTimePicker* dateTimePickerController = [IGDateTimePicker alloc];
		[dateTimePickerController setCallbacks:&OnDateTimeSetDelegate onCancelDelegate:&OnCancelDelegate];
		[dateTimePickerController setInitialDateTime:IGConvertors::ConvertToNSDate(0, 0, 0, hour, minute)];
		[dateTimePickerController setType:DateTimePickerType::TimePicker];
		[dateTimePickerController showPicker];
	});
#endif
}

void UIGDateTimePickerBPL::ShowTimePickerWithLimits(int hour, int minute, int fromHour, int fromMinute, int toHour, int toMinute,
	const FOnDateTimeSetDelegate& onTimeSetCallback, const FOnDateTimeCancelDelegate& onCancelCallback)
{
	OnDateTimeSetDelegate = onTimeSetCallback;
	OnCancelDelegate = onCancelCallback;

#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IGDateTimePicker* dateTimePickerController = [IGDateTimePicker alloc];
		[dateTimePickerController setCallbacks:&OnDateTimeSetDelegate onCancelDelegate:&OnCancelDelegate];
		[dateTimePickerController setInitialDateTime:IGConvertors::ConvertToNSDate(0, 0, 0, hour, minute)];
		[dateTimePickerController setDateTimeLimits:IGConvertors::ConvertToNSDate(0, 0, 0, fromHour, fromMinute)
			maxDateTime:IGConvertors::ConvertToNSDate(0, 0, 0, toHour, toMinute)];
		[dateTimePickerController setType:DateTimePickerType::TimePicker];
		[dateTimePickerController showPicker];
	});
#endif
}

void UIGDateTimePickerBPL::ShowDateTimePicker(FDateTime initialDate, int hour, int minute,
	const FOnDateTimeSetDelegate &onDateTimeSetCallback, const FOnDateTimeCancelDelegate &onCancelCallback)
{
	OnDateTimeSetDelegate = onDateTimeSetCallback;
	OnCancelDelegate = onCancelCallback;

#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IGDateTimePicker* dateTimePickerController = [IGDateTimePicker alloc];
		[dateTimePickerController setCallbacks:&OnDateTimeSetDelegate onCancelDelegate:&OnCancelDelegate];
		[dateTimePickerController setInitialDateTime:IGConvertors::ConvertToNSDate(initialDate.GetYear(), initialDate.GetMonth(), initialDate.GetDay(), hour, minute)];
		[dateTimePickerController setType:DateTimePickerType::DateTimePicker];
		[dateTimePickerController showPicker];
	});
#endif
}

void UIGDateTimePickerBPL::ShowDateTimePickerWithLimits(FDateTime initialDate, FDateTime fromDate, FDateTime toDate,
	int hour, int minute, int fromHour, int fromMinute, int toHour, int toMinute,
	const FOnDateTimeSetDelegate &onDateTimeSetCallback, const FOnDateTimeCancelDelegate &onCancelCallback)
{
	OnDateTimeSetDelegate = onDateTimeSetCallback;
	OnCancelDelegate = onCancelCallback;

#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IGDateTimePicker* dateTimePickerController = [IGDateTimePicker alloc];
		[dateTimePickerController setCallbacks:&OnDateTimeSetDelegate onCancelDelegate:&OnCancelDelegate];
		[dateTimePickerController setInitialDateTime:IGConvertors::ConvertToNSDate(initialDate.GetYear(), initialDate.GetMonth(), initialDate.GetDay(), hour, minute)];
		[dateTimePickerController setDateTimeLimits:IGConvertors::ConvertToNSDate(fromDate.GetYear(), fromDate.GetMonth(), fromDate.GetDay(), fromHour, fromMinute)
			maxDateTime:IGConvertors::ConvertToNSDate(toDate.GetYear(), toDate.GetMonth(), toDate.GetDay(), toHour, toMinute)];
		[dateTimePickerController setType:DateTimePickerType::DateTimePicker];
		[dateTimePickerController showPicker];
	});
#endif
}

void UIGDateTimePickerBPL::ShowCoundownTimer(int hour, int minute, const FOnDateTimeSetDelegate& onTimerSetCallback, const FOnDateTimeCancelDelegate& onCancelCallback)
{
	OnDateTimeSetDelegate = onTimerSetCallback;
	OnCancelDelegate = onCancelCallback;

#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IGDateTimePicker* dateTimePickerController = [IGDateTimePicker alloc];
		[dateTimePickerController setCallbacks:&OnDateTimeSetDelegate onCancelDelegate:&OnCancelDelegate];
		[dateTimePickerController setInitialDateTime:IGConvertors::ConvertToNSDate(0, 0, 0, hour, minute)];
		[dateTimePickerController setType:DateTimePickerType::CountdownTimer];
		[dateTimePickerController showPicker];
	});
#endif
}