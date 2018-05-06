#import "FTPKitConstants.h"
#import "PCFolderNode.h"

@class PCNode;
@class PCFileNode;
@class PCFolderNode;
@class PCFSOperation;
@class PCUUID;
@class PCOperationGroup;
@class PCProtocolExtension;
@class PCMessageQueue;


@protocol PCOperationGroupDelegate;


@interface PCVirtualFileManager : NSObject
{
}

@property (retain) PCNode <PCFolderNode>* rootNode;

// returns either the current group, or creates a new group with the delegate and schedules group operations for starting. The scoped group is passed into the operations block for use.
- (PCOperationGroup*)implicitGroupWithDelegate:(NSObject <PCOperationGroupDelegate>*)delegate operations:(void (^)(PCOperationGroup*))block;

- (void)scheduleOperationGroupStart:(PCOperationGroup*)group DEPRECATED_ATTRIBUTE;

- (NSArray*)readOnlyOperationGroups;
- (void)addOperationGroup:(PCOperationGroup*)group;
- (void)removeOperationGroup:(PCOperationGroup*)group;

- (NSError*)runOperationSynchronously:(PCFSOperation*)operation delegate:(NSObject <PCOperationGroupDelegate>*)delegate;

+ (NSString*)approximateFileSizeStringForSize:(unsigned long long)aSize;
+ (NSString*)convertSecondsToTime:(long long)inSeconds;
+ (NSString*)exactFileSizeStringForSize:(unsigned long long)aSize;

// TODO: these methods should be changed to fileNodeAtPath: & folderNodeAtPath: -wac

- (PCFileNode*)nodeForPath:(NSString*)path create:(BOOL)createFlag; // Note: remote file managers may not be able to create nodes without type information
- (PCNode*)fileNodeForPath:(NSString*)path create:(BOOL)createFlag;
- (PCNode*)folderNodeForPath:(NSString*)path create:(BOOL)createFlag;
- (PCNode*)fileNodeForUnicodePath:(NSString*)path create:(BOOL)createFlag;
- (PCNode*)folderNodeForUnicodePath:(NSString*)path create:(BOOL)createFlag;

- (PCOperationGroup*)calculateSumSizeOfNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)copyNodes:(NSArray*)nodes toPath:(NSString*)toPath delegate:(id)delegate NS_RETURNS_NOT_RETAINED;
- (PCOperationGroup*)copyNodes:(NSArray*)nodes toPath:(NSString*)folderPath conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate NS_RETURNS_NOT_RETAINED;

- (PCOperationGroup*)duplicateNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)deleteNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)deletePaths:(NSArray*)paths delegate:(id)delegate;
- (PCOperationGroup*)moveNodes:(NSArray*)nodes toPath:(NSString*)folderPath delegate:(id)delegate;
- (PCOperationGroup*)moveNodes:(NSArray*)nodes toPath:(NSString*)folderPath conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
- (PCOperationGroup*)renameNode:(PCNode*)node to:(NSString*)newName delegate:(id)delegate;
- (PCOperationGroup*)renameNodes:(NSArray*)nodes to:(NSArray*)newNames delegate:(id)delegate;

- (PCOperationGroup*)compareNode:(PCNode*)sourceNode withNode:(PCNode*)destinationNode delegate:(id)delegate;

- (PCOperationGroup*)contentsOfNode:(PCNode*)node delegate:(id)delegate;

- (PCOperationGroup*)createFileInFolder:(PCNode*)node withName:(NSString*)name delegate:(id)delegate;
- (PCOperationGroup*)createFolderInFolder:(PCNode*)node withName:(NSString*)name delegate:(id)delegate;
- (PCOperationGroup*)changeAttributes:(NSDictionary*)attributes recursively:(BOOL)recursively forNodes:(NSArray*)nodes delegate:(id)delegate;

- (PCOperationGroup*)downloadURLs:(NSArray *)URLs toPath:(NSString *)folderPath delegate:(id)delegate;
- (PCOperationGroup*)publishNodes:(NSArray*)publishNodes sourceNode:(PCNode*)sourceNode destinationNode:(PCNode*)destinationNode recursively:(BOOL)recursively conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
- (PCOperationGroup*)publishNodes:(NSArray*)publishNodes sourceNode:(PCNode*)sourceNode destinationNode:(PCNode*)destinationNode destinationMap:(NSMapTable*)nodeMap recursively:(BOOL)recursively conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;

- (void)cancelAllOperations;
- (NSSet*)cancelOperationsWithInterfaceDelegate:(id)inDelegate;

//- (PCFSOperation*)firstOperationForInterfaceDelegate:(id)inDelegate;

- (NSString*)pathByResolvingPath:(NSString*)path;
- (NSString*)pathByResolvingPath:(NSString*)path relativeToParent:(NSString*)parentPath;
- (NSArray*)completedPaths:(NSString*)uncompletedPath rootNode:(PCNode*)rootNode relativeNode:(PCNode*)relativeNode withHidden:(BOOL)includeHidden foldersOnly:(BOOL)foldersOnly;
- (NSArray*)completedPaths:(NSString*)uncompletedPath rootNode:(PCNode*)rootNode relativeNode:(PCNode*)relativeNode withHidden:(BOOL)includeHidden foldersOnly:(BOOL)foldersOnly pathTypes:(NSArray**)types; // types are PCFileSystemType NSNumbers

- (BOOL)isReadableFileAtPath:(NSString*)path;

// designated start operation method for the file manager, filters duplicate operations
- (void)startOperationGroup:(PCOperationGroup*)group;

// dependent child operations use this method
- (void)startOperation:(PCFSOperation*)operation;

@end

@interface PCVirtualFileManager (URLFactory)

- (NSURL*)URLForNode:(PCNode*)node baseURL:(NSString*)baseURL initialPath:(NSString*)initialPath withPassword:(BOOL)includePassword;
- (PCNode*)nodeForURL:(NSURL*)aURL remoteURL:(NSString*)remoteURL localURL:(NSString*)localURL basePath:(NSString*)basePath;

@end

@interface PCApproximateFileSizeStringTransformer : NSValueTransformer
{}

@end

@interface PCExactFileSizeStringTransformer : NSValueTransformer
{}

@end
