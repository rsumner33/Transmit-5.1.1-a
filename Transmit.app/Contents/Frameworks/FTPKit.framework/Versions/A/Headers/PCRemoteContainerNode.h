//
//  PCRemoteContainerNode.h
//  FTPKit
//
//  Created by Logan Collins on 8/13/14.
//  Copyright (c) 2014 Panic Inc. All rights reserved.
//

#import <FTPKit/PCRemoteFolderNode.h>


typedef NS_ENUM(NSUInteger, PCRemoteContainerType) {
    PCRemoteContainerTypeS3 = 0,		// S3 bucket
    PCRemoteContainerTypeSwift,			// Swift container
    PCRemoteContainerTypeAzure,			// Azure container
    PCRemoteContainerTypeDreamObjects,  // DreamObjects bucket
	PCRemoteContainerTypeB2,			// B2 bucket
    PCRemoteContainerTypeOneDrive,      // OneDrive drive
    PCRemoteContainerTypeSlack,         // Slack channel
	PCRemoteContainerTypeCloudFiles,	// Cloud Files Regions
    PCRemoteContainerTypeGoogleDrive    // Google Drive shared files container
};


@interface PCRemoteContainerNode : PCRemoteFolderNode

@property (readonly) PCRemoteContainerType containerType;

@end


// Uniform Type Identifiers

// Should all inherit from kUTTypeDirectory
FTPKIT_EXTERN NSString * const PCTypeIdentifierS3Bucket;
FTPKIT_EXTERN NSString * const PCTypeIdentifierSwiftContainer;
FTPKIT_EXTERN NSString * const PCTypeIdentifierAzureContainer;
FTPKIT_EXTERN NSString * const PCTypeIdentifierB2Bucket;
FTPKIT_EXTERN NSString * const PCTypeIdentifierDreamObjectsBucket;
FTPKIT_EXTERN NSString * const PCTypeIdentifierGoogleDriveSharedContainer;

