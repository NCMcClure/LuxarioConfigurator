// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "IGAppsBPL.generated.h"

/*
 * Class for application interactions.
 */
UCLASS()
class IOSGOODIES_API UIGApps : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	/**
	 * Open the screen dedicated to you application settings where user can enable permissions, etc.
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void OpenAppSettings();
	
	/**
	 * Open the YouTube video in the YouTube application.
	 * If the application is not installed, opens the link in browser instead.
	 *
	 * @param id - ID of the video in the link.
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void OpenYouTubeVideo(FString id);
	
	/**
	 * Start the face time video call.
	 *
	 * @param id - user identifier
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void StartFaceTimeVideoCall(FString id);
	
	/**
	 * Start the face time audio call.
	 *
	 * @param id - user identifier
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void StartFaceTimeAudioCall(FString id);
	
	/**
	 * Show the dialer dialogue that prompts the user to make a call.
	 *
	 * @param number - phone number to call
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void OpenDialer(FString number);
	
	/**
	 * Open existing application AppStore page.
	 *
	 * @param appId - ID of the app. To find the ID of the existing application copy it from iTunes link
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void OpenAppOnAppStore(FString appId);
	
	/**
	 * Request a rating for the current app on the AppStore.
	 */
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void RequestRating();
};
