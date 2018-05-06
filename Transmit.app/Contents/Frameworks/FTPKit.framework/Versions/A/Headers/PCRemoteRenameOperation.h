#import "PCRemoteMoveOperation.h"

@class AbstractConnection;
@class PCRemoteFileNode;

@interface PCRemoteRenameOperation : PCRemoteMoveOperation

@property (copy) NSString* originalFilename;

- (id)initWithNode:(PCRemoteFileNode*)node name:(NSString*)name;
- (id)initWithPath:(NSString*)path name:(NSString*)name;

@end
