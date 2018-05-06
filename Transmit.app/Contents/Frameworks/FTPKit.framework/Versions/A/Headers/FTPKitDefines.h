//
//  FTPKitDefines.h
//  FTPKit
//
//  Created by Logan Collins on 7/3/14.
//  Copyright (c) 2014 Panic Inc. All rights reserved.
//


#define FTPKIT_EXTERN extern __attribute__((visibility("default")))
#define FTPKIT_INLINE static inline __attribute__((visibility("default")))

#define FTPKIT_DEPRECATED(reason) __attribute__((deprecated(reason)))
