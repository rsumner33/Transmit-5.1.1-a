//
//  PCLocalNewFolderOperation.h
//  Studio
//
//  Created by Wade Cosgrove on 3/15/06.
//  Copyright 2006 Panic Inc. All rights reserved.
//

#import "PCLocalNewFileOperation.h"
#import "PCRemoteTransferOperation.h"

@interface PCLocalNewFolderOperation : PCLocalNewFileOperation <PCOperationPathProvider>
@end
