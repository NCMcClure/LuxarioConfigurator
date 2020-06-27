// Copyright (c) 2019 Nineva Studios

#pragma once

#include "Engine/EngineTypes.h"
#include "AndroidGoodiesSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class ANDROIDGOODIES_API UAndroidGoodiesSettings : public UObject
{
	GENERATED_UCLASS_BODY()

	void ConvertDirectoryPath(FDirectoryPath AndroidDrawablesFolder);

	FString ConvertedDirectoryPath;

public:
	/** Folder, files from which should be copied to the "../Android/res/drawable" folder */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings | Drawables")
	FDirectoryPath AndroidDrawablesFolder;

	/** Add send SMS permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings | Permissions")
	bool sendSmsPermission;

	/** Add set alarm permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings | Permissions")
	bool setAlarmPermission;

	/** Add camera permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings | Permissions")
	bool cameraPermission;

	/** Add flashlight permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings | Permissions")
	bool flashlightPermission;

	/** Add vibrate permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings | Permissions")
	bool vibratePermission;

	/** Add call phone permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings | Permissions")
	bool callPhonePermission;

	/** Add read phone state permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings | Permissions")
	bool readPhoneStatePermission;

	/** Add read contact permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings | Permissions")
	bool readContactsPermission;

	/** Add write contact permission to Android Manifest */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Android Goodies Settings | Permissions")
	bool writeContactsPermission;
};
