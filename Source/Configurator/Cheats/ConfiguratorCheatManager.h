// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "ConfiguratorCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class CONFIGURATOR_API UConfiguratorCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Exec)
	void ConfiguratorShareSampleToInstagram();

	/** The FName that is expected is the exact same format as when you right click on asset -> Copy Reference! You can directly paste copied references into this node! IsValid lets you know if the path was correct or not and I was able to load the object. MAKE SURE TO SAVE THE RETURNED OBJECT AS A VARIABLE. Otherwise your shiny new asset will get garbage collected. I recommend you cast the return value to the appropriate object and then promote it to a variable :)  -Rama */
	UFUNCTION(BlueprintCallable, Category = "Victory BP Library|Misc")
	static UObject* LoadObjectFromAssetPath(TSubclassOf<UObject> ObjectClass, FName Path, bool& IsValid);
};
