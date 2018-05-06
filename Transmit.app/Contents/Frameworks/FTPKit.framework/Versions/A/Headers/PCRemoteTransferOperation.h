#import "PCRemoteOperation.h"
#import "FTPKitProtocols.h"

@class PCNode;

@interface PCRemoteTransferOperation : PCRemoteOperation <PCOperationPathProvider, PCSpooledTransferOperation>

@property (retain) NSObject <PCOperationPathProvider> *destinationProvider;
@property (retain) PCNode <PCFolderNode, PCOperationPathProvider> *destinationNode; // resolved destination provider, can be local or remote folder

+ (instancetype)operationWithNode:(PCNode*)source destinationProvider:(NSObject <PCOperationPathProvider>*)destinationProvider;
- (instancetype)initWithNode:(PCNode*)node destinationProvider:(NSObject <PCOperationPathProvider>*)destinationProvider;

- (PCNode*)nodeAtPath:(NSString*)path isRemote:(BOOL)remote;

@end


@interface PCRemoteTransferOperation (AbstractConnectionProgressDelegate)

- (void)connection:(AbstractConnection*)aConnection incrementTotalProgressBy:(unsigned long long)incrementAmount;

@end