#import "PCRemoteOperation.h"

@class AbstractConnection;
@class PCRemoteFolderNode;

@interface PCRemoteChangeDirectoryOperation : PCRemoteOperation

@property (retain) NSString *path;

- (id)initWithPath:(NSString*)inPath;
- (NSString*)trimPath:(NSString*)aString;
- (BOOL)pathComponentsContainSpecialCharacters:(NSString*)aPath;

@end
