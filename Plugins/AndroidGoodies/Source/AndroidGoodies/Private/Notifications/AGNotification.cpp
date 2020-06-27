// Copyright (c) 2019 Nineva Studios

#include "Notifications/AGNotification.h"


UAGNotification::~UAGNotification()
{
	UE_LOG(LogTemp, Warning, TEXT("ANDROIDGOODIES => UAGNotification::~UAGNotification()"));
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(JavaNotificationObject);
	JavaNotificationObject = nullptr;
#endif
}

#if PLATFORM_ANDROID
void UAGNotification::Init(jobject javaNotification)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	JavaNotificationObject = Env->NewGlobalRef(javaNotification);
}
#endif