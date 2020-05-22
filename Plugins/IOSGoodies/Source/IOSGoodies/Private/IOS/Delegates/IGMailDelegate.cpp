// Copyright (c) 2018 Nineva Studios

#include "IGMailDelegate.h"

@implementation IGMailDelegate
- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error
{
	switch (result) {
		case MFMailComposeResultSent:
			_callbackSentSuccessfully();
			break;
		case MFMailComposeResultSaved:
			_callbackSaved();
			break;
		case MFMailComposeResultCancelled:
			_callbackCancelled();
			break;
		case MFMailComposeResultFailed:
			_callbackFailed();
			break;
		default:
			_callbackFailed();
			break;
	}
	
	[controller dismissViewControllerAnimated:YES completion:NULL];
}
@end
