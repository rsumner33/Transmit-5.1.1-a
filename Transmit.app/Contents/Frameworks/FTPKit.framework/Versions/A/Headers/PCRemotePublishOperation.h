#import "FTPKitConstants.h"
#import "PCRemoteTransferOperation.h"

@class AbstractConnection;
@class PCRemoteFileNode;
@protocol PCOperationGroupDelegate;

@interface PCRemotePublishOperation : PCRemoteTransferOperation
{
	NSString* iLocalPath;
	NSString* iRemotePath;
}

@property (assign) BOOL recurive;

- (id)initWithNodes:(NSArray*)someNodes localRootPath:(NSString*)localPath remoteRootPath:(NSString*)remotePath recursive:(BOOL)recurive;

@end


@protocol PCRemotePublishInterfaceDelegateProtocolAddition <PCOperationGroupDelegate>

@optional
- (PCNode*)remotePublishOperation:(PCRemotePublishOperation*)operation willPublishNode:(PCNode*)node toPath:(NSString*)remotePath;

@end
