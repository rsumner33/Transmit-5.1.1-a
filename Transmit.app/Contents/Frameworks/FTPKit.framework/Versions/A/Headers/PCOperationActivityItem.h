//
//  PCOperationActivityItem.h
//  PanicFileAppKit
//
//  Created by Logan Collins on 6/22/15.
//  Copyright © 2015 Panic Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FTPKit/FTPKitConstants.h>


NS_ASSUME_NONNULL_BEGIN


#if TARGET_OS_IPHONE
@class UIColor;
#else
@class NSColor;
#endif

@class PCOperationGroup, PCFSOperation, PCProgress, PCNode, PCOperationResult;


// Represents an operation in an activity queue
@interface PCOperationActivityItem : NSObject

- (instancetype)initWithOperation:(PCFSOperation *)operation NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithGroup:(PCOperationGroup *)group NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@property (readonly, getter=isCancellable) BOOL cancellable;
- (void)cancel;

@property (readonly, getter=isFinished) BOOL finished;
- (void)didFinish;

@property (nonatomic, strong, readonly) PCFSOperation *operation; // Represented operation, or nil if group
@property (nonatomic, strong) PCProgress *progress; // Operation or group progress

//@property (nullable, nonatomic, readonly) NSString *name;
@property (nullable, nonatomic, readonly) PCNode *node;
@property (nullable, nonatomic, readonly) NSError *error;
@property (nullable, nonatomic, strong) PCOperationResult *result;

#if TARGET_OS_IPHONE
@property (nullable, nonatomic, readonly) UIColor *progressTintColor;
#else
@property (nullable, nonatomic, readonly) NSColor *progressTintColor;
#endif

@property (nonatomic) PCFileSystemOperationType operationType;

@property (nonatomic, weak, readonly) PCOperationActivityItem *parent;

// The set of child items (generally this is the set of executing sub-operations)
@property (nonatomic, copy, readonly) NSArray <PCOperationActivityItem *> *children;

@end


extern NSColor * PCOperationActivityItemTintColorForOperationType(PCFileSystemOperationType operationType, BOOL vibrant); // vibrant: color will be shown on vibrant background


NS_ASSUME_NONNULL_END

