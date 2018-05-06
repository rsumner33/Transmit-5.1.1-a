#import "PCRemoteUploadOperation.h"

@class PCRemoteFolderNode;

@interface PCRemoteNewFileOperation : PCRemoteUploadOperation

@property (retain) NSDate *customModificationDate;

// pass in nil to get default unique name
- (id)initWithName:(NSString*)inName destinationProvider:(NSObject <PCOperationPathProvider>*)destinationProvider;

- (NSString*)defaultNewItemName;

@end
