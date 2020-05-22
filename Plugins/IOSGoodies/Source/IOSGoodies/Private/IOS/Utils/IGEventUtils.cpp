// Copyright (c) 2019 Nineva Studios

#include "IGEventUtils.h"

EKEvent* IGEventUtils::CreateBasicEvent(EKEventStore* store, NSString* title, NSString* notes, NSDate* startDate, NSDate* endDate) {
    EKEvent* event = [EKEvent eventWithEventStore:store];
    event.title = title;
    event.notes = notes;
    event.startDate = startDate;
    event.endDate = endDate;
    event.calendar = [store defaultCalendarForNewEvents];
    return event;
}

EKReminder* IGEventUtils::CreateBasicReminder(EKEventStore* store, NSString* title, NSDateComponents* startDate, NSDateComponents* dueDate) {
    EKReminder* reminder = [EKReminder reminderWithEventStore:store];
    reminder.title = title;
    reminder.startDateComponents = startDate;
    reminder.dueDateComponents = dueDate;
    reminder.calendar = [store defaultCalendarForNewReminders];
    reminder.completed = NO;
    return reminder;
}

EKRecurrenceRule* IGEventUtils::CreateRecurrencyRule(NSDate* repeatUntilDate, RecurrencyRuleType ruleType, int interval) {
    EKRecurrenceFrequency frequency = EKRecurrenceFrequencyDaily;
    switch ((int) ruleType) {
        case 0:
            frequency = EKRecurrenceFrequencyDaily;
            break;
        case 1:
            frequency = EKRecurrenceFrequencyWeekly;
            break;
        case 2:
            frequency = EKRecurrenceFrequencyMonthly;
            break;
        case 3:
            frequency = EKRecurrenceFrequencyYearly;
            break;
        default:
            break;
    }
    EKRecurrenceRule* rule = [[EKRecurrenceRule alloc]
                              initRecurrenceWithFrequency:frequency
                              interval:interval
                              end:[EKRecurrenceEnd recurrenceEndWithEndDate:repeatUntilDate]];
    return rule;
}

void IGEventUtils::SaveEventToCalendar(EKEventStore* store, EKEvent* event,
                         EventsNSStringFunctionDelegate onSuccess, EventsNSStringFunctionDelegate onError) {
    NSError* err = nil;
    [store saveEvent:event span:EKSpanThisEvent commit:YES error:&err];
    NSString* identifier = event.eventIdentifier;
    
    if(err != nil) {
        dispatch_async(dispatch_get_main_queue(), ^{
            onError(err.localizedDescription);
        });
    } else {
        dispatch_async(dispatch_get_main_queue(), ^{
            onSuccess(identifier);
        });
    }
}

void IGEventUtils::SaveReminder(EKEventStore* store, EKReminder* reminder,
                  EventsNSStringFunctionDelegate onSuccess, EventsNSStringFunctionDelegate onError) {
    NSError* err = nil;
    [store saveReminder:reminder commit:YES error:&err];
    NSString* identifier = reminder.calendarItemIdentifier;
    
    if(err != nil) {
        dispatch_async(dispatch_get_main_queue(), ^{
            onError(err.localizedDescription);
        });
    } else {
        dispatch_async(dispatch_get_main_queue(), ^{
            onSuccess(identifier);
        });
    }
}
