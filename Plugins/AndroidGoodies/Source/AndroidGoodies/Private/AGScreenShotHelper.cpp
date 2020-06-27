// Copyright (c) 2019 Nineva Studios

#include "AGScreenShotHelper.h"
#include "AGPickersBPL.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/UnrealClient.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AGMediaUtils.h"
#endif

void UScreenShotHelper::ProcessScreenShot(int InSizeX, int InSizeY, const TArray<FColor>& InImageData)
{
#if PLATFORM_ANDROID
	TArray<uint8> bytes;
	bytes.SetNumZeroed(InSizeX * InSizeY * 4);

	for (int i = 0; i < InImageData.Num(); i++)
	{
		bytes[4 * i] = InImageData[i].A;
		bytes[4 * i + 1] = InImageData[i].R;
		bytes[4 * i + 2] = InImageData[i].G;
		bytes[4 * i + 3] = InImageData[i].B;
	}

	UAGPickersBPL::OnImageReady(AGMediaUtils::TextureFromByteArray(bytes, InSizeX, InSizeY));

	GEngine->GameViewport->OnScreenshotCaptured().RemoveAll(this);
    
	ConditionalBeginDestroy();
#endif
}
