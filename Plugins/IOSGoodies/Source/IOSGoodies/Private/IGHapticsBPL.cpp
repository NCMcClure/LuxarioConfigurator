// Copyright (c) 2018 Nineva Studios

#include "IGHapticsBPL.h"
#include "IGDeviceInfoBPL.h"

#if PLATFORM_IOS
#import <AudioToolbox/AudioToolbox.h>
#import <sys/utsname.h>
#endif

UIGHaptics::UIGHaptics(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

bool UIGHaptics::IsHapticFeedbackSupported()
{
	bool result = false;
#if PLATFORM_IOS
	int deviceCode = 0;
	struct utsname systemInfo;
	uname(&systemInfo);
	
	NSString* deviceModel = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
	if ([deviceModel hasPrefix: @"iPhone"]) {
		deviceModel = [deviceModel stringByReplacingOccurrencesOfString:@"iPhone" withString:@""];
		unichar firstChar = [deviceModel characterAtIndex:0];
		if (firstChar == '1' || firstChar == '9') {
			result = true;
		}
	}
#endif
	return result;
}

void UIGHaptics::SendNotificationHapticFeedback(NotificationType type)
{
#if PLATFORM_IOS
	UINotificationFeedbackType notificationType;
	switch ((int)type) {
		case 0:
			notificationType = UINotificationFeedbackTypeError;
			break;
		case 1:
			notificationType = UINotificationFeedbackTypeWarning;
			break;
		case 2:
			notificationType = UINotificationFeedbackTypeSuccess;
			break;
		default:
			notificationType = UINotificationFeedbackTypeError;
			break;
	}
	dispatch_async(dispatch_get_main_queue(), ^ {
		UINotificationFeedbackGenerator *notification = [[UINotificationFeedbackGenerator alloc] init];
		[notification notificationOccurred:notificationType];
	});
#endif
}

void UIGHaptics::SendSelectionHapticFeedback()
{
#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^ {
		UISelectionFeedbackGenerator *selector = [[UISelectionFeedbackGenerator alloc] init];
		[selector selectionChanged];
	});
#endif
}

void UIGHaptics::SendImpactHapticFeedback(ImpactStrength strength)
{
#if PLATFORM_IOS
	UIImpactFeedbackStyle impactType;
	switch ((int)strength) {
		case 0:
			impactType = UIImpactFeedbackStyleLight;
			break;
		case 1:
			impactType = UIImpactFeedbackStyleMedium;
			break;
		case 2:
			impactType = UIImpactFeedbackStyleHeavy;
			break;
		default:
			impactType = UIImpactFeedbackStyleLight;
			break;
	}
	dispatch_async(dispatch_get_main_queue(), ^ {
		UIImpactFeedbackGenerator *impact = [[UIImpactFeedbackGenerator alloc] initWithStyle:impactType];
		[impact impactOccurred];
	});
#endif
}

void UIGHaptics::Vibrate()
{
#if PLATFORM_IOS
	AudioServicesPlayAlertSound(SystemSoundID(kSystemSoundID_Vibrate));
#endif
}
