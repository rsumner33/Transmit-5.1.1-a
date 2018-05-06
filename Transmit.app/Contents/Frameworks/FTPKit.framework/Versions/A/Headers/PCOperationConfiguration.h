//
//  PCOperationConfiguration.h
//  FTPKit
//
//  Created by Wade Cosgrove on 2/3/15.
//  Copyright (c) 2015 Panic Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FTPKitConstants.h"
//#import "PCFSOperation.h"

@class PCCredentials;
@class PCNode;
@class PCFSOperation;

@interface PCOperationConfiguration : NSObject

- (instancetype)initWithCredentials:(PCCredentials*)credentials;

@property (assign) FTPKitConflictMode conflictMode;
@property (retain) PCCredentials *credentials;

// Properties for transfer operations

@property (assign) BOOL calculateTotalSizes;
@property (assign) BOOL followSymlinks;
@property (assign) BOOL shouldTransferHiddenFiles;
@property (assign) BOOL shouldPreserveCreationDates;
@property (assign) BOOL shouldHideFileExtensionsOnRemove;
@property (assign) char transferMode;
@property (assign) BOOL shouldContinueAfterError;
@property (assign) BOOL useTransferRules;
@property (assign, getter=isPaused) BOOL paused; // transfers should pause
@property (assign, readwrite, getter=isAtomicUpload) BOOL atomicUpload;

@property(readonly) NSPredicate* skipFilesPredicate; // generated from the two properties below
@property(readonly) NSPredicate* skipFilesBasePredicate;
@property(readwrite, retain) NSPredicate* skipFilesUserPredicate;
@property(readwrite, retain) NSPredicate* showFilesUserPredicate;

- (FTPKitConflictMode)conflictModeForNode:(PCNode*)sourceNode; // destination:(PCNode*)destinationNode operation:(PCFSOperation*)operation;
- (void)setConflictMode:(FTPKitConflictMode)conflictMode forNode:(PCNode*)node;
- (void)setValidatedConflictMode:(FTPKitConflictMode)newConflictMode canResume:(BOOL)canResume;

@end
