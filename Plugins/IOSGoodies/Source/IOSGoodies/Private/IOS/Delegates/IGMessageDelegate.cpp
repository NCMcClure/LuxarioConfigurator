// Copyright (c) 2018 Nineva Studios

#include "IGMessageDelegate.h"

@implementation IGMessageDelegate
- (void)messageComposeViewController:(MFMessageComposeViewController *)controller didFinishWithResult:(MessageComposeResult)result {
    switch (result) {
        case MessageComposeResultCancelled:
            _callbackCancelled();
            break;
        case MessageComposeResultFailed:
            _callbackFailed();
            break;
        case MessageComposeResultSent:
            _callbackSentSuccessfully();
            break;
            
        default:
            _callbackCancelled();
            break;
    }
    
    [controller dismissViewControllerAnimated:YES completion:nil];
}
@end
