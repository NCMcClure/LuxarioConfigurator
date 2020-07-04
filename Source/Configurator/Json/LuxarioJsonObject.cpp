// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxarioJsonObject.h"

#include "Serialization/JsonWriter.h"
#include "Misc/Base64.h"

void ULuxarioJsonObject::PostInitProperties()
{
    Super::PostInitProperties();
    JsonObject = MakeShareable(new FJsonObject);
}

ULuxarioJsonObject* ULuxarioJsonObject::AddFloatProperty(const FString& Name, float Value)
{
    JsonObject->SetNumberField(Name, Value);
    return this;
}

ULuxarioJsonObject* ULuxarioJsonObject::AddStringProperty(const FString& Name, const FString& Value)
{
    JsonObject->SetStringField(Name, Value);
    return this;
}

ULuxarioJsonObject* ULuxarioJsonObject::AddBoolProperty(const FString& Name, bool Value)
{
    JsonObject->SetBoolField(Name, Value);
    return this;
}

FString ULuxarioJsonObject::ToString() const
{
    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    return OutputString;
}

FString ULuxarioJsonObject::ToBase64() const
{
    return FBase64::Encode(ToString());
}
