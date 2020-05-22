// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "IGImpactStrength.h"
#include "IGNotificationType.h"
#include "IGHapticsBPL.generated.h"

/**
 * Class for haptic feedbacks and vibrations
 */
UCLASS()
class IOSGOODIES_API UIGHaptics : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	/**
	* Check if device supports haptic feedbacks.
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static bool IsHapticFeedbackSupported();
	
	/**
	* Send the notification haptic feedback.
	* @param type - type of notification
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void SendNotificationHapticFeedback(NotificationType type);
	
	/**
	* Send the selection haptic feedback.
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void SendSelectionHapticFeedback();
	
	/**
	* Send the impact haptic feedback.
	* @param strength - impact strength
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void SendImpactHapticFeedback(ImpactStrength strength);
	
	/**
	* Vibrate with standard vibration pattern.
	*/
	UFUNCTION(BlueprintCallable, Category = "iOSGoodies")
	static void Vibrate();
};
	
