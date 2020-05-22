// Copyright (c) 2019 Nineva Studios

#include "IGEventsBPL.h"
#include "Runtime/Core/Public/Async/Async.h"

#if PLATFORM_IOS
#include "IOS/Utils/IGConvertors.h"
#include "IOS/Utils/IGEventUtils.h"
#endif

FEventCreatedDelegate UIGEvents::OnSuccessDelegate;
FEventErrorDelegate UIGEvents::OnErrorDelegate;
FEventRemovedDelegate UIGEvents::OnRemovedDelegate;

UIGEvents::UIGEvents(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UIGEvents::OpenCalendar()
{
#if PLATFORM_IOS
    NSURL* url = [NSURL URLWithString:@"calshow://"];
    [[UIApplication sharedApplication] openURL:url options:@{} completionHandler:nil];
#endif
}

void UIGEvents::OpenCalendarAtDate(FDateTime date)
{
#if PLATFORM_IOS
    NSDate* nsDate = IGConvertors::ConvertToNSDate(date);
    NSInteger interval = [nsDate timeIntervalSinceReferenceDate];
    NSURL* url = [NSURL URLWithString:[NSString stringWithFormat:@"calshow:%ld", (long)interval]];
    [[UIApplication sharedApplication] openURL:url options:@{} completionHandler:nil];
#endif
}

void UIGEvents::CreateCalendarEvent(FString title, FString notes, FDateTime startDate, FDateTime endDate,
    const FEventCreatedDelegate &onSuccessCallback, const FEventErrorDelegate &onErrorCallback)
{
    OnSuccessDelegate = onSuccessCallback;
    OnErrorDelegate = onErrorCallback;
#if PLATFORM_IOS
    __block NSString* titleStr = title.GetNSString();
    __block NSString* notesStr = notes.GetNSString();
    EKEventStore *store = [EKEventStore new];
    [store requestAccessToEntityType:EKEntityTypeEvent completion:^(BOOL granted, NSError *error) {
        if (!granted) {
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnErrorDelegate.ExecuteIfBound(FString(error.localizedDescription));
            });
            return;
        }
        EKEvent* event = IGEventUtils::CreateBasicEvent(store, titleStr, notesStr,
                                          IGConvertors::ConvertToNSDate(startDate),
                                          IGConvertors::ConvertToNSDate(endDate));
        
        IGEventUtils::SaveEventToCalendar(store, event, ^(NSString* identifier) {
            FString fIdentifier = FString(identifier);
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnSuccessDelegate.ExecuteIfBound(fIdentifier);
            });
        }, ^(NSString* err) {
            FString fError = FString(err);
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnErrorDelegate.ExecuteIfBound(fError);
            });
        });
    }];
#endif
}

void UIGEvents::CreateRepeatingEvent(FString title, FString notes,
    FDateTime startDate, FDateTime endDate, FDateTime repeatUntilDate, RecurrencyRuleType ruleType, int interval,
    const FEventCreatedDelegate &onSuccessCallback, const FEventErrorDelegate &onErrorCallback)
{
    OnSuccessDelegate = onSuccessCallback;
    OnErrorDelegate = onErrorCallback;
#if PLATFORM_IOS
    __block NSString* titleStr = title.GetNSString();
    __block NSString* notesStr = notes.GetNSString();
    EKEventStore* store = [EKEventStore new];
    [store requestAccessToEntityType:EKEntityTypeEvent completion:^(BOOL granted, NSError *error) {
        if (!granted) {
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnErrorDelegate.ExecuteIfBound(FString(error.localizedDescription));
            });
            return;
        }
        EKEvent* event = IGEventUtils::CreateBasicEvent(store, titleStr, notesStr,
                                          IGConvertors::ConvertToNSDate(startDate),
                                          IGConvertors::ConvertToNSDate(endDate));
        
        EKRecurrenceRule *rule = IGEventUtils::CreateRecurrencyRule(IGConvertors::ConvertToNSDate(repeatUntilDate),
                                                                    ruleType, interval);
        [event addRecurrenceRule:rule];
        
        IGEventUtils::SaveEventToCalendar(store, event, ^(NSString* identifier){
            FString fIdentifier = FString(identifier);
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnSuccessDelegate.ExecuteIfBound(fIdentifier);
            });
        }, ^(NSString* err) {
            FString fError = FString(err);
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnErrorDelegate.ExecuteIfBound(fError);
            });
        });
    }];
#endif
}

void UIGEvents::RemoveCalendarEvent(FString eventId, const FEventRemovedDelegate &onRemovedCallback)
{
    OnRemovedDelegate = onRemovedCallback;
#if PLATFORM_IOS
    EKEventStore* store = [EKEventStore new];
    __block NSString* idStr = eventId.GetNSString();
    [store requestAccessToEntityType:EKEntityTypeEvent completion:^(BOOL granted, NSError *error) {
        if (!granted) {
            return;
        }
        EKEvent* eventToRemove = [store eventWithIdentifier:idStr];
        if (eventToRemove) {
            NSError* err = nil;
            BOOL bResult = [store removeEvent:eventToRemove span:EKSpanFutureEvents commit:YES error:&err];
            if(bResult) {
                AsyncTask(ENamedThreads::GameThread, [=]() {
                    OnRemovedDelegate.ExecuteIfBound();
                });
            }
        }
    }];
#endif
}

void UIGEvents::CreateReminder(FString title, FDateTime startDate, FDateTime dueDate,
    const FEventCreatedDelegate &onSuccessCallback, const FEventErrorDelegate &onErrorCallback)
{
    OnSuccessDelegate = onSuccessCallback;
    OnErrorDelegate = onErrorCallback;
#if PLATFORM_IOS
    __block NSString* titleStr = title.GetNSString();
    EKEventStore* store = [EKEventStore new];
    [store requestAccessToEntityType:EKEntityTypeReminder completion:^(BOOL granted, NSError *error) {
        if (!granted) {
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnErrorDelegate.ExecuteIfBound(FString(error.localizedDescription));
            });
            return;
        }
        EKReminder* reminder = IGEventUtils::CreateBasicReminder(store, titleStr, IGConvertors::ConvertToNSDateComponents(startDate), IGConvertors::ConvertToNSDateComponents(dueDate));
        
        IGEventUtils::SaveReminder(store, reminder, ^(NSString* identifier) {
            FString fIdentifier = FString(identifier);
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnSuccessDelegate.ExecuteIfBound(fIdentifier);
            });
        }, ^(NSString* err) {
            FString fError = FString(err);
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnErrorDelegate.ExecuteIfBound(fError);
            });
        });
    }];
#endif
}

bool UIGEvents::CompleteReminder(FString reminderId, bool complete)
{
    bool bResult = false;
    
#if PLATFORM_IOS
    EKEventStore* store = [EKEventStore new];
    EKReminder* reminder = (EKReminder*) [store calendarItemWithIdentifier:reminderId.GetNSString()];
    if(reminder) {
        reminder.completed = complete;
        NSError* err = nil;
        bResult = [store saveReminder:reminder commit:YES error:&err];
    }
#endif
    
    return bResult;
}

bool UIGEvents::DeleteReminder(FString reminderId)
{
    bool bResult = false;
    
#if PLATFORM_IOS
    EKEventStore* store = [EKEventStore new];
    EKReminder* reminder = (EKReminder*) [store calendarItemWithIdentifier:reminderId.GetNSString()];
    if(reminder) {
        NSError* err = nil;
        bResult = [store removeReminder:reminder commit:YES error:&err];
    }
#endif
    
    return bResult;
}

