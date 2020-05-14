// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CopyPaste.generated.h"

/**
 * 
 */
UCLASS()
class CONFIGURATOR_API UCopyPaste : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "System")
	static void Copy(const FString& ToClipboard);
	
};
