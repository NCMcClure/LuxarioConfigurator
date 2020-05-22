// Copyright (c) 2018 Nineva Studios

#pragma once

#include "IGFlashlightBPL.h"
#if PLATFORM_IOS
#import <AVFoundation/AVFoundation.h>
#endif

UIGFlashlight::UIGFlashlight(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UIGFlashlight::EnableFlashlight(bool enable) {
#if PLATFORM_IOS
	AVCaptureDevice *device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
	if ([device hasTorch]) {
		[device lockForConfiguration:nil];
		[device setTorchMode:enable ? AVCaptureTorchModeOn : AVCaptureTorchModeOff];
		[device unlockForConfiguration];
	}
#endif
}

bool UIGFlashlight::DeviceHasFlashlight() {
	bool result = false;
#if PLATFORM_IOS
	result = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo].hasTorch;
#endif
	return result;
}

void UIGFlashlight::SetFlashlightLevel(float level) {
#if PLATFORM_IOS
	AVCaptureDevice *device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
	if ([device hasTorch]) {
		[device lockForConfiguration:nil];
		if (level <= 0.0) {
			[device setTorchMode:AVCaptureTorchModeOff];
		} else {
			if (level >= 1.0) {
				level = AVCaptureMaxAvailableTorchLevel;
			}
			BOOL success = [device setTorchModeOnWithLevel:level error:nil];
		}
		[device unlockForConfiguration];
	}
#endif
}
