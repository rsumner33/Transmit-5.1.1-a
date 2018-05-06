//
//  PCOperationResult.h
//  FTPKit
//
//  Created by Wade Cosgrove on 11/12/09.
//  Copyright 2009 Panic Inc.. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PCFSOperation;
@class PCNode;

@interface PCOperationResult : NSObject

@property (nullable, retain) NSObject *resultObject;
@property (retain) NSMutableSet <PCNode*> *modifiedNodes;
@property (retain) NSMutableSet <PCNode*> *deletedNodes;
@property (retain) NSMutableSet <PCNode*> *createdNodes;
@property (retain) NSMutableArray <NSError*> *errors;

- (nullable PCNode*)createdNodeForSource:(PCNode*)sourceNode;
- (void)removeCreatedNodeForSource:(PCNode*)sourceNode;
- (void)addCreatedNode:(PCNode*)newNode forSource:(PCNode*)sourceNode;
- (void)addCreatedNode:(PCNode*)createdNode;
- (BOOL)containsCreatedNode:(PCNode*)createdNode;

- (nullable PCNode*)sourceForCreatedNode:(PCNode*)createdNode;

- (void)addModifiedNode:(PCNode*)modifiedNode;
- (BOOL)containsModifiedNode:(PCNode*)modifiedNode;

- (void)addDeletedNode:(PCNode*)deletedNode;
- (BOOL)containsDeletedNode:(PCNode*)deletedNode;

- (void)addObjectsFromResult:(PCOperationResult*)result;
- (void)clearResult;

- (void)addError:(nullable NSError*)error;
- (void)setError:(nullable NSError*)error; // only use if the operation is going to report a single error
- (NSError*)error; // first error

@end

NS_ASSUME_NONNULL_END
