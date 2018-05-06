#import <Foundation/Foundation.h>
#import "FTPKitConstants.h"


@interface NSError (FTPKitAdditions)

+ (nonnull NSError*)ftp_errorWithTitle:(nonnull NSString*)title message:(nullable NSString*)message domain:(nullable NSString*)domain code:(NSInteger)code userInfo:(nullable NSDictionary*)userInfo;
+ (nonnull NSError*)ftp_errorWithTitle:(nonnull NSString*)title message:(nullable NSString*)message code:(FTPKitErrorCode)code userInfo:(nullable NSDictionary*)userInfo;
+ (nonnull NSError*)ftp_errorWithTitle:(nonnull NSString*)title message:(nullable NSString*)message code:(FTPKitErrorCode)code;

+ (nonnull NSError*)ftp_errorWithCode:(FTPKitErrorCode)code userInfo:(nullable NSDictionary*)userInfo;

+ (nonnull  NSError*)ftp_cancelledError;
+ (nonnull NSError*)ftp_unsupportedErrorWithTitle:(nonnull NSString*)title; // preferable to the method below, allows for more user-friendly messages
+ (nonnull NSError*)ftp_unsupportedError;
+ (nonnull NSError*)ftp_authenticationErrorWithAddress:(nonnull NSString*)address;
+ (nonnull NSError*)ftp_reauthorizationErrorWithAddress:(nonnull NSString*)address;

- (void)ftp_setShouldPresent:(BOOL)flag;
- (BOOL)ftp_shouldPresent;

@end
