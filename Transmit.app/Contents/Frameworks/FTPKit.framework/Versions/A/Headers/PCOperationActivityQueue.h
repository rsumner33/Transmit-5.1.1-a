//
//  PCOperationActivityQueue.h
//  PanicFileAppKit
//
//  Created by Logan Collins on 10/5/15.
//  Copyright © 2015 Panic Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FTPKit/FTPKitConstants.h>
#import <FTPKit/PCOperationGroup.h>
#import <FTPKit/PCOperationActivityItem.h>


NS_ASSUME_NONNULL_BEGIN


@class PCVirtualFileManager, PCLocalFileManager, PCFileNode, PCFolderNode, PCRemoteFileManager, PCRemoteFileNode, PCRemoteFolderNode;
@protocol PCOperationActivityQueueObserver;


/*!
 * @class PCOperationActivityQueue
 * @abstract Coordinates a series of operations as a visual queue
 *
 * @discussion
 * Thread safety note: Activity queue objects are not safe to modify from multiple threads.
 * Mutations to the items in the queue or its options should be performed from a single thread (generally the main thread).
 */
@interface PCOperationActivityQueue : NSObject <PCOperationGroupDelegate, PCMessageQueueDelegate>

// While paused, the queue will automatically mark any added operations as paused when enqueued
@property (nonatomic, getter=isPaused) BOOL paused;


@property (nonatomic) FTPKitConflictMode uploadConflictMode;
@property (nonatomic) FTPKitConflictMode downloadConflictMode;
@property (nonatomic) BOOL shouldContinueAfterError;
@property (nonatomic) BOOL shouldTransferHiddenFiles;
@property (nonatomic) BOOL shouldHideFileExtensionsOnRemove;

// Operations
// The operations is the set of all queued or executing operations within the queue.
// When an operation finishes or is cancelled, it is automatically removed from the operations set (unlike the activity list).

// Whether the queue has any queued or executing operations
@property (nonatomic, readonly) BOOL hasActiveOperations;

- (NSUInteger)numberOfActiveOperationsForFileManager:(PCVirtualFileManager *)fileManager;

- (NSSet <PCOperationGroup *> *)operationGroupsForFileManager:(PCVirtualFileManager *)fileManager;

@property (nonatomic, copy, readonly) NSSet <PCOperationGroup *> *operationGroups;

// Adds an operation group to the queue, optionally including its operation in the queue's activity items
// Note: Adding an operation group to the queue resets the group's delegate to the queue
- (void)addOperationGroup:(PCOperationGroup *)operationGroup addToActivityItems:(BOOL)addToActivityItems;

// The operation that is most recent, to display as a representation of the entire queue.
@property (nullable, nonatomic, strong, readonly) PCFSOperation *displayOperation;

// Cancels all operations
- (void)cancelAllOperations;
- (void)cancelActivityItem:(PCOperationActivityItem*)activityItem;


// Activity Items
// The "activity items" list is maintained as the visual list of operations executing in the queue
// This list is a subset of all operations being executed in the queue, depending on whether "addToActivityItems"
// was specified when the operation was added to the queue.

// The set of all items that are queued, executing, or finished in the activity list
@property (nonatomic, copy, readonly) NSArray <__kindof PCOperationActivityItem *> *activityItems;

- (nullable PCOperationActivityItem *)activityItemForKey:(NSObject *)key;

// Whether the queue should remove activity items automatically when they finish. The default is NO.
@property (readonly, nonatomic) BOOL shouldAutomaticallyRemoveActivityItems;

// Removes all activity items from the queue that have finished or been cancelled
- (void)clear;


// Observers
@property (nonatomic, copy, readonly) NSSet <id <PCOperationActivityQueueObserver>> *activityQueueObservers;
- (void)addActivityQueueObserver:(id <PCOperationActivityQueueObserver>)observer;
- (void)removeActivityQueueObserver:(id <PCOperationActivityQueueObserver>)observer;


// PCOperationGroupDelegate implementations
// If you override these operation group delegate methods, you must invoke the super implementation
- (void)operationDidStart:(PCFSOperation *)operation NS_REQUIRES_SUPER;
- (void)operationDidEnd:(PCFSOperation *)operation error:(NSError *)error moreComing:(BOOL)moreComing NS_REQUIRES_SUPER;
- (void)operation:(PCFSOperation *)operation progressDidChange:(PCProgress *)progress NS_REQUIRES_SUPER;

@end


/*!
 * @protocol PCOperationActivityQueueObserver
 * @abstract Implemented by objects acting as observers of an activity queue
 *
 * @discussion
 * Objects that need to display information about an activity queue should implement this protocol and register themselves
 * with the queue using -addActivityQueueObserver: to receive automatically throttled feedback as the queue changes.
 */
@protocol PCOperationActivityQueueObserver <NSObject>

@optional

// Invoked before a series of updates are delivered to the observer
- (void)activityQueueWillBeginBatchedUpdates:(PCOperationActivityQueue *)activityQueue;
- (void)activityQueueDidEndBatchedUpdates:(PCOperationActivityQueue *)activityQueue;

// PCOperationGroupDelegate callbacks
// These methods are automatically delivered using the queue's default update throttling to prevent too many interface updates too quickly
- (void)activityQueue:(PCOperationActivityQueue *)activityQueue operationDidStart:(PCFSOperation *)operation;
- (void)activityQueue:(PCOperationActivityQueue *)activityQueue operationDidEnd:(PCFSOperation *)operation error:(NSError *)error moreComing:(BOOL)moreComing;
- (void)activityQueue:(PCOperationActivityQueue *)activityQueue operation:(PCFSOperation *)operation progressDidChange:(PCProgress*)progress;

@end


@interface PCOperationActivityQueue (PCOperationGroupHelpers)

// Operation group helpers
// These methods automatically adds the returned operation group to the queue,
// and automatically creates activity items for the items that should have one.

- (nullable PCOperationGroup *)connectToCredentials:(PCCredentials *)credentials;

- (nullable PCOperationGroup *)cacheNodes:(NSArray <PCNode *> *)nodes;

- (PCOperationGroup *)compressNodes:(NSArray <PCFileNode *> *)nodes toFolder:(PCFolderNode *)destinationNode;

- (PCOperationGroup *)copyNodes:(NSArray <PCNode *> *)nodes toFolderPath:(NSString *)folderPath;
- (PCOperationGroup *)copyNodes:(NSArray <PCNode *> *)nodes toFolderPath:(NSString *)folderPath conflictMode:(FTPKitConflictMode)conflictMode;

- (PCOperationGroup *)createFileInFolder:(PCNode *)node;
- (PCOperationGroup *)createFileInFolder:(PCNode *)node withName:(nullable NSString *)fileName;

- (PCOperationGroup *)createFolderInFolder:(PCNode *)node;
- (PCOperationGroup *)createFolderInFolder:(PCNode *)node withName:(nullable NSString *)folderName;

- (PCOperationGroup *)deleteNodes:(NSArray <PCNode *> *)nodes;
- (PCOperationGroup *)deleteNodes:(NSArray <PCNode *> *)nodes moveToTrash:(BOOL)moveToTrash;
- (PCOperationGroup *)deletePaths:(NSArray <NSString *> *)paths fileManager:(PCVirtualFileManager *)fileManager;

- (PCOperationGroup *)downloadNodes:(NSArray <PCRemoteFileNode *> *)nodes toFolder:(PCFolderNode *)destinationNode;
- (PCOperationGroup *)downloadNodes:(NSArray <PCRemoteFileNode *> *)nodes toFolder:(PCFolderNode *)destinationNode conflictMode:(FTPKitConflictMode)conflictMode;
- (PCOperationGroup *)downloadPaths:(NSArray <NSString *> *)paths toFolder:(PCFolderNode *)destinationNode conflictMode:(FTPKitConflictMode)conflictMode fileManager:(PCRemoteFileManager *)fileManager;

- (PCOperationGroup *)duplicateNodes:(NSArray <PCNode *> *)nodes;

- (PCOperationGroup *)moveNodes:(NSArray <PCNode *> *)nodes toFolderPath:(NSString *)folderPath;
- (PCOperationGroup *)moveNodes:(NSArray <PCNode *> *)nodes toFolderPath:(NSString *)folderPath conflictMode:(FTPKitConflictMode)conflictMode;

- (nullable PCOperationGroup *)renameFileAtPath:(NSString *)path to:(NSString *)newName fileManager:(PCVirtualFileManager *)fileManager;
- (nullable PCOperationGroup *)renameFilesAtPaths:(NSArray *)paths to:(NSArray*)newNames fileManager:(PCVirtualFileManager *)fileManager;

- (PCOperationGroup *)publishNodes:(NSArray <PCFileNode *> *)nodes sourceNode:(PCNode *)sourceNode destinationNode:(PCNode *)destinationNode fileManager:(PCRemoteFileManager *)fileManager;

- (PCOperationGroup *)uploadNodes:(NSArray <PCFileNode *> *)nodes toFolder:(PCRemoteFolderNode *)destinationNode;
- (PCOperationGroup *)uploadNodes:(NSArray <PCFileNode *> *)nodes toFolder:(PCRemoteFolderNode *)destinationNode conflictMode:(FTPKitConflictMode)conflictMode;
- (PCOperationGroup *)uploadNodes:(NSArray <PCFileNode *> *)nodes toPath:(NSString *)toPath conflictMode:(FTPKitConflictMode)conflictMode fileManager:(PCRemoteFileManager *)destinationManager;

- (PCOperationGroup *)uploadNodesFromServer:(NSArray <PCRemoteFileNode *> *)nodes toFolder:(PCRemoteFolderNode *)destinationFolder;

@end


NS_ASSUME_NONNULL_END

