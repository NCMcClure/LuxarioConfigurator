// Copyright (c) 2018 Nineva Studios

#include "IGDateTimePicker.h"
#include "IOS/IOSAppDelegate.h"
#include "Runtime/Core/Public/Async/Async.h"

NS_ASSUME_NONNULL_BEGIN

@implementation IGDateTimePicker
{
}

- (void)setCallbacks:(FOnDateTimeSetDelegate*)onDateTimeSelectedDelegate onCancelDelegate:(FOnDateTimeCancelDelegate*)onCancelDelegate
{
	self = [super init];

	_onDateTimeSelectedDelegate = onDateTimeSelectedDelegate;
	_onCancelDelegate = onCancelDelegate;
}

- (void)setInitialDateTime:(NSDate*)initialDateTime;
{
	_initialDateTime = initialDateTime;
}

- (void)setDateTimeLimits:(NSDate*)minDateTime maxDateTime:(NSDate*)maxDateTime
{
	_minDateTime = minDateTime;
	_maxDateTime = maxDateTime;
}

- (void)setType:(DateTimePickerType)pickerType
{
	_pickerType = pickerType;
}

- (void)showPicker
{
	UIView *rootView = [IOSAppDelegate GetDelegate].RootView;

	// Block input behind
	_blockerButton = [[UIButton alloc] initWithFrame:rootView.frame];
	[_blockerButton setBackgroundColor:[UIColor clearColor]];
	_blockerButton.tag = 42;
	_blockerButton.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.6];
	[rootView addSubview:_blockerButton];

	// Date Picker
	_picker = [[UIDatePicker alloc] init];
	_picker.frame = CGRectMake(0, rootView.frame.size.height - _picker.frame.size.height, rootView.frame.size.width, _picker.frame.size.height);
	_picker.autoresizingMask = UIViewAutoresizingFlexibleTopMargin;

	if (_pickerType == DateTimePickerType::DatePicker) {
		_picker.datePickerMode = UIDatePickerModeDate;
	} else if (_pickerType == DateTimePickerType::TimePicker) {
		_picker.datePickerMode = UIDatePickerModeTime;
	} else if (_pickerType == DateTimePickerType::DateTimePicker) {
		_picker.datePickerMode = UIDatePickerModeDateAndTime;
	} else if (_pickerType == DateTimePickerType::CountdownTimer) {
		_picker.datePickerMode = UIDatePickerModeCountDownTimer;
	}

	_picker.hidden = NO;
	_picker.date = _initialDateTime;
    
    // When using plugin for iOS 13 and newer uncomment the following block of code
    
//    if (@available(iOS 13, *)) {
//        UITraitCollection* traitCol = [_picker traitCollection];
//        if (traitCol.userInterfaceStyle == UIUserInterfaceStyleLight) {
//            _picker.backgroundColor = [UIColor whiteColor];
//        } else if (traitCol.userInterfaceStyle == UIUserInterfaceStyleDark) {
//            _picker.backgroundColor = [UIColor blackColor];
//        } else {
//            _picker.backgroundColor = [UIColor whiteColor];
//        }
//    } else {
//        _picker.backgroundColor = [UIColor whiteColor];
//    }
    
    // end uncommenting here

    // When using plugin for iOS 13 and newer comment the following line of code
    _picker.backgroundColor = [UIColor whiteColor];
    // end commenting here
	
	if(_minDateTime && _maxDateTime)
	{
		_picker.minimumDate = _minDateTime;
		_picker.maximumDate = _maxDateTime;
	}

	[[IOSAppDelegate GetDelegate].RootView addSubview:_picker];

	// Toolbar - Done button
	CGRect toolbarRect = CGRectMake(0, _picker.frame.origin.y - 44, rootView.frame.size.width, 44);
	_toolbar = [[UIToolbar alloc] initWithFrame:toolbarRect];
	UIBarButtonItem *spacer = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil];
	UIBarButtonItem *doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(onDatePicked:)];
	UIBarButtonItem *cancelButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(dismiss:)];
	[_toolbar setItems:@[cancelButton, spacer, doneButton]];

	[[IOSAppDelegate GetDelegate].RootView addSubview:_toolbar];
}

- (void)dismiss:(id)dismiss
{
	[self removeViews];
    AsyncTask(ENamedThreads::GameThread, [=]() {
        _onCancelDelegate->ExecuteIfBound();
    });
	
}

- (void)onDatePicked:(id)dismiss
{
	[self removeViews];
    
    AsyncTask(ENamedThreads::GameThread, [=]() {
        NSDateComponents *components = [[NSCalendar currentCalendar] components:NSCalendarUnitDay |
                                        NSCalendarUnitMonth | NSCalendarUnitYear | NSCalendarUnitHour |
                                        NSCalendarUnitMinute fromDate:_picker.date];
        
        NSInteger day = [components day];
        NSInteger month = [components month];
        NSInteger year = [components year];
        NSInteger hour = [components hour];
        NSInteger minute = [components minute];
        
        _onDateTimeSelectedDelegate->ExecuteIfBound(year, month, day, hour, minute);
    });
	
}

- (void)removeViews
{
	[_blockerButton removeFromSuperview];
	[_toolbar removeFromSuperview];
	[_picker removeFromSuperview];
}
@end

NS_ASSUME_NONNULL_END
