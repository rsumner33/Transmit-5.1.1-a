#import "PCVirtualFileManager.h"

@class PCFolderNode;
@class PCLocalArchiveOperation;
@class PCLocalChangeAttributesOperation;
@class PCLocalCopyOperation;
@class PCLocalListDirectoryOperation;
@class PCLocalNewFileOperation;
@class PCLocalNewFolderOperation;
@class PCLocalRenameOperation;
@class PCLocalSumSizeOperation;
@class PCLocalTrashOperation;
@class PCLocalUnarchiveOperation;
@class PCURLDownloadOperation;

@interface PCLocalFileManager : PCVirtualFileManager

+ (PCLocalFileManager*)defaultManager;

- (PCOperationGroup*)archiveNodes:(NSArray*)nodes toFolder:(PCFolderNode*)folderNode delegate:(id)delegate;
- (PCOperationGroup*)calculateSumSizeOfNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)changeAttributes:(NSDictionary*)attributes recursively:(BOOL)recursively forNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)contentsOfNode:(PCFolderNode*)node delegate:(id)delegate;
- (PCOperationGroup*)copyNodes:(NSArray*)nodes toPath:(NSString*)folderPath conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate NS_RETURNS_NOT_RETAINED;
- (PCOperationGroup*)createFileInFolder:(PCFolderNode*)node withName:(NSString*)name delegate:(id)delegate;
- (PCOperationGroup*)createFolderInFolder:(PCFolderNode*)node withName:(NSString*)name delegate:(id)delegate;
- (PCOperationGroup*)deleteNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)duplicateNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)renameNode:(PCNode*)node to:(NSString*)newName delegate:(id)delegate;
- (PCOperationGroup*)trashNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)trashPaths:(NSArray*)paths delegate:(id)delegate;
- (PCOperationGroup*)unarchiveNode:(PCNode*)node toFolder:(PCFolderNode*)folderNode delegate:(id)delegate;

- (PCFileNode*)nodeForPath:(NSString*)path create:(BOOL)createFlag;
- (PCFileNode*)nodeForUnicodePath:(NSString*)path create:(BOOL)createFlag;
- (PCFileNode*)fileNodeForPath:(NSString*)path create:(BOOL)create;
- (PCFolderNode*)folderNodeForPath:(NSString*)path create:(BOOL)create;
- (PCFileNode*)fileNodeForUnicodePath:(NSString*)path create:(BOOL)create;
- (PCFolderNode*)folderNodeForUnicodePath:(NSString*)path create:(BOOL)create;

- (NSArray*)createNodesForPaths:(NSArray*)paths;

@end
