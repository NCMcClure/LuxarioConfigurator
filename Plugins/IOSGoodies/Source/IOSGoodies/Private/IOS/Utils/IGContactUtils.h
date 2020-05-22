// Copyright (c) 2019 Nineva Studios

#pragma once

#import "IGContactsBPL.h"

#import <Foundation/Foundation.h>
#import <Contacts/Contacts.h>

class IGContactUtils
{
public:
    
    static void FetchAllContacts(const FOnContactsFetchedDelegate& onFetchComplete);
    static void FetchContactByName(FString name, const FOnContactsFetchedDelegate& onFetchComplete);
    static void FetchContactByNumber(FString number, const FOnContactsFetchedDelegate& onFetchComplete);

    static bool AddContact(FIGContact contact);
    
    static FIGContact ParseContact(CNContact* contact);
};
