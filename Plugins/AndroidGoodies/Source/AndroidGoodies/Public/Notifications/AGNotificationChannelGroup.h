// Copyright (c) 2019 Nineva Studios

#pragma once

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#endif

#include "AGDeviceInfoBPL.h"
#include "AGNotificationChannel.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotificationChannelGroup.generated.h"

UCLASS(BlueprintType)
class UAGNotificationChannelGroup : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UAGNotificationChannelGroup();

	/**
	* Constructor.
	*
	* @param id - the id of the group. Must be unique per package. The value may be truncated if it is too long.
	* @param name - the user visible name of the group. The recommended maximum length is 40 characters; the value may be truncated if it is too long.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	static UAGNotificationChannelGroup* NewNotificationChannelGroup(FString id, FString name);

	/**
	* Get the id of this group.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	FString GetId();

	/**
	* Get the user visible name of this group.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	FString GetName();

	/**
	* Get the user visible description of this group.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	FString GetDescription();

	/**
	* Set the user visible description of this group.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	UAGNotificationChannelGroup* SetDescription(FString description);

	/**
	* Get whether or not notifications posted to channels belonging to this group are blocked.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	bool IsBlocked();

	/**
	* Get the list of channels that belong to this group
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies | Notifications")
	TArray<UAGNotificationChannel*> GetChannels();

#if PLATFORM_ANDROID
	jobject JavaNotificationGroupObject;
#endif
};
