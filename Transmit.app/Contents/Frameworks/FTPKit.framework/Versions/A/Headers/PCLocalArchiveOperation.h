#import <FTPKit/PCFSOperation.h>

@class PCFolderNode;
@class PCRemoteFolderNode;

@interface PCLocalArchiveOperation : PCFSOperation

- (id)initWithNodes:(NSArray*)inNodes destination:(PCFolderNode*)inFolder;

@end
