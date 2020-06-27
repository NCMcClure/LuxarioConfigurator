// Copyright (c) 2018 Nineva Studios

#include "AGMediaUtils.h"

#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "HAL/FileManager.h"
#include "Modules/ModuleManager.h"
#include "Runtime/Launch/Resources/Version.h"

static const int THEME_DEFAULT = 16974126;
static const int THEME_HOLO_DARK = 2;
static const int THEME_HOLO_LIGHT = 3;
static const int THEME_DEVICE_DEFAULT_DARK = 4;
static const int THEME_DEVICE_DEFAULT_LIGHT = 5;
static const int THEME_DEVICE_DEFAULT_DIALOG_ALERT = 16974545;
static const int THEME_DEVICE_DEFAULT_LIGHT_DIALOG_ALERT = 16974546;

FString AGMediaUtils::GenerateTempImageFilePath()
{
	FString fileName;	

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass ShareClass = FAndroidApplication::FindJavaClass("com/ninevastudios/androidgoodies/AGShare");
	jmethodID ShareImageMethod = FJavaWrapper::FindStaticMethod(Env, ShareClass, "shareImage", "(Landroid/app/Activity;Ljava/lang/String;ZLjava/lang/String;)V", bIsOptional);

	jmethodID GetExternalPictureDirMethod = FJavaWrapper::FindStaticMethod(Env, ShareClass, "getExternalPicturesDirectory", "()Ljava/lang/String;", bIsOptional);

	jstring path = static_cast<jstring>(Env->CallStaticObjectMethod(ShareClass, GetExternalPictureDirMethod));

	const char * UTFString = Env->GetStringUTFChars(path, nullptr);
	fileName = UTF8_TO_TCHAR(UTFString);
	Env->ReleaseStringUTFChars(path, UTFString);

	FGuid guid = FGuid::NewGuid();
	fileName += ("/" + guid.ToString() + ".png");

	return fileName;
}

FString AGMediaUtils::SaveTextureToTempFile(UTexture2D* texture)
{
	FString fileName = AGMediaUtils::GenerateTempImageFilePath();	

	int w = texture->GetSizeX();
	int h = texture->GetSizeY();

	bool isBGRA = texture->PlatformData->PixelFormat == PF_B8G8R8A8;

	const FColor* FormatedImageData = reinterpret_cast<const FColor*>(texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY));

	TArray<FColor> colorArray;
	colorArray.SetNumZeroed(w*h);

	for (int32 X = 0; X < w; X++)
	{
		for (int32 Y = 0; Y < h; Y++)
		{
			colorArray[Y * w + X] = FormatedImageData[Y * w + X];
		}
	}

	texture->PlatformData->Mips[0].BulkData.Unlock();

	EImageCompressionQuality LocalCompressionQuality = EImageCompressionQuality::Uncompressed;

	IImageWrapperModule* ImageWrapperModule = FModuleManager::LoadModulePtr<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWriter = ImageWrapperModule->CreateImageWrapper(EImageFormat::PNG);

	const size_t BitsPerPixel = (sizeof(FColor) / 4) * 8;
	const ERGBFormat SourceChannelLayout = isBGRA ? ERGBFormat::BGRA : ERGBFormat::RGBA;

	ImageWriter->SetRaw((void*)&colorArray[0], sizeof(FColor)* w * h, w, h, SourceChannelLayout, BitsPerPixel);

	IFileManager* FileManager = &IFileManager::Get();
	FArchive* Ar = FileManager->CreateFileWriter(fileName.GetCharArray().GetData());

	if (Ar != nullptr)
	{

#if ENGINE_MINOR_VERSION >= 25
		const TArray64<uint8>& CompressedData = ImageWriter->GetCompressed((int32)LocalCompressionQuality);
#else
		const TArray<uint8>& CompressedData = ImageWriter->GetCompressed((int32)LocalCompressionQuality);
#endif

		int32 CompressedSize = CompressedData.Num();
		Ar->Serialize((void*)CompressedData.GetData(), CompressedSize);
		delete Ar;
	}

	return fileName;
}

int AGMediaUtils::GetDialogTheme(DialogTheme theme)
{
	if (theme == DialogTheme::DefaultTheme)
	{
		return THEME_DEFAULT;
	}

	int SdkInt = UAGDeviceInfo::GetSdkInt();

	if (SdkInt >= 22)
	{
		if (theme == DialogTheme::DarkTheme)
		{
			return THEME_DEVICE_DEFAULT_DIALOG_ALERT;
		}
		else
		{
			return THEME_DEVICE_DEFAULT_LIGHT_DIALOG_ALERT;
		}
	}

	if (SdkInt >= 14)
	{
		if (theme == DialogTheme::DarkTheme)
		{
			return THEME_DEVICE_DEFAULT_DARK;
		}
		else
		{
			return THEME_DEVICE_DEFAULT_LIGHT;
		}
	}

	if (SdkInt >= 11)
	{
		if (theme == DialogTheme::DarkTheme)
		{
			return THEME_HOLO_DARK;
		}
		else
		{
			return THEME_HOLO_LIGHT;
		}
	}

	return THEME_DEFAULT;
}

UTexture2D* AGMediaUtils::TextureFromByteArray(TArray<uint8> bytes, int width, int height)
{
	UTexture2D* result = UTexture2D::CreateTransient(width, height, PF_R8G8B8A8);

	FColor* MipData = (FColor*)result->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	for (int i = 0; i < bytes.Num() / 4; i++)
	{
		MipData[i].A = bytes[4 * i];
		MipData[i].B = bytes[4 * i + 1];
		MipData[i].G = bytes[4 * i + 2];
		MipData[i].R = bytes[4 * i + 3];
	}
	result->PlatformData->Mips[0].BulkData.Unlock();	
	result->UpdateResource();

	return result;
}

TArray<uint8> AGMediaUtils::ByteArrayFromTexture(UTexture2D* image)
{
	bool isBGRA = image->PlatformData->PixelFormat == PF_B8G8R8A8;

	FColor* MipData = (FColor*)image->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY);
	TArray<uint8> bytes;
	int w = image->GetSizeX();
	int h = image->GetSizeY();
	for (int i = 0; i < w * h; i++)
	{
		bytes.Add(isBGRA ? MipData[i].R : MipData[i].B);
		bytes.Add(MipData[i].G);
		bytes.Add(isBGRA ? MipData[i].B : MipData[i].R);
		bytes.Add(MipData[i].A);
	}
	image->PlatformData->Mips[0].BulkData.Unlock();
	image->UpdateResource();

	return bytes;
}