// Copyright (c) 2019 Nineva Studios

#pragma once

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#endif

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGNotification.generated.h"

UCLASS()
class UAGNotification : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UAGNotification();


#if PLATFORM_ANDROID
	void Init(jobject javaNotification);

	jobject JavaNotificationObject;
#endif
};