// Copyright (c) 2019 Nineva Studios

#pragma once

#include "IGContact.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IGContactsBPL.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnContactsFetchedDelegate, const TArray<FIGContact>&, contacts);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnContactSavedDelegate, bool, result);

UCLASS()
class IOSGOODIES_API UIGContactsBPL : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    
    /**
    * Get list of all contacts.
    * @param onFetchComplete - callback function that is called after list of all contacts was fetched
    */
    UFUNCTION(BlueprintCallable, Category = "IOSGoodies | Contacts", meta = (AutoCreateRefTerm = "onFetchComplete"))
    static void GetAllContacts(const FOnContactsFetchedDelegate& onFetchComplete);
    
    /**
    * Get contacts with specified name.
    * @param name - name of all contacts to be fetched
    * @param onFetchComplete - callback function that is called after list of all contacts with specified name was fetched
    */
    UFUNCTION(BlueprintCallable, Category = "IOSGoodies | Contacts", meta = (AutoCreateRefTerm = "onFetchComplete"))
    static void GetContactsWithName(FString name, const FOnContactsFetchedDelegate& onFetchComplete);
    
    /**
    * Get contacts with specified phone number.
    * @param number - phone number of all contacts to be fetched
    * @param onFetchComplete - callback function that is called after list of all contacts with specified number was fetched
    */
    UFUNCTION(BlueprintCallable, Category = "IOSGoodies | Contacts", meta = (AutoCreateRefTerm = "onFetchComplete"))
    static void GetContactsWithNumber(FString number, const FOnContactsFetchedDelegate& onFetchComplete);
    
    /**
    * Add new item to contacts list.
    * @param contact - data structure representing new contact that should be added to device contacts list
    * @param onSaveResult - callback function that is called after contact was added to contacts list
    */
    UFUNCTION(BlueprintCallable, Category = "IOSGoodies | Contacts", meta = (AutoCreateRefTerm = "onSaveResult"))
    static void AddContact(FIGContact contact, const FOnContactSavedDelegate& onSaveResult);
    
private:

    static FOnContactsFetchedDelegate OnFetchedDelegate;
    static FOnContactSavedDelegate OnSavedDelegate;
};
