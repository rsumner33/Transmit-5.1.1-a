#import "PCFSOperation.h"

@class PCFolderNode;

@interface PCLocalMoveOperation : PCFSOperation <NSFileManagerDelegate, PCSpooledTransferOperation>

@property (retain) NSObject <PCOperationPathProvider> *destinationProvider;
@property (retain) PCFolderNode *destinationNode;

- (id)initWithNode:(PCNode*)node destinationProvider:(NSObject <PCOperationPathProvider>*)destinationProvider;

//- (BOOL)shouldProceedAfterNSFileManagerError:(NSError *)error sourcePath:(NSString *)srcPath;

@end
