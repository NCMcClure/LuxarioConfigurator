// Copyright (c) 2018 Nineva Studios

#include "IGAppsBPL.h"
#if PLATFORM_IOS
#include "Utils/IGCommonUtils.h"
#import <StoreKit/StoreKit.h>
#endif

UIGApps::UIGApps(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UIGApps::OpenAppSettings() {
#if PLATFORM_IOS
	NSURL *settingsUrl = [NSURL URLWithString:UIApplicationOpenSettingsURLString];
	[[UIApplication sharedApplication] openURL:settingsUrl options:@{} completionHandler:nil];
#endif
}

void UIGApps::OpenYouTubeVideo(FString id) {
#if PLATFORM_IOS
	NSString *idStr = id.GetNSString();
	NSString *urlString = [NSString stringWithFormat:@"youtube://%@", idStr];
	NSURL *url = [NSURL URLWithString:urlString];
	if ([[UIApplication sharedApplication] canOpenURL:url]) {
		IGCommonUtils::OpenUrl(urlString);
	} else {
		NSString *urlStringFallback = [NSString stringWithFormat:@"http://www.youtube.com/watch?v=%@", idStr];
		IGCommonUtils::OpenUrl(urlStringFallback);
	}
#endif
}

void UIGApps::StartFaceTimeVideoCall(FString id) {
#if PLATFORM_IOS
	NSString *idStr = id.GetNSString();
	NSString *urlString = [NSString stringWithFormat:@"facetime:%@", idStr];
	IGCommonUtils::OpenUrl(urlString);
#endif
}

void UIGApps::StartFaceTimeAudioCall(FString id) {
#if PLATFORM_IOS
	NSString *idStr = id.GetNSString();
	NSString *urlString = [NSString stringWithFormat:@"facetime-audio:%@", idStr];
	IGCommonUtils::OpenUrl(urlString);
#endif
}

void UIGApps::OpenDialer(FString number) {
#if PLATFORM_IOS
	NSString *numberStr = number.GetNSString();
	NSString *urlString = [NSString stringWithFormat:@"tel:%@", numberStr];
	IGCommonUtils::OpenUrl(urlString);
#endif
}

void UIGApps::OpenAppOnAppStore(FString appId) {
#if PLATFORM_IOS
	NSString *appIdStr = appId.GetNSString();
	NSString *urlString = [NSString stringWithFormat:@"itms://itunes.apple.com/us/app/apple-store/id%@?mt=8", appIdStr];
	IGCommonUtils::OpenUrl(urlString);
#endif
}

void UIGApps::RequestRating() {
#if PLATFORM_IOS
	[SKStoreReviewController requestReview];
#endif
}
