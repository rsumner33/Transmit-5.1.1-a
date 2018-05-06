#import "PCRemoteOperation.h"
#import "FTPKitConstants.h"

@class AbstractConnection;
@class PCRemoteFileNode;

@interface PCRemoteChangeAttributesOperation : PCRemoteOperation <PCSpooledProcessingOperation>

+ (instancetype)operationWithNode:(PCRemoteFileNode*)node arguments:(NSDictionary*)args;
- (instancetype)initWithNode:(PCRemoteFileNode*)node arguments:(NSDictionary*)args;

@end
