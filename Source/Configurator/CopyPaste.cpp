// Fill out your copyright notice in the Description page of Project Settings.


#include "CopyPaste.h"
#include "Configurator.h"

void UCopyPaste::Copy(const FString& ToClipboard)
{
	FPlatformMisc::ClipboardCopy(*ToClipboard);
}

