// Copyright (c) 2018 Nineva Studios

#include "IGMapsBPL.h"
#if PLATFORM_IOS
#include "Utils/IGCommonUtils.h"
#include "Utils/IGConvertors.h"
#endif

UIGMapsBPL::UIGMapsBPL(const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer)
{
}
#if PLATFORM_IOS
NSString* const MapsUrl = @"http://maps.apple.com/?";
int const DefaultZoom = 7;
int const MinimalZoom = 2;
int const MaximalZoom = 23;
float const LatitudeBound = 90.0f;
float const LongitudeBound = 180.0f;


NSArray *MapViewTypeArray() {
	return @[@"m", @"k", @"h", @"r"];
}

NSArray *MapTransportTypeArray() {
	return @[@"d", @"w", @"r"];
}

bool ParametersAreValid(float latitude, float longitude, int zoom) {
	return latitude >= -LatitudeBound && latitude <= LatitudeBound &&
	longitude >= -LongitudeBound && longitude <= LongitudeBound &&
	zoom <= MaximalZoom && zoom >= MinimalZoom;
}
#endif

void UIGMapsBPL::OpenMapLocation(float latitude, float longitude, FString label, MapViewType viewType) {
#if PLATFORM_IOS
	if (!ParametersAreValid(latitude, longitude, DefaultZoom)) {
		NSLog(@"One of the parameters (latitude, longitude, zoom) is invalid!");
		return;
	}
	NSString *urlString = [NSString stringWithFormat:@"%@ll=%.7f,%.7f&t=%@&q=%@", MapsUrl, latitude, longitude,
						   MapViewTypeArray()[(int) viewType], IGConvertors::ConvertFStringToEncodedNSString(label)];
	IGCommonUtils::OpenUrl(urlString);
#endif
}

void UIGMapsBPL::OpenMapAddress(FString address, FString label, MapViewType viewType) {
#if PLATFORM_IOS
	NSString* addressFormatted = [address.GetNSString() stringByReplacingOccurrencesOfString:@" " withString:@"+"];
	NSString *urlString = [NSString stringWithFormat:@"%@address=%@&t=%@&q=%@", MapsUrl, addressFormatted,
						   MapViewTypeArray()[(int) viewType], IGConvertors::ConvertFStringToEncodedNSString(label)];
	IGCommonUtils::OpenUrl(urlString);
#endif
}

void UIGMapsBPL::GetDirections(FString destinationAddress, FString sourceAddress,
				   TransportType transportType, MapViewType viewType) {
#if PLATFORM_IOS
	NSString* destinationAddressStr = IGConvertors::ConvertFStringToEncodedNSString(destinationAddress);
	NSString* sourceAddressStr = IGConvertors::ConvertFStringToEncodedNSString(sourceAddress);
	
	NSString *urlString = [NSString stringWithFormat:@"%@daddr=%@&dirflg=%@&t=%@&saddr=%@", MapsUrl,
						   destinationAddressStr, MapTransportTypeArray()[(int) transportType],
						   MapViewTypeArray()[(int) viewType], sourceAddressStr];
	IGCommonUtils::OpenUrl(urlString);
#endif
}

void UIGMapsBPL::PerformSearch(FString query, MapViewType viewType) {
#if PLATFORM_IOS
	NSString* queryStr = IGConvertors::ConvertFStringToEncodedNSString(query);
	
	NSString *urlString = [NSString stringWithFormat:@"%@q=%@&t=%@", MapsUrl,
						   queryStr, MapViewTypeArray()[(int) viewType]];
	IGCommonUtils::OpenUrl(urlString);
#endif
}

void UIGMapsBPL::PerformSearchNearLocation(FString query, float latitude, float longitude, int zoom, MapViewType viewType) {
#if PLATFORM_IOS
	if (!ParametersAreValid(latitude, longitude, zoom)) {
		NSLog(@"One of the parameters (latitude, longitude, zoom) is invalid!");
		return;
	}
	NSString* queryStr = IGConvertors::ConvertFStringToEncodedNSString(query);
	
	NSString *urlString = [NSString stringWithFormat:@"%@q=%@&sll=%.7f,%.7f&z=%d&t=%@", MapsUrl,
						   queryStr, latitude, longitude, zoom, MapViewTypeArray()[(int) viewType]];
	IGCommonUtils::OpenUrl(urlString);
#endif
}
