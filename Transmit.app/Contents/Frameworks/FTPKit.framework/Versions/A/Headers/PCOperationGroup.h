//
//  PCOperationGroup.h
//  FTPKit
//
//  Created by Wade Cosgrove on 1/27/15.
//  Copyright (c) 2015 Panic Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PanicCore/PCOperationRequest.h>
#import "PCConnectionAuthorizationProvider.h"
#import "FTPKitProtocols.h"
#import <libkern/OSAtomic.h>
#import <PanicCore/PCTrust.h>

@class PCFSOperation;
@class PCNode;
@class PCRemoteFileNode;
@class PCFileNode;
@class PCOperationConfiguration;
@class PCGroupProgress;
@class PCRemoteDownloadOperation;
@class PCVirtualFileManager;
@class PCOperationResult;

@protocol PCOperationGroupDelegate;

@interface PCOperationGroup : NSObject <PCProgressDelegate>

+ (PCOperationGroup *)currentGroup;

+ (PCOperationGroup *)beginGroupWithFileManager:(PCVirtualFileManager *)fileManager delegate:(id <PCOperationGroupDelegate>)delegate;
+ (void)commitGroup;

@property (retain) PCVirtualFileManager *fileManager;
@property (retain) PCOperationConfiguration *configuration;
@property (nonatomic, retain) NSObject <PCOperationGroupDelegate> *delegate;
@property (nonatomic) BOOL canApplyToMultipleFiles;
@property (retain) PCGroupProgress *progress;
@property (retain) PCOperationResult *result;
@property (nonatomic, assign) PCFileSystemOperationType operationType; // a hint describing what type of operations are in the group
@property (nonatomic, retain) NSString* caption;
@property (readonly, getter=isCancelled) BOOL cancelled;
@property (nonatomic, readonly) BOOL hasPrimaryOperation; // YES if the group represents a single non-spooler operation
@property (nonatomic, assign) PCMessageQueue *messageQueue;
@property (copy) NSDictionary *userInfo;
@property (strong) void (^completionBlock)(NSError *error);

#if !TARGET_OS_IPHONE
@property (retain) NSScriptCommand* scriptCommand; // this property is for applescript support to track the script command assocated with this group
#endif

+ (instancetype)groupWithFileManager:(PCVirtualFileManager*)fileManager delegate:(NSObject <PCOperationGroupDelegate> *)delegate;
- (instancetype)initWithFileManager:(PCVirtualFileManager*)fileManager delegate:(NSObject <PCOperationGroupDelegate> *)delegate;

// top level operations, finished and scheduled
- (NSArray*)operations;
- (BOOL)addOperation:(PCFSOperation*)operation; // starts operation by default
- (BOOL)addOperation:(PCFSOperation*)operation start:(BOOL)start;

// returns top-level operations matching a specified type
- (NSArray <__kindof PCFSOperation *> *)operationsOfType:(PCFileSystemOperationType)operationType;
- (__kindof PCFSOperation *)firstOperationOfType:(PCFileSystemOperationType)operationType;

// all operations belonging to the group that are in scheduled & in progress
- (BOOL)addGroupOperation:(PCFSOperation*)operation; // starts operation by default
- (BOOL)addGroupOperation:(PCFSOperation*)operation start:(BOOL)flag;
- (NSUInteger)groupOperationCount;

- (BOOL)addImplicitOperation:(PCFSOperation*)operation; // consider private, used in init by operations when a group is made current

- (void)begin;
- (void)commit;
- (void)cancel;

// process for the group

- (FTPKitConflictMode)operation:(PCFSOperation*)operation resolveConflict:(PCNode*)sourceNode newName:(NSString*)newName destination:(PCNode <PCFolderNode>*)destinationFolder conflictNode:(PCNode**)ioConflictNode error:(NSError**)error;

- (PCFSOperationRequestResponse)operation:(PCFSOperation*)operation presentRequest:(PCOperationRequest *)request performedAction:(PCOperationRequestAction **)outAction results:(NSDictionary **)outResults; // coalleses requests of the same type
- (void)operation:(PCFSOperation*)operation didCompleteRequest:(PCOperationRequest *)request response:(PCFSOperationRequestResponse)response action:(PCOperationRequestAction *)action results:(NSDictionary *)results;
- (PCConnectionAuthorizationResult)operation:(PCFSOperation*)operation authorizeCredentialsIfNeeded:(BOOL)authorizeIfNeeded;
- (BOOL)operation:(PCFSOperation*)operation isWorthyTrust:(PCTrust*)trust;
- (NSInteger)operation:(PCFSOperation*)operation presentError:(NSError*)error; // will always present error, no coallesing
- (BOOL)operation:(PCFSOperation*)operation shouldContinueAfterRunningAlertWithError:(NSError*)error; // optionally presents error, coallesing errors when applying to all
- (void)operation:(PCFSOperation*)operation progressDidChange:(PCProgress*)progress; // optionally can be sent on worker thread

// client callbacks from interface interactions

- (void)interfaceDelegateResolvedFileConflict:(FTPKitConflictMode)conflictMode;
- (void)interfaceDelegateEvaluatedTrust:(PCTrust*)trust evaluation:(PCTrustEvaluation)evaluation;
- (void)interfaceDelegateDidPresentError:(NSError *)error recoveryOptionIndex:(NSInteger)recoveryOptionIndex;
- (void)interfaceDelegateDidAuthorizeWithProvider:(PCConnectionAuthorizationProvider *)provider result:(PCConnectionAuthorizationResult)result;

- (void)operationDidStart:(PCFSOperation*)operation;
- (void)operationDidEnd:(PCFSOperation*)operation error:(NSError*)error;

@end


@protocol PCOperationGroupDelegate <NSObject>

@optional

- (void)operationGroup:(PCOperationGroup*)group evaluateTrust:(PCTrust*)trust;
- (void)operationGroup:(PCOperationGroup*)group presentError:(NSError*)error;
- (void)operationGroup:(PCOperationGroup*)group presentRequest:(PCOperationRequest *)request;
- (void)operationGroup:(PCOperationGroup*)group progressDidChange:(PCProgress*)progress;
- (void)operationGroup:(PCOperationGroup*)group operation:(PCFSOperation*)operation resolveConflict:(PCNode*)sourceNode destination:(PCNode*)destinationNode;
- (void)operationGroup:(PCOperationGroup*)group performAuthorizationWithProvider:(PCConnectionAuthorizationProvider *)provider;
- (void)operationGroupRelinquishedPrimaryOperation:(PCOperationGroup*)group;

- (void)operation:(PCFSOperation*)operation progressDidChange:(PCProgress*)progress;
- (void)operationWillStart:(PCFSOperation*)operation;
- (void)operationDidStart:(PCFSOperation*)operation;
- (void)operationDidEnd:(PCFSOperation*)operation error:(NSError*)error moreComing:(BOOL)moreComing;

@end


@interface GroupInterfaceCallbackContext : NSObject

@property (retain) NSConditionLock *interfaceLock;
@property (retain) NSInvocation *callbackInvocation;
@property (retain) PCFSOperation *operation;
@property (retain) NSObject *interactionResult;

- (void)callbackResolvedFeedback:(id)resultInfo;
- (void)invokeCallbackAndWaitForReply;
- (void)lockWaitingForCallback;

@end
