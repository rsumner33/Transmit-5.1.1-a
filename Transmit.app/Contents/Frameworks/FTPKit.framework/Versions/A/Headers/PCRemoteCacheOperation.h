#import "PCRemoteDownloadOperation.h"


@interface PCRemoteCacheOperation : PCRemoteDownloadOperation

@property (strong) NSString* sourcePath;
@property (assign) BOOL validateModificationDate; // default to NO, performs list dir before caching

- (id)initWithPath:(NSString*)path destinationProvider:(NSObject <PCOperationPathProvider>*)destinationProvider;

- (NSError*)cacheNode:(PCRemoteFileNode*)node to:(PCFolderNode*)destination;

@end
