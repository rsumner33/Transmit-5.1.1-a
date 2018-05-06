#import "FTPKitConstants.h"
#import "FTPKitDefines.h"
#import "FTPKitProtocols.h"
#import <PanicCore/PanicCore.h>
#import <libkern/OSAtomic.h>

/* NOTE: Error codes are found in FTPKitConstants.h */

@class PCNode;
@class PCFileNode;
@class PCFolderNode;
@class PCOperationResult;
@class PCUUID;
@class PCProgress;
@class PCOperationGroup;
@class PCVirtualFileManager;
@class PCTenseString;

extern NSString* const PCOperationObservationContext;
extern NSString* const PCOperationKVOIsCancelledKeyPath;
extern NSString* const PCOperationKVOCancelledKeyPath;
extern NSString* const PCOperationKVOPausedKeyPath;


extern PCTenseString * PCOperationActionStringForOperationType(PCFileSystemOperationType operationType);

@interface PCFSOperation : NSOperation <NSCopying, PCOperationRequestSender, PCProgressDelegate>
{
@private
	NSLock *_dependentOperationMutex;
	//BOOL	_isReady;
}

- (id)initWithNode:(PCNode*)node; // NS_DESIGNATED_INITIALIZER
- (id)initWithNodes:(NSArray*)nodes; // Unless there is a specific need, use initWithNode:

@property (nonatomic, retain) PCNode *node;
@property (copy) NSArray <PCNode*> *nodes; // a few operations init with nodes
@property (nonatomic, assign) PCOperationGroup *group;
@property (readonly) PCVirtualFileManager* fileManager;
@property (readonly) NSError *error;
@property (retain) PCOperationResult *result;
@property (retain) PCUUID* uuid;
@property (readonly) NSString *key;
@property (nonatomic, retain) NSDictionary* userInfo;
@property (retain) NSObject* providerInfo; // user info provided to and by the spooler
@property (assign) PCFSOperation *childOperation;
@property (assign) PCFSOperation *parentOperation;
@property (assign) BOOL reportsProgress;
@property (assign) BOOL propagateResult; // copy results from child operation to parent or from operation to group
@property (getter=isScheduled) BOOL scheduled; // internals, yes when an operation has been added to a queue
@property (getter=isPaused) BOOL paused;
@property (nonatomic, retain) NSString *caption;
@property (readonly) PCFileSystemOperationType operationType;
@property (copy) void (^operationDidEndBlock)(void);
@property (readonly) PCProgress *progress;

- (PCProgress*)displayProgress; // Operation progress, or child progress if running child operation that reports progress

- (BOOL)addDependentOperation:(PCFSOperation*)operation;

- (BOOL)runSynchronouslyError:(NSError**)error; //DEPRECATE? NOTE: unless you have a very specific reason, use runChildOperation::: instead.
- (BOOL)runChildOperation:(PCFSOperation*)op error:(NSError**)error; // reportProgress and propagateResult default to parent operation flags
- (BOOL)runChildOperation:(PCFSOperation*)op reportProgress:(BOOL)flag propagateResult:(BOOL)resultFlag error:(NSError**)error;
- (BOOL)runQuicklyWithParent:(PCFSOperation*)parentOperation; // Optional, determine if operation should be run based on some state defined by operation. Operation should fill out result object as though operation was run successfully. Return YES if operation was run quickly.
- (void)setThreadName:(NSString*)name;

- (void)operationMainDidStart; // called when main starts
- (void)operationMainWillEnd:(NSError*)error; // called when main ends
- (void)operationDidEnd:(NSError*)error; // called when operation ends, via start/main


// These must be implemented by subclasses

- (BOOL)isRemote;
+ (PCFileSystemOperationType)operationType;
- (BOOL)shouldRateLimit; // defaults to NO
- (NSString*)uniqueKeySuffix;

// end rquired by subclass

- (BOOL)isCancellable;

- (NSString*)detailedCaption; /*optional, but recommended*/
- (NSString*)captionForNodes:(NSArray <PCNode*>*)nodes;
- (NSString*)captionForPaths:(NSArray <NSString*>*)paths;

//- (void)waitIfPaused;

- (PCNode*)currentNode;
- (void)setCurrentNode:(PCNode*)inNode;

// Private
// Convenience methods for status changing, performed on worker threads
- (void)postOverwriteNotificationForNode:(PCNode*)overwrittenNode replacement:(PCNode*)newNode;
- (BOOL)_operationIsReadyInternal;

- (PCFolderNode*)resolveLocalDestinationProvider:(NSObject <PCOperationPathProvider> *)destinationProvider error:(NSError**)error;

@end


// fixme5, remove? call into group directly
@interface PCFSOperation (IntefaceDelegateInteraction)

// These methods callback to the main thread to the associated interfaceDelegate methods, blocking until the appropriate response method is called.

- (BOOL)isWorthyTrust:(PCTrust*)trust;

- (PCFSOperationRequestResponse)presentRequest:(PCOperationRequest *)request performedAction:(PCOperationRequestAction **)outAction results:(NSDictionary **)outResults;

- (NSInteger)presentError:(NSError *)error;

@end


@interface PCFSOperation (Private)

- (void)_cancel;
- (BOOL)canContinueAfterError; // subclasses should override this
- (BOOL)shouldContinueAfterRunningAlertWithError:(NSError*)error;

@end


