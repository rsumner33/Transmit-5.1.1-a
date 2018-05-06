#import "PCRemoteNewFileOperation.h"

@interface PCRemoteNewFolderOperation : PCRemoteNewFileOperation

@property (copy) NSDictionary *customAttributes; // allows the caller to provide custom new folder attributes

@end
