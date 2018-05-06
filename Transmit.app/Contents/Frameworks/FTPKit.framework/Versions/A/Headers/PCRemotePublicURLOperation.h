//
//  PCRemotePublicURLOperation.h
//  FTPKit
//
//  Created by Will Cosgrove on 3/14/16.
//  Copyright © 2016 Panic Inc. All rights reserved.
//

#import <FTPKit/FTPKit.h>

@interface PCRemotePublicURLOperation : PCRemoteOperation <PCSpooledProcessingOperation>

extern NSString* const kPublicURLCreateWithLogin;
extern NSString* const kPublicURLMakeSecure;
extern NSString* const kPublicURLSiteURL;
extern NSString* const kPublicURLRemotePath;

@property (assign) BOOL createWithLogin;
@property (assign) BOOL makeSecure;

@property (retain) NSString *siteURL;
@property (retain) NSString *remotePath;

@end
