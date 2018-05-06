#import "PCRemoteOperation.h"

@class AbstractConnection;
@class PCRemoteFolderNode;

@interface PCRemoteListDirectoryOperation : PCRemoteOperation

- (BOOL)getContentsOfNode:(PCRemoteFolderNode*)node error:(NSError**)error;

@end


@interface PCRemoteListDirectoryOperation (PreventUnnecessaryCasting)

+ (PCRemoteListDirectoryOperation*)alloc;

@end
