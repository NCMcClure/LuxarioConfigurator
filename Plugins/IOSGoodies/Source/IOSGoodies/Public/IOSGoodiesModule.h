// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class IOSGoodiesModule : public IModuleInterface
{
public:

	static inline IOSGoodiesModule& Get()
    {
        return FModuleManager::LoadModuleChecked<IOSGoodiesModule>("IOSGoodies");
    }
    
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("IOSGoodies");
    }
};
