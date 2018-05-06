//
//  PCProgress.h
//  Checkmark
//
//  Created by Wade Cosgrove on 3/6/15.
//  Copyright (c) 2015 Wade Cosgrove. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FTPKitProtocols.h"
//#import "os/lock.h"

@class PCTenseString;


@interface PCProgress : NSProgress <NSCopying>
{
	NSRecursiveLock *_readWriteLock;
	NSLock *_infoLock;
}

@property (assign, getter=isCalculatingTotalUnitCount) BOOL calculatingTotalUnitCount;
@property (assign) id <PCProgressDelegate> delegate;
@property (nonatomic, retain) PCTenseString *actionString;

+ (PCProgress*)pc_currentProgress;
+ (instancetype)progressWithTotalUnitCount:(int64_t)count;

- (void)pc_becomeCurrent;
- (void)pc_resignCurrent;

- (NSUInteger)totalFileCount;
- (void)setTotalFileCount:(NSUInteger)fileCount; // userInfo key NSProgressFileTotalCountKey, value is propogated to parent

- (void)incrementCompletedUnitCount:(NSInteger)incrementCount;
- (void)incrementTotalUnitCount:(NSInteger)incrementCount;
- (void)incrementCompletedFileCount:(NSInteger)incrementCount;
- (void)incrementTotalFileCount:(NSInteger)incrementCount;

- (NSUInteger)completedFileCount; // userInfo key NSProgressFileCompletedCountKey, value is propogated to parent
- (void)setCompletedFileCount:(NSUInteger)completedCount;

@property (nonatomic, readonly) PCProgress *pc_parentProgress;
- (void)setParentProgress:(PCProgress*)parent; // generally there is no need to call this, used when setting up progress trees after initialization

@property (atomic, assign) PCOperationState operationState;

// PCOperationStatus replacement methods

@property (getter=isStalled) BOOL stalled;

// caption == localizedDescription
// detailedCaption = localizedAdditionalDescription;


@property (readonly) long long secondsRemaining;
@property (readonly) double kBytesPerSecond;
@property (readonly) double fractionCompleted; // -1 is indeterminate

- (void)publish;
- (void)unpublish;

- (void)lock;
- (void)unlock;
- (double)unsafe_fractionCompleted;
- (BOOL)unsafe_isIndeterminate;
- (NSString*)unsafe_localizedDescription;
- (NSString*)unsafe_localizedAdditionalDescription;

@end


@interface PCGroupProgress : PCProgress

@property (nonatomic, retain) NSString *destination;

- (void)incrementRunningFileCount;
- (void)decrementRunningFileCount;

@end


/*
@interface PCProgressLock : NSObject <NSLocking>
{
	os_unfair_lock unfairLock;
}

- (BOOL)tryLock;
- (void)unlock;
- (void)lock;

@end


@interface PCRecursiveProgressLock : PCProgressLock
{
	NSThread *lockThread;
	NSInteger threadLockDepth;
}
@end
*/
