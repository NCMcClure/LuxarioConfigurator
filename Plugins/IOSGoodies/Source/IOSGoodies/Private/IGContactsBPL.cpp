// Copyright (c) 2019 Nineva Studios

#include "IGContactsBPL.h"

#include "Async/Async.h"

#if PLATFORM_IOS
#include "IOS/Utils/IGContactUtils.h"
#endif

FOnContactsFetchedDelegate UIGContactsBPL::OnFetchedDelegate;
FOnContactSavedDelegate UIGContactsBPL::OnSavedDelegate;

void UIGContactsBPL::GetAllContacts(const FOnContactsFetchedDelegate& onFetchComplete)
{
    OnFetchedDelegate = onFetchComplete;
    
#if PLATFORM_IOS
    if ([CNContactStore class])
    {
        CNEntityType entityType = CNEntityTypeContacts;
        if ([CNContactStore authorizationStatusForEntityType:entityType] != CNAuthorizationStatusAuthorized)
        {
            CNContactStore* contactStore = [[CNContactStore alloc] init];
            [contactStore requestAccessForEntityType:entityType completionHandler:^(BOOL granted, NSError * _Nullable error) {
                if (granted)
                {
                    IGContactUtils::FetchAllContacts(OnFetchedDelegate);
                }
            }];
        }
        else
        {
            IGContactUtils::FetchAllContacts(OnFetchedDelegate);
        }
    }
#endif
}

void UIGContactsBPL::GetContactsWithName(FString name, const FOnContactsFetchedDelegate& onFetchComplete)
{
    OnFetchedDelegate = onFetchComplete;
    
#if PLATFORM_IOS
    if ([CNContactStore class])
    {
        CNEntityType entityType = CNEntityTypeContacts;
        if ([CNContactStore authorizationStatusForEntityType:entityType] != CNAuthorizationStatusAuthorized)
        {
            CNContactStore* contactStore = [[CNContactStore alloc] init];
            [contactStore requestAccessForEntityType:entityType completionHandler:^(BOOL granted, NSError* _Nullable error) {
                if (granted)
                {
                    IGContactUtils::FetchContactByName(name, OnFetchedDelegate);
                }
            }];
        }
        else
        {
            IGContactUtils::FetchContactByName(name, OnFetchedDelegate);
        }
    }
#endif
}

void UIGContactsBPL::GetContactsWithNumber(FString number, const FOnContactsFetchedDelegate& onFetchComplete)
{
    OnFetchedDelegate = onFetchComplete;
    
#if PLATFORM_IOS
    if ([CNContactStore class])
    {
        CNEntityType entityType = CNEntityTypeContacts;
        if ([CNContactStore authorizationStatusForEntityType:entityType] != CNAuthorizationStatusAuthorized)
        {
            CNContactStore* contactStore = [[CNContactStore alloc] init];
            [contactStore requestAccessForEntityType:entityType completionHandler:^(BOOL granted, NSError* _Nullable error) {
                if (granted)
                {
                    IGContactUtils::FetchContactByNumber(number, OnFetchedDelegate);
                }
            }];
        }
        else
        {
            IGContactUtils::FetchContactByNumber(number, OnFetchedDelegate);
        }
    }
#endif
}

void UIGContactsBPL::AddContact(FIGContact contact, const FOnContactSavedDelegate& onSaveResult)
{
    OnSavedDelegate = onSaveResult;
    
#if PLATFORM_IOS
    if ([CNContactStore class])
    {
        CNEntityType entityType = CNEntityTypeContacts;
        if ([CNContactStore authorizationStatusForEntityType:entityType] != CNAuthorizationStatusAuthorized)
        {
            CNContactStore* contactStore = [[CNContactStore alloc] init];
            [contactStore requestAccessForEntityType:entityType completionHandler:^(BOOL granted, NSError* _Nullable error) {
                if (granted)
                {
                    bool result = IGContactUtils::AddContact(contact);
                    AsyncTask(ENamedThreads::GameThread, [=]() {
                        OnSavedDelegate.ExecuteIfBound(result);
                    });
                } else
                {
                    AsyncTask(ENamedThreads::GameThread, [=]() {
                        OnSavedDelegate.ExecuteIfBound(false);
                    });
                }
            }];
        }
        else
        {
            bool result = IGContactUtils::AddContact(contact);
            AsyncTask(ENamedThreads::GameThread, [=]() {
                OnSavedDelegate.ExecuteIfBound(result);
            });
        }
    }
#endif
}
