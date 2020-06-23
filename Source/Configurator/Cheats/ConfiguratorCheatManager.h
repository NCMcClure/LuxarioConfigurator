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
///storage/self/primary/UE4Game/Configurator/Configurator/Content/Non-Assets
	UFUNCTION(Exec)
	void ConfiguratorShareSampleToInstagram();	
};
