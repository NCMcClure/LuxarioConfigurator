// Copyright (c) 2019 Nineva Studios

#include "IGImagePickerDelegate.h"

@implementation IGImagePickerDelegate {
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<NSString *, id> *)info {
	_imagePicked(info);
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
	if (_imagePickCancelled) {
		_imagePickCancelled();
	}
}
@end
