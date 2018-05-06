//
//  NSMutableURLRequest+FTPKitAdditions.h
//  FTPKit
//
//  Created by Logan Collins on 2/12/13.
//  Copyright (c) 2013 Panic Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSMutableURLRequest (FTPKitAdditions)

- (void)pc_signWithOAuthConsumerKey:(NSString *)consumerKey consumerSecret:(NSString *)consumerSecret accessKey:(NSString *)accessKey accessSecret:(NSString *)accessSecret;

@end
