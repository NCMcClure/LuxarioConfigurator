// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dom/JsonObject.h"
#include "LuxarioJsonObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CONFIGURATOR_API ULuxarioJsonObject : public UObject
{
	GENERATED_BODY()
public:
	virtual void PostInitProperties() override;
	
	UFUNCTION(BlueprintCallable)
	ULuxarioJsonObject* AddFloatProperty(const FString& Name, float Value);
	UFUNCTION(BlueprintCallable)
	ULuxarioJsonObject* AddStringProperty(const FString& Name, const FString& Value);
	UFUNCTION(BlueprintPure)
	FString ToString() const;
	UFUNCTION(BlueprintPure)
	FString ToBase64() const;
protected:
	TSharedPtr<FJsonObject> JsonObject;
};
