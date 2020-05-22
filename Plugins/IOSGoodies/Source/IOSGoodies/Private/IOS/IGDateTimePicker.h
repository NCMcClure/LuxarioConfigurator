// Copyright (c) 2018 Nineva Studios

#import <Foundation/Foundation.h>
#import "IGDateTimePickerBPL.h"
#import "IGDateTimePickerType.h"

NS_ASSUME_NONNULL_BEGIN

@interface IGDateTimePicker : NSObject
{
	DateTimePickerType _pickerType;

	NSDate* _initialDateTime;
	NSDate* _minDateTime;
	NSDate* _maxDateTime;

	FOnDateTimeSetDelegate* _onDateTimeSelectedDelegate;
	FOnDateTimeCancelDelegate* _onCancelDelegate;

	UIButton* _blockerButton;
	UIDatePicker* _picker;
	UIToolbar* _toolbar;
}

- (void)setCallbacks:(FOnDateTimeSetDelegate*)onDateTimeSelectedDelegate onCancelDelegate:(FOnDateTimeCancelDelegate*)onCancelDelegate;

- (void)setInitialDateTime:(NSDate*)initialDateTime;
- (void)setDateTimeLimits:(NSDate*)minDateTime maxDateTime:(NSDate*)maxDateTime;

- (void)setType:(DateTimePickerType)pickerType;

- (void)showPicker;

@end

NS_ASSUME_NONNULL_END