#import "PCFSOperation.h"

@class PCFolderNode;
@class PCNode;

@interface PCLocalNewFileOperation : PCFSOperation

@property (copy) NSString *filename;
@property (retain) NSObject <PCOperationPathProvider>* destinationProvider;

// pass in nil to get default unique name
- (id)initWithName:(NSString*)newName destinationProvider:(NSObject <PCOperationPathProvider>*)provider;

// for subclass
- (NSError*)createNewItemInFolder:(PCFolderNode*)destinationFolder;
- (NSString*)defaultNewItemName;

@end
