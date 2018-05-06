#import "FTPKitConstants.h"
#import "PCRemoteTransferOperation.h"

@class PCFolderNode;
@class PCRemoteFileNode;

@interface PCRemoteDownloadOperation : PCRemoteTransferOperation <PCSpooledTransferOperation>

@property BOOL quarantineFiles;

- (NSError*)downloadNode:(PCRemoteFileNode*)sourceNode to:(PCFolderNode*)destinationFolder;

@end
