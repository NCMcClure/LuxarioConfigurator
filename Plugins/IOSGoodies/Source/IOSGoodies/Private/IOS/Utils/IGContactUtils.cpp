// Copyright (c) 2019 Nineva Studios

#include "IGContactUtils.h"

#include "Async/Async.h"

void IGContactUtils::FetchAllContacts(const FOnContactsFetchedDelegate& onFetchComplete)
{
    NSError* contactError;
    CNContactStore* addressBook = [[CNContactStore alloc]init];
    [addressBook containersMatchingPredicate:[CNContainer predicateForContainersWithIdentifiers: @[addressBook.defaultContainerIdentifier]] error:&contactError];
    NSArray* keysToFetch = @[CNContactPhoneNumbersKey, [CNContactFormatter descriptorForRequiredKeysForStyle: CNContactFormatterStyleFullName]];
    CNContactFetchRequest* request = [[CNContactFetchRequest alloc] initWithKeysToFetch:keysToFetch];
    
    NSMutableArray *contacts = [NSMutableArray new];
    
    BOOL success = [addressBook enumerateContactsWithFetchRequest:request error:&contactError usingBlock:^(CNContact* __nonnull contact, BOOL* __nonnull stop) {
                        [contacts addObject:contact];
                    }];
    
    TArray<FIGContact> fetchedContacts;
    
    for (CNContact* contact in contacts)
    {
        fetchedContacts.Add(ParseContact(contact));
    }
    
    AsyncTask(ENamedThreads::GameThread, [=]() {
        onFetchComplete.ExecuteIfBound(fetchedContacts);
    });
}

void IGContactUtils::FetchContactByName(FString name, const FOnContactsFetchedDelegate& onFetchComplete)
{
    CNContactStore* addressBook = [[CNContactStore alloc]init];
    
    NSArray* keysToFetch = @[CNContactPhoneNumbersKey, [CNContactFormatter descriptorForRequiredKeysForStyle: CNContactFormatterStyleFullName]];
    NSError* contactError;
    NSString* nameString = name.GetNSString();
    
    NSArray<CNContact*>* contacts = [addressBook unifiedContactsMatchingPredicate: [CNContact predicateForContactsMatchingName: nameString]
                                        keysToFetch: keysToFetch
                                        error: &contactError];
    
    TArray<FIGContact> fetchedContacts;
    
    for (CNContact* contact in contacts) {
        fetchedContacts.Add(ParseContact(contact));
    }
    
    AsyncTask(ENamedThreads::GameThread, [=]() {
        onFetchComplete.ExecuteIfBound(fetchedContacts);
    });
}

void IGContactUtils::FetchContactByNumber(FString number, const FOnContactsFetchedDelegate& onFetchComplete)
{
    CNContactStore* addressBook = [[CNContactStore alloc]init];
    
    TArray<FIGContact> fetchedContacts;
    
    NSError* contactError;
    [addressBook containersMatchingPredicate:[CNContainer predicateForContainersWithIdentifiers: @[addressBook.defaultContainerIdentifier]] error:&contactError];
    NSArray* keysToFetch = @[CNContactPhoneNumbersKey, [CNContactFormatter descriptorForRequiredKeysForStyle: CNContactFormatterStyleFullName]];
    CNContactFetchRequest* request = [[CNContactFetchRequest alloc] initWithKeysToFetch:keysToFetch];
    
    NSMutableArray *contacts = [NSMutableArray new];
    
    BOOL success = [addressBook enumerateContactsWithFetchRequest:request error:&contactError usingBlock:^(CNContact* __nonnull contact, BOOL* __nonnull stop) {
        [contacts addObject:contact];
    }];
    
    for (CNContact* contact in contacts) {
        FIGContact unrealContact = ParseContact(contact);
        if (unrealContact.PhoneNumbers.Contains(number)) {
            fetchedContacts.Add(unrealContact);
        }
    }
    
    AsyncTask(ENamedThreads::GameThread, [=]() {
        onFetchComplete.ExecuteIfBound(fetchedContacts);
    });
}

bool IGContactUtils::AddContact(FIGContact contact)
{
    CNContactStore* addressBook = [[CNContactStore alloc] init];
    CNMutableContact* cont = [[CNMutableContact alloc] init];
    cont.givenName = contact.DisplayName.GetNSString();
    
    NSMutableArray<CNLabeledValue*>* numbers = [[NSMutableArray alloc] init];
    
    for (int i = 0; i < contact.PhoneNumbers.Num(); i++)
    {
        NSString* numberString = contact.PhoneNumbers[i].GetNSString();
        CNPhoneNumber* phoneNumber = [[CNPhoneNumber alloc] initWithStringValue: numberString];
        CNLabeledValue* labeledValue = [CNLabeledValue labeledValueWithLabel:CNLabelHome value: phoneNumber];
        [numbers addObject: labeledValue];
    }
    
    cont.phoneNumbers = numbers;
    
    CNSaveRequest* request = [[CNSaveRequest alloc] init];
    [request addContact:cont toContainerWithIdentifier:nil];
    
    NSError* saveError;
    return [addressBook executeSaveRequest:request error:&saveError];
}

FIGContact IGContactUtils::ParseContact(CNContact* contact)
{
    FIGContact unrealContact;
    
    NSString* displayName = [CNContactFormatter stringFromContact:contact style:CNContactFormatterStyleFullName];
    unrealContact.DisplayName = FString(displayName);
    
    if(contact.phoneNumbers.count > 0)
    {
        for (CNLabeledValue<CNPhoneNumber*>* number in contact.phoneNumbers)
        {
            unrealContact.PhoneNumbers.Add(FString(((CNPhoneNumber *)number.value).stringValue));
        }
    }
    
    return unrealContact;
}
