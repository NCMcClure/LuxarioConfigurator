// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InstagramBlueprintStatics.generated.h"

/**
 * 
 */
UCLASS()
class CONFIGURATOR_API UInstagramBlueprintStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static void ShareToInstagram(class UTexture2D* Texture);

	UFUNCTION(BlueprintCallable)
	static class UTexture2D* CropTexture(class UTexture2D* Texture, const int32 Width, const int32 Height, int32 OffsetX = 0, int32 OffsetY = 0);

	UFUNCTION(BlueprintPure)
	static bool IsInstagramAvailable();
private:
	static TArray<FColor> GetTextureColorData(class UTexture2D* Texture);
};
