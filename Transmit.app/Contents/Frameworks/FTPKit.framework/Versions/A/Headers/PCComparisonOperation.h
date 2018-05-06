//
//  PCComparisonOperation.h
//  FTPKit
//
//  Created by Will Cosgrove on 9/9/15.
//  Copyright (c) 2015 Panic Inc. All rights reserved.
//

#import <FTPKit/FTPKit.h>

NSString* StringForTimeInterval(NSTimeInterval aTimeInterval, int maxOutputComponents);

typedef NS_ENUM(short, PCCompareAction)
{
	CompareActionAll = 0,
	CompareActionTransfer = 1,
	CompareActionDelete,
	CompareActionSkip
};

@interface PCComparisonOperation : PCFSOperation <TranscriptConnection>

@property (strong) PCNode *source;
@property (strong) PCNode *destination;

@property BOOL followSymlinks;
@property BOOL compareUsingSize;
@property (strong) NSDate* modificationCutOffDate;
@property BOOL deleteOrphanFiles;
@property NSTimeInterval serverTimeOffset;

@property (assign) id<ConnectionTranscriptDelegate> transcriptDelegate;

- (id)initWithSourceFolder:(PCNode*)source destination:(PCNode*)destination;

@end


@interface PCReportItem : NSObject

/* Path of preflighted node or destination node */
@property (strong) NSString *path;
@property (strong) NSString *displayPath;
@property (strong) NSString *destinationPath;

@property (assign) PCCompareAction action;
@property (strong) NSString *message;
@property (assign) BOOL enabled;

+ (PCReportItem*)report;

@end
