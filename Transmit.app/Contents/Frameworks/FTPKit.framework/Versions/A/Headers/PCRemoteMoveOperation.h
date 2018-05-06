#import "PCRemoteOperation.h"

@class PCRemoteFileNode;

@interface PCRemoteMoveOperation : PCRemoteOperation <PCSpooledTransferOperation>

@property (copy) NSString *customFilename;
@property (strong) NSObject <PCOperationPathProvider> *destinationProvider;

- (instancetype)initWithNode:(PCRemoteFileNode*)node destinationProvider:(NSObject <PCOperationPathProvider> *)destinationProvider;

@end
