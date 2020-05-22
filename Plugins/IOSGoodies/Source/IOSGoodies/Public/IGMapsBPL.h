// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "IGMapTransportType.h"
#include "IGMapViewType.h"
#include "IGMapsBPL.generated.h"

/**
 * Class for passing querries to Apple Maps application.
 */
UCLASS()
class IOSGOODIES_API UIGMapsBPL : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	/**
	 * Open the apple maps location.
	 *
	 * @param latitude - latitude of location to open. Should be between -90 and 90, inclusive
	 * @param longitude - longitude of location to open. SHould be between -180 and 180, inclusive
	 * @param label - label title
	 * @param viewType - map view type
	 */
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies")
	static void OpenMapLocation(float latitude, float longitude, FString label, MapViewType viewType);
	
	/**
	 * Open the apple maps location.
	 *
	 * @param address - address to open
	 * @param label - label title
	 * @param viewType - map view type
	 */
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies")
	static void OpenMapAddress(FString address, FString label, MapViewType viewType);
	
	/**
	 * Open apple maps maps application with direction to destination.
	 *
	 * @param destinationAddress - destination address
	 * @param sourceAddress - source address
	 * @param transportType - transport type
	 * @param viewType - map view type
	 */
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies")
	static void GetDirections(FString destinationAddress, FString sourceAddress, TransportType transportType, MapViewType viewType);
	
	/**
	 * Perform the search in apple maps application.
	 *
	 * @param query - the query.
	 * This parameter is treated as if its value had been typed into the Maps search field by the user
	 * @param viewType - map view type
	 */
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies")
	static void PerformSearch(FString query, MapViewType viewType);
	
	/**
	 * Perform the search with provided query near specified location.
	 *
	 * @param query - the query.
	 * This parameter is treated as if its value had been typed into the Maps search field by the user
	 * @param latitude - latitude of location to open. Should be between -90 and 90, inclusive
	 * @param longitude - longitude of location to open. SHould be between -180 and 180, inclusive
	 * @param zoom - map zoom. Should be between 2 and 23, inclusive
	 * @param viewType - map view type
	 */
	UFUNCTION(BlueprintCallable, Category = "IOSGoodies")
	static void PerformSearchNearLocation(FString query, float latitude, float longitude, int zoom, MapViewType viewType);
};
