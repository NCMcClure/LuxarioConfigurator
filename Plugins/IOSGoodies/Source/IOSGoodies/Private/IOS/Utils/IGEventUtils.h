// Copyright (c) 2019 Nineva Studios

#pragma once

#import <Foundation/Foundation.h>
#import <EventKit/EventKit.h>

typedef void(^EventsNSStringFunctionDelegate)(NSString* str);

class IGEventUtils
{
public:
    static EKEvent* CreateBasicEvent(EKEventStore* store, NSString* title, NSString* notes,
                                            NSDate* startDate, NSDate* endDate);
    
    static EKReminder* CreateBasicReminder(EKEventStore* store, NSString* title,
                                           NSDateComponents* startDate, NSDateComponents* dueDate);
    
    static EKRecurrenceRule* CreateRecurrencyRule(NSDate* repeatUntilDate,
                                                  RecurrencyRuleType ruleType, int interval);
    
    static void SaveEventToCalendar(EKEventStore* store, EKEvent* event,
                                    EventsNSStringFunctionDelegate onSuccess,
                                    EventsNSStringFunctionDelegate onError);
    
    static void SaveReminder(EKEventStore* store, EKReminder* reminder,
                             EventsNSStringFunctionDelegate onSuccess,
                             EventsNSStringFunctionDelegate onError);
};
