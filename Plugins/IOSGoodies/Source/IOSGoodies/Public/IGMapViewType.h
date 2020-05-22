// Copyright (c) 2018 Nineva Studios

#pragma once

UENUM(BlueprintType)
enum MapViewType
{
	Standard = 0 UMETA(DisplayName = "Standard"),
	Satellite = 1 UMETA(DisplayName = "Satellite"),
	Hybrid = 2 UMETA(DisplayName = "Hybrid"),
	Transit = 3 UMETA(DisplayName = "Transit"),
};
