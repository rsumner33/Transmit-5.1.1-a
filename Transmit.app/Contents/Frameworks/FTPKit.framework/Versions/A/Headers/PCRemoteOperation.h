#import "PCFSOperation.h"
#import "FTPKitProtocols.h"
#import <PanicCore/PCTrust.h>


@class AbstractConnection;
@class PCAcquireConnectionOperation;
@class PCRemoteFolderNode;


@interface PCRemoteOperation : PCFSOperation <AbstractConnectionProgressMonitoring, AbstractConnectionAuthentication>

@property(nonatomic, readonly, retain) AbstractConnection* connection;
@property(nonatomic, readonly) BOOL ownsConnection; // If YES (the default value), this operation will act as delegate for the connection and release it back to the connection pool on operationDidEnd.
@property(readonly) BOOL isSecure;
@property(readonly, retain) PCTrust* trust;
@property (retain) PCAcquireConnectionOperation* acquireConnectionOperation;

- (PCRemoteFolderNode*)resolveRemoteDestinationProvider:(NSObject <PCOperationPathProvider> *)destinationProvider error:(NSError**)error;

- (BOOL)nodesFromPaths:(NSArray*)inPath nodes:(NSArray**)outNodes withError:(NSError**)error;
- (BOOL)shouldTransferNode:(PCNode*)node;

- (void)setConnection:(AbstractConnection*)connection isOwner:(BOOL)isOwner;

// operation helpers

- (NSString*)remoteStringForDisplayString:(NSString*)string;
- (NSString*)displayStringForRemoteString:(NSString*)string;

@end

@interface PCRemoteOperation (Private)

- (AbstractConnection*)acquireConnection:(NSError**)error;

@end
