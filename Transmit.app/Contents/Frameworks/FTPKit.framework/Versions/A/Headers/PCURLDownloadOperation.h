//
//  PCURLDownloadOperation.h
//  FTPKit
//
//  Created by Logan Collins on 7/22/14.
//  Copyright (c) 2014 Panic Inc. All rights reserved.
//

#import <FTPKit/PCRemoteTransferOperation.h>

@class PCFolderNode;

@interface PCURLDownloadOperation : PCRemoteTransferOperation

- (instancetype)initWithURL:(NSURL*)url destinationProvider:(NSObject <PCOperationPathProvider>*)provider;

@end
