#import "FTPKitConstants.h"
#import "PCRemoteTransferOperation.h"

@class PCFileNode;
@class PCRemoteFolderNode;

@interface PCRemoteUploadOperation : PCRemoteTransferOperation

@property (copy) NSString *customFilename;

- (NSError*)uploadNode:(PCFileNode*)sourceNode to:(PCRemoteFolderNode*)destinationFolder newName:(NSString*)newName;

@end
