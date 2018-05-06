#import "PCFSOperation.h"

@class PCFolderNode;

@interface PCLocalListDirectoryOperation : PCFSOperation

@property (assign) BOOL folderContentsDidChange;

@end


@interface PCLocalListDirectoryOperation (PreventUnnecessaryCasting)

+ (PCLocalListDirectoryOperation*)alloc;

@end
