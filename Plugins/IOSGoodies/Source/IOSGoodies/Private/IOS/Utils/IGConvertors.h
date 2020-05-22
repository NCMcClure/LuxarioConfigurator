// Copyright (c) 2018 Nineva Studios

#pragma once

#import <Foundation/Foundation.h>

class IGConvertors
{
public:

	static NSDate* ConvertToNSDate(int year, int month, int day, int hour, int minute);
    static NSDate* ConvertToNSDate(FDateTime dateTime);
    
    static NSDateComponents* ConvertToNSDateComponents(FDateTime dateTime);

	static NSArray* ConvertToNSArray(const TArray<FString>& array);
	
	static NSString* ConvertFStringToEncodedNSString(FString input);
};
