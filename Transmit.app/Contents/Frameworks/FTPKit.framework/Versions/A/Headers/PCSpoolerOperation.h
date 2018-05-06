#import "PCRemoteTransferOperation.h"
#import "FTPKitProtocols.h"

@class PCNode;

@interface PCSpoolerOperation : PCRemoteTransferOperation <PCOperationPathProvider>

@property (copy) NSArray *preflightNames;
@property (assign) BOOL canResume;
@property (assign, getter=isRecursive) BOOL recursive; // Defaults to YES, should the spooler traverse folders or not
@property (assign) BOOL spoolDepthFirst; // Defaults to NO, should the spooler process folder children before the folder itself
@property (assign) BOOL runSpooledOperationsSynchronously; // Defaults to NO, runs operations synchronously with the spooler's connection as they are created
@property (strong) NSObject *operationProviderInfo; // extra user info that can be attached to the path providers

- (instancetype)initWithNodes:(NSArray*)nodes destinationProvider:(NSObject <PCOperationPathProvider> *)pathProvider remoteProvider:(BOOL)flag operationClass:(Class)spooledClass;
- (instancetype)initWithPaths:(NSArray*)paths destinationProvider:(NSObject <PCOperationPathProvider> *)pathProvider remoteProvider:(BOOL)flag operationClass:(Class)spooledClass;

- (instancetype)initWithNodes:(NSArray*)nodes arguments:(NSObject*)arguments operationClass:(Class)spooledClass;
- (instancetype)initWithPaths:(NSArray*)paths arguments:(NSObject*)arguments operationClass:(Class)spooledClass;

- (PCFileSystemOperationType)spooledOperationType;

@end

@interface NSString (PathProviderProtocolAddition)

- (NSString*)providerPath;

@end
