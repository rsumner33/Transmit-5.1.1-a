#import "PCVirtualFileManager.h"
#import "PCRemoteFolderNode.h"

#import <PanicCore/PanicCore.h>

@class AbstractConnection;
@class PCConnectionPool;
@class PCCredentials;
@class PCRemoteAliasNode;
@class PCRemoteCacheOperation;
@class PCRemoteChangeAttributesOperation;
@class PCRemoteChangeDirectoryOperation;
@class PCRemoteChangeExtensionOperation;
@class PCRemoteConnectOperation;
@class PCRemoteCopyOperation;
@class PCRemoteDeleteOperation;
@class PCRemoteDownloadOperation;
@class PCRemoteFileNode;
@class PCRemoteFolderNode;
@class PCRemoteGetAttributesOperation;
@class PCRemoteListDirectoryOperation;
@class PCRemoteMoveOperation;
@class PCRemoteNewFileOperation;
@class PCRemoteNewFolderOperation;
@class PCRemoteOperation;
@class PCRemotePublishOperation;
@class PCRemoteRawCommandOperation;
@class PCRemoteRenameOperation;
@class PCRemoteResolveSymlinkOperation;
@class PCRemoteReversePublishOperation;
@class PCRemoteSumSizeOperation;
@class PCRemoteUploadOperation;

@interface PCRemoteFileManager : PCVirtualFileManager

@property(retain) PCConnectionPool* connectionPool;
@property(retain) PCRemoteFolderNode* loginNode; // This is the node that the server logged the user into by default for the credentials given
@property(assign) BOOL supportsAtomicUploads;

// To obtain access to a file manager use remoteManagerForCredentials… this will return an autoreleased manager

+ (PCRemoteFileManager*)addFileManager:(PCRemoteFileManager*)newManager;

+ (PCRemoteFileManager*)remoteManagerForCredentials:(PCCredentials*)credentials;
//+ (PCRemoteFileManager*)remoteManagerForCredentials:(PCCredentials*)credentials create:(BOOL)createIfNeeded;
+ (NSArray*)remoteManagers;
+ (void)removeRemoteManager:(PCRemoteFileManager *)fileManager;

+ (PCOperationGroup*)connectToCredentials:(PCCredentials*)credentials delegate:(id)delegate;

- (PCOperationGroup*)cacheNodes:(NSArray*)nodes conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
- (PCOperationGroup*)cachePaths:(NSArray*)paths conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
- (PCOperationGroup*)calculateSumSizeOfNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)changeDirectoryAndCreateNode:(NSString*)path delegate:(id)delegate;
- (PCOperationGroup*)changeAttributes:(NSDictionary*)dictionary recursively:(BOOL)recursively forNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)contentsOfNode:(PCRemoteFolderNode*)node delegate:(id)delegate;
- (PCOperationGroup*)copyNodes:(NSArray*)nodes toPath:(NSString*)toPath conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate NS_RETURNS_NOT_RETAINED;
- (PCOperationGroup*)createFileInFolder:(PCRemoteFolderNode*)node withName:(NSString*)name delegate:(id)delegate;
- (PCOperationGroup*)createFolderInFolder:(PCRemoteFolderNode*)node withName:(NSString*)name delegate:(id)delegate;
- (PCOperationGroup*)deleteNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)deletePaths:(NSArray*)paths delegate:(id)delegate;
- (PCOperationGroup*)downloadNodes:(NSArray*)sourceNodes toFolder:(PCFolderNode*)destinationNode conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
- (PCOperationGroup*)downloadPaths:(NSArray*)sourcePaths toFolder:(PCFolderNode*)destinationNode conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
- (PCOperationGroup*)duplicateNodes:(NSArray*)nodes delegate:(id)delegate;
- (PCOperationGroup*)getAttributesForNodes:(NSArray*)sourceNodes delegate:(id)delegate;
- (PCOperationGroup*)moveNodes:(NSArray*)nodes toPath:(NSString*)folderPath conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
//- (PCOperationGroup*)publishNodes:(NSArray*)sourceNodes sourceNode:(PCNode*)sourceNode destinationNode:(PCNode*)destinationNode recursively:(BOOL)recursively conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
- (PCOperationGroup*)renameFileAtPath:(NSString*)sourcePath to:(NSString*)newName delegate:(id)delegate;
- (PCOperationGroup*)renameFilesAtPaths:(NSArray*)sourcePaths to:(NSArray*)newNames delegate:(id)delegate;
- (PCOperationGroup*)renameNode:(PCRemoteFileNode*)node to:(NSString*)newName delegate:(id)delegate;
- (PCOperationGroup*)resolveSymlink:(PCRemoteAliasNode*)node delegate:(id)delegate;
//- (PCOperationGroup*)reversePublishNodes:(NSArray*)sourceNodes sourceNode:(PCNode*)sourceNode destinationNode:(PCNode*)destinationNode recursively:(BOOL)recursively conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
- (PCOperationGroup*)sendRawCommand:(NSString*)command delegate:(id)delegate;
- (PCOperationGroup*)uploadNodes:(NSArray*)sourceNodes toFolder:(NSString*)destinationPath conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
- (PCOperationGroup*)transferNodes:(NSArray*)someNodes toFolder:(PCRemoteFolderNode*)destinationNode conflictMode:(FTPKitConflictMode)conflictMode delegate:(id)delegate;
- (PCOperationGroup*)createPublicURLs:(NSArray*)someNodes delegate:(id)delegate;
- (PCOperationGroup*)createPublicURLsFromPaths:(NSArray*)somePaths copyArgs:(NSDictionary*)args delegate:(id)delegate;

- (PCRemoteFileNode*)fileNodeForPath:(NSString*)path create:(BOOL)create;
- (PCRemoteFolderNode*)folderNodeForPath:(NSString*)inPath create:(BOOL)create;
- (PCRemoteFileNode*)fileNodeForUnicodePath:(NSString*)path create:(BOOL)create;
- (PCRemoteFolderNode*)folderNodeForUnicodePath:(NSString*)inPath create:(BOOL)create;

- (NSString*)pathRelativeToLoginPath:(NSString*)relativePath;

// accessors
- (BOOL)hasConnected;
+ (NSSet*)activeConnections;

@property(retain) id <ConnectionTranscriptDelegate> transcriptDelegate;

- (PCCredentials*)credentials;

- (NSString*)address;
- (void)disconnectIdleConnections;
- (void)disconnectIdleConnectionsAtPath:(NSString*)path;
- (NSString*)password;
- (int)port;
- (FTPKitProtocol)protocol;
- (NSString*)username;

@end

@interface PCRemoteFileManager (URLFactory)

- (NSString*)URLStringForNode:(PCNode*)node withPassword:(BOOL)includePassword;

@end


@interface PCRemoteRootNode : PCRemoteFolderNode
@end


@interface PCAcquireConnectionOperation : NSOperation
@property (assign, nonatomic) PCRemoteOperation *operation;
- (instancetype)initWithOperation:(PCRemoteOperation*)operation;
@end
