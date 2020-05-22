// Copyright (c) 2018 Nineva Studios

#pragma once

#include "Engine/Texture2D.h"

class IGMediaUtils
{
public:

    static UIImage* ConvertTextureToImage(UTexture2D *texture);
    static UTexture2D* ConvertImageToTexture(UIImage *image);
};
