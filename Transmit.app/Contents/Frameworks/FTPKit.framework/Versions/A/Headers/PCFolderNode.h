#import "PCFileNode.h"
#import "FTPKitConstants.h"
#import "PCRemoteTransferOperation.h"
#import "FTPKitProtocols.h"

#import <pthread.h>
#import <PanicCore/PanicCore.h>

#define kIconLoadingThreshold 30

typedef enum : NSUInteger {
	PCChangeTypeReplace,
	PCChangeTypeAddition,
	PCChangeTypeDeletion,
	PCChangeTypeUpdate
} PCChangeType;

// This protocol implements the policy for creating the containers used by a folder and is required.
@protocol PCNodeContainerCreating
@required

+ (NSMutableDictionary*)filenameDictionaryWithCapacity:(NSUInteger)capacity;

@end

@protocol PCFolderContentObserver <NSObject>

@required

- (void)folderContentDidChange:(PCNode <PCFolderNode>*)folder changes:(NSArray*)changes type:(PCChangeType)type;

@end


// default policies, collect them all!
extern NSMutableDictionary* LiteralFilenameDictionary(NSUInteger capacity);
extern NSMutableDictionary* NonliteralFilenameDictionary(NSUInteger capacity);


// This is an implementation of a folder's contents. The intended use is for the owning folder to conform to the PCFolderNode protocol and forward any unhandled methods to the contents object. If the owning folder wishes to override any methods it is free to do so, in which case it may manually invoke the corresponding method on the contents object.
@interface PCFolderNodeContents : NSObject <PCFolderNode>
{

@private
	
	NSMutableDictionary* iContentsDict;
	NSMutableSet* iVisibleContents;
	NSMutableSet* _pendingFilenames;
}

@property (readonly) NSRecursiveLock *busyLock;

@property (readonly) PCNode<PCFolderNode>* iFolder;

// You must obtain the busy lock when directly accessing -contentsDict_. This lock is locked behind the scenes when inserting or removing a node, or when calling -contentsDict or -countWithHidden:. Do not call this directly unless you know what you're doing.
- (NSDictionary*)contentsDict_;
- (pthread_rwlock_t*)contentsLock_;

- (id)initWithFolder:(PCNode<PCFolderNode>*)folder;
- (void)setPath:(NSString*)inPath;

// Do not call directly, go through parent folder
- (NSString*)uniquePendingFilename:(NSString*)filename copySuffix:(NSString*)suffix;

// Observing
- (void)addContentObserver:(NSObject <PCFolderContentObserver>*)object;
- (void)removeContentObserver:(NSObject <PCFolderContentObserver>*)object;
- (void)flushBufferedChanges;

// Private-like, only folders should call this
- (void)markChangedNodes:(NSArray*)nodes ofType:(PCChangeType)type;

@end


@interface PCFolderNode : PCFileNode <PCNodeContainerCreating, PCFolderNode, PCOperationPathProvider>
{
@protected
	PCFolderNodeContents* iContents;
	
	BOOL iPackage;
	
	BOOL iCancelIconLoading;
	NSLock* iconLock;
	BOOL iExpired;
}

@property (nonatomic, getter=isExpired) BOOL expired;
@property BOOL isPackage;

+ (id)folderNodeWithPath:(NSString*)path;

// accessors

- (PCFileNode*)nodeWithFilename:(NSString*)name;
- (PCFileNode*)nodeWithFilename:(NSString*)name createWithType:(PCFileSystemType)type;

- (PCFileNode*)nodeWithFilename:(NSString*)name useContentsLock:(BOOL)flag; // Only call this method if you have already obtained the contents lock manually.

// redeclared from PCFolderNode protocol for proper argument type specialization and checking

- (void)addNode:(PCNode*)node;
- (void)childNodeWasRenamed:(PCFileNode*)node oldName:(NSString*)oldName;
- (void)removeNode:(PCNode*)node;

// misc

- (void)noteContentAttributesChanged;

- (NSSet*)contentsSet; // observable - deprecated
- (void)cancelIconLoading;

- (pthread_rwlock_t*)contentsLock;

- (void)addContentObserver:(NSObject <PCFolderContentObserver>*)object;
- (void)removeContentObserver:(NSObject <PCFolderContentObserver>*)object;
- (void)flushBufferedChanges;

@end
