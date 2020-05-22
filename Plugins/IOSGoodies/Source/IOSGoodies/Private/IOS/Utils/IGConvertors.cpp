// Copyright (c) 2018 Nineva Studios

#include "IGConvertors.h"

NSDate* IGConvertors::ConvertToNSDate(int year, int month, int day, int hour, int minute)
{
	NSDateComponents *components = [[NSDateComponents alloc] init];
	[components setYear:year];
	[components setMonth:month];
	[components setDay:day];
	[components setHour:hour];
	[components setMinute:minute];

	NSCalendar *calendar = [NSCalendar currentCalendar];

	return [calendar dateFromComponents:components];
}

NSDate* IGConvertors::ConvertToNSDate(FDateTime dateTime)
{
    NSDateComponents* components = IGConvertors::ConvertToNSDateComponents(dateTime);
    NSCalendar* calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSCalendarIdentifierGregorian];
    
    return [calendar dateFromComponents:components];
}

NSDateComponents* IGConvertors::ConvertToNSDateComponents(FDateTime dateTime)
{
    NSDateComponents *components = [[NSDateComponents alloc] init];
    [components setMinute:dateTime.GetMinute()];
    [components setHour:dateTime.GetHour()];
    [components setDay:dateTime.GetDay()];
    [components setMonth:dateTime.GetMonth()];
    [components setYear:dateTime.GetYear()];
    
    return components;
}

NSArray* IGConvertors::ConvertToNSArray(const TArray<FString>& array)
{
	NSMutableArray *outArray = [NSMutableArray new];

	for(int i = 0; i < array.Num(); i++)
	{
		NSString *recipientStr = array[i].GetNSString();
		[outArray addObject:recipientStr];
	}

	return outArray;
}

NSString* IGConvertors::ConvertFStringToEncodedNSString(FString input) {
	NSString *inputStr = input.GetNSString();
	NSString *unreserved = @"-._~/?";
	NSMutableCharacterSet *allowed = [NSMutableCharacterSet alphanumericCharacterSet];
	[allowed addCharactersInString:unreserved];
	
	return [inputStr stringByAddingPercentEncodingWithAllowedCharacters:allowed];
}
