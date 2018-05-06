#import "PCRemoteOperation.h"

@class PCRemoteFolderNode;

@interface PCRemoteConnectOperation : PCRemoteOperation

@property (retain) PCRemoteFolderNode* initialNode;
@property (retain) PCRemoteFolderNode* currentDirectoryNode;

@property (copy) NSString* downloadPath; // if initial path points to a file, nil otherwise.
@property (copy) NSString *changeToDirectoryPath;

- (id)initWithInitialPath:(NSString*)unicodePath;

//- (void)addDependentOperation:(PCFSOperation *)operation; // operation to be run after connect succeeds

@end
