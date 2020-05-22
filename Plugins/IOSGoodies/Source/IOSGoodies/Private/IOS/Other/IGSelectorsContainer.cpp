// Copyright (c) 2019 Nineva Studios

#import "IGSelectorsContainer.h"

@implementation IGSelectorsContainer

- (void)thisImage:(UIImage *)image hasBeenSavedInPhotoAlbumWithError:(NSError *)error usingContextInfo:(void*)ctxInfo {
    if (error) {
        _onError();
    } else {
        _onImageSaved();
    }
}

@end
