// Copyright (c) 2018 Nineva Studios

#include "IGShareBPL.h"

#if PLATFORM_IOS
#import <MessageUI/MessageUI.h>
#include "IOS/IOSAppDelegate.h"
#include "Utils/IGConvertors.h"
#include "Utils/IGMediaUtils.h"
#include "Utils/IGCommonUtils.h"
#include "Utils/IGSharingUtils.h"
#endif

FOnShareSuccessDelegate UIGShare::OnShareSuccessDelegate;
FOnShareErrorDelegate UIGShare::OnShareErrorDelegate;
FOnShareCancelDelegate UIGShare::OnShareCancelDelegate;
FOnSavedDraftDelegate UIGShare::OnSavedDraftDelegate;

UIGShare::UIGShare(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UIGShare::ShareText(FString message, int posX, int posY,
    const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback)
{
	OnShareSuccessDelegate = onSuccessCallback;
	OnShareErrorDelegate = onErrorCallback;

#if PLATFORM_IOS
	NSMutableArray *array = [NSMutableArray new];

	NSString *messageStr = message.GetNSString();
	[array addObject:messageStr];
	
	IGSharingUtils::PresentShareViewWithItems(array, posX, posY, OnShareSuccessDelegate, OnShareErrorDelegate);
#endif
}

void UIGShare::ShareImage(UTexture2D *texture, int posX, int posY,
    const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback)
{
	OnShareSuccessDelegate = onSuccessCallback;
	OnShareErrorDelegate = onErrorCallback;
	
#if PLATFORM_IOS
	NSMutableArray *array = [NSMutableArray new];
	
	if (texture != nil)
	{
		UIImage *image = IGMediaUtils::ConvertTextureToImage(texture);
		[array addObject:image];
	}
	
	IGSharingUtils::PresentShareViewWithItems(array, posX, posY, OnShareSuccessDelegate, OnShareErrorDelegate);
#endif
}

void UIGShare::ShareLink(FString link, int posX, int posY,
    const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback)
{
	OnShareSuccessDelegate = onSuccessCallback;
	OnShareErrorDelegate = onErrorCallback;
	
#if PLATFORM_IOS
	NSMutableArray *array = [NSMutableArray new];
	
	NSString *linkStr = link.GetNSString();
	NSURL *url = [NSURL URLWithString:linkStr];
	[array addObject:url];
	
	IGSharingUtils::PresentShareViewWithItems(array, posX, posY, OnShareSuccessDelegate, OnShareErrorDelegate);
#endif
}

void UIGShare::ShareTextWithImage(FString message, UTexture2D *texture, int posX, int posY,
    const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback)
{
	OnShareSuccessDelegate = onSuccessCallback;
	OnShareErrorDelegate = onErrorCallback;

#if PLATFORM_IOS
	NSMutableArray *array = [NSMutableArray new];
	
	NSString *messageStr = message.GetNSString();
	[array addObject:messageStr];

	if (texture != nil) {
		UIImage *image = IGMediaUtils::ConvertTextureToImage(texture);
		[array addObject:image];
	}
	
	IGSharingUtils::PresentShareViewWithItems(array, posX, posY, OnShareSuccessDelegate, OnShareErrorDelegate);
#endif
}

void UIGShare::ShareTextWithLink(FString message, FString link, int posX, int posY,
    const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback)
{
	OnShareSuccessDelegate = onSuccessCallback;
	OnShareErrorDelegate = onErrorCallback;

#if PLATFORM_IOS
	NSMutableArray *array = [NSMutableArray new];
	
	NSString *messageStr = message.GetNSString();
	[array addObject:messageStr];
	
	NSString *linkStr = link.GetNSString();
	NSURL *url = [NSURL URLWithString:linkStr];
	[array addObject:url];
	
	IGSharingUtils::PresentShareViewWithItems(array, posX, posY, OnShareSuccessDelegate, OnShareErrorDelegate);
#endif
}

void UIGShare::ShareTextWithImageAndLink(FString message, UTexture2D *texture, FString link, int posX, int posY,
    const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback)
{
	OnShareSuccessDelegate = onSuccessCallback;
	OnShareErrorDelegate = onErrorCallback;
	
#if PLATFORM_IOS
	NSMutableArray *array = [NSMutableArray new];
	
	NSString *messageStr = message.GetNSString();
	[array addObject:messageStr];
	
	NSString *linkStr = link.GetNSString();
	NSURL *url = [NSURL URLWithString:linkStr];
	[array addObject:url];
	
	if (texture != nil) {
		UIImage *image = IGMediaUtils::ConvertTextureToImage(texture);
		[array addObject:image];
	}
	
	IGSharingUtils::PresentShareViewWithItems(array, posX, posY, OnShareSuccessDelegate, OnShareErrorDelegate);
#endif
}

void UIGShare::SendSms(FString phoneNumber, FString msgText,
	const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback, const FOnShareCancelDelegate &onCancelCallback)
{
	OnShareSuccessDelegate = onSuccessCallback;
	OnShareErrorDelegate = onErrorCallback;
	OnShareCancelDelegate = onCancelCallback;

#if PLATFORM_IOS
	NSString *phoneNumberStr = phoneNumber.GetNSString();
    NSString *msgTextStr = msgText.GetNSString();

	IGMessageDelegate *MessageDelegate = IGSharingUtils::CreateMessageDelegate(OnShareSuccessDelegate, OnShareErrorDelegate, OnShareCancelDelegate);

    MFMessageComposeViewController *messageController = [[MFMessageComposeViewController alloc] init];
    messageController.messageComposeDelegate = MessageDelegate;

    NSArray *recipients = @[phoneNumberStr];
    [messageController setRecipients:recipients];
    [messageController setBody:msgTextStr];

    [[IOSAppDelegate GetDelegate].IOSController presentViewController:messageController animated:YES completion:nil];
#endif
}

void UIGShare::SendSMSViaDefaultApp(FString phoneNumber, FString msgText)
{
#if PLATFORM_IOS
	NSString *phoneNumberStr = phoneNumber.GetNSString();
	NSString *msgTextStr = IGConvertors::ConvertFStringToEncodedNSString(msgText);

	NSString *urlString = [NSString stringWithFormat:@"sms:%@&body=%@", phoneNumberStr, msgTextStr];
	IGCommonUtils::OpenUrl(urlString);
#endif
}

void UIGShare::SendEmailViaDefaultApp(FString subject, FString body, TArray<FString> recipients, TArray<FString> cc, TArray<FString> bcc)
{
#if PLATFORM_IOS
	NSArray *recipientsArray = IGConvertors::ConvertToNSArray(recipients);
	NSString *recipientsStr = [[recipientsArray valueForKey:@"description"] componentsJoinedByString:@","];
	
	NSString *subjectStr = IGConvertors::ConvertFStringToEncodedNSString(subject);
	NSString *bodyStr = IGConvertors::ConvertFStringToEncodedNSString(body);
	
	NSMutableString *urlString = [NSMutableString stringWithString:[NSString stringWithFormat:@"mailto:%@?subject=%@&body=%@", recipientsStr, subjectStr, bodyStr]];
    
    if (cc.Num() > 0) {
		NSArray *ccArray = IGConvertors::ConvertToNSArray(cc);
		NSString *ccStr = [[ccArray valueForKey:@"description"] componentsJoinedByString:@","];
		[urlString appendString: [NSString stringWithFormat:@"&cc=%@", ccStr]];
    }
    if (bcc.Num() > 0) {
		NSArray *bccArray = IGConvertors::ConvertToNSArray(bcc);
		NSString *bccStr = [[bccArray valueForKey:@"description"] componentsJoinedByString:@","];
		[urlString appendString: [NSString stringWithFormat:@"&bcc=%@", bccStr]];
    }
	
	FString url = FString(urlString);
	IGCommonUtils::OpenUrl(urlString);
#endif
}

void UIGShare::SendEmail(FString subject, FString body, UTexture2D *texture,
	TArray<FString> recipients, TArray<FString> cc, TArray<FString> bcc,
	const FOnShareSuccessDelegate &onSuccessCallback, const FOnShareErrorDelegate &onErrorCallback,
	const FOnShareCancelDelegate &onCancelCallback, const FOnSavedDraftDelegate &onSavedDraftCallback)
{
	OnShareSuccessDelegate = onSuccessCallback;
	OnShareErrorDelegate = onErrorCallback;
	OnShareCancelDelegate = onCancelCallback;
	OnSavedDraftDelegate = onSavedDraftCallback;

#if PLATFORM_IOS
	MFMailComposeViewController *mailVC = [[MFMailComposeViewController alloc] init];
		
	IGMailDelegate *MailDelegate = IGSharingUtils::CreateMailDelegate(OnShareSuccessDelegate, OnShareErrorDelegate, OnShareCancelDelegate, OnSavedDraftDelegate);
	mailVC.mailComposeDelegate = MailDelegate;
		
	[mailVC setSubject:subject.GetNSString()];
	[mailVC setMessageBody:body.GetNSString() isHTML:NO];
	[mailVC setToRecipients:IGConvertors::ConvertToNSArray(recipients)];
	if (cc.Num() > 0) {
		[mailVC setCcRecipients:IGConvertors::ConvertToNSArray(cc)];
	}
	if (bcc.Num() > 0) {
		[mailVC setBccRecipients:IGConvertors::ConvertToNSArray(bcc)];
	}
	
	if (texture != nil) {
		UIImage *image = IGMediaUtils::ConvertTextureToImage(texture);
		NSData *dataForImage = UIImagePNGRepresentation(image);
		[mailVC  addAttachmentData: dataForImage mimeType: @"image/png" fileName: @"Image"];
	}

	dispatch_async(dispatch_get_main_queue(), ^{
		[[IOSAppDelegate GetDelegate].IOSController presentViewController:mailVC animated:YES completion:NULL];
	});
#endif
}

bool UIGShare::CanSendEmail()
{
	bool result = false;
#if PLATFORM_IOS
	result = [MFMailComposeViewController canSendMail];
#endif
	return result;
}

bool UIGShare::CanSendSMS()
{
	bool result = false;
#if PLATFORM_IOS
	result = [MFMessageComposeViewController canSendText];
#endif
	return result;
}
