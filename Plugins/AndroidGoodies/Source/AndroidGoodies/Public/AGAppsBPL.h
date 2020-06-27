// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGAppsBPL.generated.h"

/*Class to open other apps on device and other application manipulations.*/
UCLASS()
class ANDROIDGOODIES_API UAGApps : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Open video in YouTube app if its installed, otherwise, falls back to browser.
	* @param videoId - YouTube video identifier (part that follows after "https://www.youtube.com/watch?v=")
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void OpenYoutubeVideo(FString videoId);

	/**
	* Open the Twitter profile in the app (falls back to browser if Twitter app is not installed).
	* @param profileId - Twitter profile identifier
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void OpenTwitterProfile(FString profileId);

	/**
	* Open the Instagram profile in the app (falls back to browser if Instagram app is not installed).
	* @param profileId - Instagram profile identifier
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void OpenInstagramProfile(FString profileId);

	/**
	* Open the Facebook profile in the app (falls back to browser if Facebook app is not installed).
	* @param profileId - Facebook profile identifier
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void OpenFacebookProfile(FString profileId);

	/**
	* Open the other app on device.
	* @param packageName - name of package to be opened
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void OpenAnotherApplication(FString packageName);

	/**
	* Display the prompt to uninstall the app.
	* @param packageName - name of package to be uninstalled
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void UninstallPackage(FString packageName);

	/**
	* Install the APK file from SD card.
	* @param filePath - path to APK file that is located on the devices SD card
	* @note The file MUST exist. Always check if file exists before invoking the method.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void InstallApkFromFile(FString filePath);

	/**
	* Indicates whether the device has the app installed which can place phone calls.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool HasPhoneApp();

	/**
	* Opens the dialer with the number provided.
	* @param number - phone number
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void DialPhoneNumber(FString number);

	/**
	* Places the phone call immediately.
	* @param number - phone number
	* @note To use this method android permission "android.permission.CALL_PHONE" must be granted.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void CallPhoneNumber(FString number);
};