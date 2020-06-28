#pragma once

#if PLATFORM_ANDROID

FString GetStorageFilePath(const FString& FileName);
void PostToInstagram(const FString& Message, const FString& Path);
bool IsInstagramInstalled();

#endif