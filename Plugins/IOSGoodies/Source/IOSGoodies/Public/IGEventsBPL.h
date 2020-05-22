// Copyright (c) 2019 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "IGRecurrencyRuleType.h"
#include "IGEventsBPL.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FEventCreatedDelegate, FString, eventId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FEventErrorDelegate, FString, error);
DECLARE_DYNAMIC_DELEGATE(FEventRemovedDelegate);

/**
 * Class for events and reminders
 */
UCLASS()
class IOSGOODIES_API UIGEvents : public UBlueprintFunctionLibrary
{
    GENERATED_UCLASS_BODY()
    
    /**
    * Open the default calendar app
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static void OpenCalendar();
    
    /**
    * Open the default calendar app at the specified date
    * @param date - the date to open calendar at
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static void OpenCalendarAtDate(FDateTime date);
    
    /**
    * Create calendar event
    * @param title - event name
    * @param notes - event description
    * @param startDate - event start date
    * @param endDate - event end date
    * @param onSuccessCallback - callback function that is called after calendar event was created (receives unique identifier of the event)
    * @param onErrorCallback - callback function that is called if calendar event creation resulted with an error
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback"))
    static void CreateCalendarEvent(FString title, FString notes, FDateTime startDate, FDateTime endDate,
        const FEventCreatedDelegate &onSuccessCallback, const FEventErrorDelegate &onErrorCallback);
    
    /**
    * Create repeating calendar event
    * @param title - event name
    * @param notes - event description
    * @param startDate - event start date
    * @param endDate - event end date
    * @param repeatUntilDate - the date until which event repeats
    * @param ruleType - recurrence type of the event (daily, weekly, monthly, or yearly)
    * @param interval - the number of RecurrenceRuleType instances to be skipped until event repetition
    * @param onSuccessCallback - callback function that is called after calendar event was created (receives unique identifier of the event)
    * @param onErrorCallback - callback function that is called if calendar event creation resulted with an error
    * @note i.e. if you choose Daily rule type and pass 5 as interval, the event will be repeated every 5 days
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback"))
    static void CreateRepeatingEvent(FString title, FString notes,
        FDateTime startDate, FDateTime endDate, FDateTime repeatUntilDate, RecurrencyRuleType ruleType, int interval,
        const FEventCreatedDelegate &onSuccessCallback, const FEventErrorDelegate &onErrorCallback);
    
    /**
    * Remove calendar event
    * @param eventId - the unique identifier of the event
    * @param onRemovedCallback - callback function that is called after calendar event was removed
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onRemovedCallback"))
    static void RemoveCalendarEvent(FString eventId, const FEventRemovedDelegate &onRemovedCallback);
    
    /**
    * Create reminder with given parameters
    * @param title - reminder name
    * @param startDate - reminder start date
    * @param dueDate - reminder due date
    * @param onSuccessCallback - callback function that is called after reminder was created (receives unique identifier of the event)
    * @param onErrorCallback - acallback function that is called if reminder creation resulted with an error
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies", meta = (AutoCreateRefTerm = "onSuccessCallback, onErrorCallback"))
    static void CreateReminder(FString title, FDateTime startDate, FDateTime dueDate,
        const FEventCreatedDelegate &onSuccessCallback, const FEventErrorDelegate &onErrorCallback);
    
    /**
    * Mark reminder with specified identifier as completed/incomplete
    * @param eventId - the unique identifier of the reminder
    * @param complete - flag indicating whether to mark reminder as completed
    * @return - true if reminder was marked as expected; otherwise, false.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static bool CompleteReminder(FString reminderId, bool complete);
    
    /**
    * Remove reminder
    * @param reminderId - the unique identifier of the reminder
    * @return - true if reminder was deleted; otherwise, false.
    */
    UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
    static bool DeleteReminder(FString reminderId);
    
private:
    
    static FEventCreatedDelegate OnSuccessDelegate;
    static FEventErrorDelegate OnErrorDelegate;
    static FEventRemovedDelegate OnRemovedDelegate;
};
