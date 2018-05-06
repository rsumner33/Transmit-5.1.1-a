//
//  PCOperationPathProviderProtocol.h
//  FTPKit
//
//  Created by Wade Cosgrove on 7/21/16.
//  Copyright © 2016 Panic Inc. All rights reserved.
//

#ifndef PCOperationPathProviderProtocol_h
#define PCOperationPathProviderProtocol_h

#import "FTPKitConstants.h"
#import "PCConnectionAuthorizationProvider.h"

@class AbstractConnection;
@class PCProgress;
@class PCCredentials;
@class PCTrust;
@class PCNode;

@protocol PCFolderNode;

@protocol PCOperationPathProvider <NSObject>

@required
- (NSString*)providerPath;

@optional
- (NSObject <PCOperationPathProvider> *)spoolerProviderForNode:(PCNode*)node; // only called from the spooler at the moment. Use for custom logic for generating paths for an item. 
- (PCNode <PCFolderNode>*)resolveDestinationError:(NSError**)outError;

@end


@protocol PCSpooledTransferOperation <NSObject>
+ (instancetype)operationWithNode:(PCNode*)node destinationProvider:(NSObject <PCOperationPathProvider> *)destination;
- (NSObject <PCOperationPathProvider> *)destinationProvider;

@optional
- (void)setCustomFilename:(NSString*)filename;

@end

@protocol PCSpooledProcessingOperation <NSObject>
+ (instancetype)operationWithNode:(PCNode*)node arguments:(NSObject*)arguments;
@optional
+ (BOOL)spoolerSkipParentAfterChildError; // Defaults to NO, informs spooler how to process parent folders if one of their children fails
@end


@protocol PCProgressDelegate <NSObject>

@required
- (void)progressDidChange:(PCProgress*)progress;
- (void)progressShouldCancel:(PCProgress*)progress;

@end


@protocol PCFolderNode
@optional

// accessors

- (NSLock*)busyLock;
- (pthread_rwlock_t*)contentsLock;
- (NSSet*)contentsWithHidden:(BOOL)flag;
- (NSSet*)contentsWithHidden:(BOOL)hiddenFlag includeDSStore:(BOOL)DSStoreFlag;
- (NSArray*)contentsWithSortType:(FTPSortType)sortType includeHidden:(BOOL)hidden ascending:(BOOL)ascending;
- (NSArray*)contentsWithSortType:(FTPSortType)sortType includeHidden:(BOOL)hidden includeDSStore:(BOOL)store ascending:(BOOL)ascending;
- (NSDictionary*)contentsDict;
- (NSUInteger)countWithHidden:(BOOL)flag;
- (NSArray*)filenamesOfContents;
- (NSArray*)displayNamesOfContents;
- (BOOL)isExpired;
- (void)setExpired:(BOOL)flag;
- (BOOL)isPackage;

// misc
- (void)addNodes:(NSObject<NSFastEnumeration>*)nodes;
- (void)addNodes:(NSObject<NSFastEnumeration>*)nodes useContentsLock:(BOOL)flag; //private, do not use
- (void)childNodeWasRenamed:(PCNode*)node oldName:(NSString*)oldName;
- (void)removeAllNodes;
- (void)removeNodes:(NSObject<NSFastEnumeration>*)nodes;
- (Class)containerClass;
- (void)flushBufferedChanges;

// Reserves the filename in the folder, so future calls to filenamesOfContents will include the future filename.
// Requires a balancing call to removePendingFilename: if addNode: is not called with the pending filename.
- (NSString*)uniquePendingFilename:(NSString*)filename copySuffix:(NSString*)suffix;
- (void)removePendingFilename:(NSString*)name;

// the arguments will be retained, not copied, and contentsDict should have been created using the PCFolderNodeCreating category above to maintain composition insensitivity
- (void)setContentsDict:(NSMutableDictionary*)contentsDict visibleContents:(NSMutableSet*)visibleContents;

@end


@protocol AbstractConnectionInterfaceDelegate
@required

/* connection:presentError:
 * This callback tells the delegate to present an error and wait for a reply
 */

- (NSInteger)connection:(AbstractConnection*)connection presentError:(NSError*)error;
- (void)connection:(AbstractConnection*)connection promptForPasswordWithMessage:(NSString *)message responseHandler:(void (^)(NSString *response, FTPKitModalResponse responseCode))handler contextInfo:(void *)contextInfo;
- (void)connection:(AbstractConnection *)connection promptForUsernameAndPasswordWithMessage:(NSString *)message responseHandler:(void (^)(NSString *, NSString *, FTPKitModalResponse))handler contextInfo:(void *)contextInfo;
- (void)connection:(AbstractConnection *)connection promptForKeyPassphraseWithMessage:(NSString *)message responseHandler:(void (^)(NSString *response, FTPKitModalResponse responseCode))handler contextInfo:(void *)contextInfo;
- (void)connection:(AbstractConnection *)connection promptForVerificationCodeWithTitle:(NSString*)title andMessage:(NSString*)message responseHandler:(void (^)(NSString *response, FTPKitModalResponse responseCode))handler contextInfo:(void *)contextInfo;
- (void)connection:(AbstractConnection *)connection promptForHostKeyMismatchWithTitle:(NSString*)title andMessage:(NSString*)message responseHandler:( void (^)(FTPKitModalResponse responseCode))handler contextInfo:(void *)contextInfo;
- (void)connection:(AbstractConnection *)connection promptForPinWithMessage:(NSString*)message responseHandler:(void (^)(NSString *response, FTPKitModalResponse responseCode))handler contextInfo:(void *)contextInfo;

- (BOOL)connection:(AbstractConnection*)connection isWorthyTrust:(PCTrust*)trust;

- (void)connection:(AbstractConnection*)connection cancelAllOperations:(BOOL)shouldCancel;

@end


@protocol AbstractConnectionProgressMonitoring
@required

/* connection:transferredBytes:throughput:stalled:
 * This callback informs the receiver of the file transfer progress.
 * Bytes are the total number of bytes transferred so far in the current file.
 * Throughput is the transfer rate in bytes per second and stalled indicates if the connection is currently stalled.
 */
- (void)connection:(AbstractConnection*)connection transferredBytes:(long long)bytes stalled:(BOOL)stalled;
- (void)substractTransferredBytes:(int64_t)bytes forConnection:(AbstractConnection*)connection;

@end


@protocol AbstractConnectionStreaming
@required

- (NSUInteger)connection:(AbstractConnection*)connection streamBytes:(void*)bytes length:(NSUInteger)length;

@end

@protocol AbstractConnectionAuthentication <NSObject>

@optional

- (PCConnectionAuthorizationResult)connection:(AbstractConnection*)connection authorizeCredentialsIfNeeded:(BOOL)authorizeIfNeeded;

@end


@protocol PCCredentialsProvider <NSObject>

@required
- (PCCredentials*)credentials;
- (NSString*)identifier;
- (NSString*)name;

@optional
- (NSString*)localPath;
- (NSString*)remotePath;
- (NSString*)siteURL;

- (void)setOAuthCode:(NSString*)value;
- (void)setOAuthAccessToken:(NSString*)value;
- (void)setOAuthEndpoint:(NSString*)value;
- (void)setExpiryDate:(NSDate*)value;

- (void)setFileListEncoding:(NSStringEncoding)encoding;
- (NSStringEncoding)fileListEncoding;

#if !TARGET_OS_IPHONE
- (NSImage*)icon;
- (NSImage*)smallIcon;
#endif

// Do not use this method if at all possible
- (void)credentialsDidUpdate:(PCCredentials *)credentials saveInKeychain:(BOOL)saveInKeychain;

@end

#endif /* PCOperationPathProviderProtocol_h */
