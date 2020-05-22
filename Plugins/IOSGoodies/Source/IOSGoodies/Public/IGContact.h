// Copyright (c) 2019 Nineva Studios

#pragma once

#include "IGContact.generated.h"

USTRUCT(BlueprintType)
struct IOSGOODIES_API FIGContact
{
    GENERATED_USTRUCT_BODY()
    
public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "iOSGoodies | Contacts")
    FString DisplayName;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "iOSGoodies | Contacts")
    TArray<FString> PhoneNumbers;
};
