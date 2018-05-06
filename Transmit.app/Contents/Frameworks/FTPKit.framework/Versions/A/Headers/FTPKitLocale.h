#import <Foundation/Foundation.h>
#import <FTPKit/FTPKitDefines.h>


FTPKIT_EXTERN CFBundleRef FTPKitBundle(void);

// Function for localizing things out of the FTPKit bundle's .strings file
FTPKIT_EXTERN NSString * FTPKitLocalizedString(NSString *key);
