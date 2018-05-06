//
//  PCLocalUnarchiveOperation.h
//  FTPKit
//
//  Created by Logan Collins on 9/15/14.
//  Copyright (c) 2014 Panic Inc. All rights reserved.
//

#import <FTPKit/PCFSOperation.h>


@class PCFolderNode;


@interface PCLocalUnarchiveOperation : PCFSOperation

- (instancetype)initWithNode:(PCNode *)node destinationProvider:(NSObject<PCOperationPathProvider> *)destinationProvider;

@end
