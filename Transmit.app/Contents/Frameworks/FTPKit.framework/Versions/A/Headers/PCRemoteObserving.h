//
//  PCRemoteObserving.h
//  FTPKit
//
//  Created by Logan Collins on 12/17/15.
//  Copyright © 2015 Panic Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN


@class PCRemoteFileManager, PCRemoteFileNode;


// Types of remote changes
typedef NS_ENUM(NSUInteger, PCRemoteChangeType) {
    PCRemoteChangeTypeCreated = 0,      // The node was created
    PCRemoteChangeTypeModified = 1,     // The node was modified
    PCRemoteChangeTypeDeleted = 2,      // The node was deleted
    PCRemoteChangeTypeMoved = 3,        // The node was moved
};


// An object describing a set of changes
@interface PCRemoteChange : NSObject

- (instancetype)initWithNode:(PCRemoteFileNode *)node changeType:(PCRemoteChangeType)changeType NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, strong, readonly) PCRemoteFileNode *node;
@property (nonatomic, readonly) PCRemoteChangeType changeType;

// For move operations, the old path for the file can be populated to associate the change.
// For other operations, this will most likely be nil.
@property (nullable, nonatomic, copy) NSString *oldPath;

@end


@protocol PCRemoteObservationProviderDelegate;


// An abstract class meant for subclassing by each connection type
// Instances of this class are used to facilitate remote observation on file managers.
@interface PCRemoteObservationProvider : NSObject

// Automatically creates an instance of the proper provider class for a given file manager
// If the file manager does not support remote observing, this method returns nil.
// You should use this method to create providers.
+ (nullable instancetype)remoteObserverationProviderWithFileManager:(PCRemoteFileManager *)fileManager;

// Invoked automatically when a provider is created. Do not call this method yourself.
// Subclasses may override this method to perform initialization.
- (instancetype)initWithFileManager:(PCRemoteFileManager *)fileManager NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;


@property (weak, readonly) PCRemoteFileManager *fileManager;

@property (weak) id <PCRemoteObservationProviderDelegate> delegate;


// For observation providers supporting cursors, this property should be set to the latest cursor value
// after changes are received. When a provider is created, this property can be set to the last known value
// before observation is started, to allow observation to deliver any changes that have occurred since the
// last observation. If a provider does not support cursors, this value can be safely ignored as nil.
@property (nullable, strong) id <NSCoding> latestCursor;


// Subclasses must override these methods
// The default implementations raise an exception
- (void)startObservingAtPath:(NSString *)path options:(nullable NSDictionary <NSString *, id> *)options;
- (void)stopObservingAtPath:(NSString *)path;


// Subclasses can optionally override these methods
- (void)pauseObserving;
- (void)resumeObserving;

@end


// Implemented by objects wishing to observe remote changes
@protocol PCRemoteObservationProviderDelegate <NSObject>

- (void)remoteObservationProvider:(PCRemoteObservationProvider *)provider didReceiveChanges:(NSArray <PCRemoteChange *> *)changes;

@end


NS_ASSUME_NONNULL_END

