//
//  PCConnectionAuthorizationProvider.h
//  FTPKit
//
//  Created by Logan Collins on 8/22/13.
//  Copyright (c) 2013 Panic Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FTPKit/FTPKitConstants.h>
#import <FTPKit/FTPKitDefines.h>


@class PCCredentials;
@protocol PCConnectionAuthorizationProviderDelegate;


typedef NS_ENUM(NSUInteger, PCConnectionAuthorizationResult) {
    PCConnectionAuthorizationResultSuccess = 0,
    PCConnectionAuthorizationResultFailed = 1,
    PCConnectionAuthorizationResultCancelled = 2,
};


/*!
 * @class PCConnectionAuthorizationProvider
 * @abstract Abstract superclass of objects that are able to request or generate credentials for a service on behalf of the user
 */
@interface PCConnectionAuthorizationProvider : NSObject

/*!
 * @method credentialsRequireAuthorization:
 * @abstract Returns whether the credentials require authorization before use
 * 
 * @discussion
 * This method must be implemented by subclasses.
 */
+ (BOOL)credentialsRequireAuthorization:(PCCredentials *)credentials;


- (instancetype)initWithCredentials:(PCCredentials *)credentials NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;


@property (strong, readonly) PCCredentials *credentials;
@property (weak) id <PCConnectionAuthorizationProviderDelegate> delegate;


/*!
 * @method performAuthorization:
 * @abstract Invoked to perform the authorization workflow
 *
 * @param full
 * Do a refresh or full authorization
 *
 * @discussion
 * This method must be implemented by subclasses.
 */
- (void)performAuthorization:(BOOL)full;

/*!
 * @method cancelAuthorization
 * @abstract Invoked to cancel the authorization workflow
 *
 * @discussion
 * This method must be implemented by subclasses.
 */
- (void)cancelAuthorization;

@end


/*!
 * @protocol PCConnectionAuthorizationProviderDelegate
 * @abstract Implemented by an authorization provider's delegate
 */
@protocol PCConnectionAuthorizationProviderDelegate <NSObject>

/*!
 * @method authorizationProviderDidFinish:withCredentials:userInfo:
 * @abstract The authorization process has finished
 *
 * @param provider
 * The authorization provider
 *
 * @param result
 * The result of the authorization
 */
- (void)authorizationProvider:(PCConnectionAuthorizationProvider *)provider didFinishWithResult:(PCConnectionAuthorizationResult)result error:(NSError *)error;


/*!
 * @method authorizationProvider:presentURLRequest:callbackURL:responseHandler:
 * @abstract Invoked to request the delegate present a URL request to the user, and listen for a callback URL to be invoked
 *
 * @param provider
 * The authorization provider
 *
 * @param request
 * The URL request to present
 * 
 * @param callbackURL
 * The callback URL for which to listen in response to user action
 *
 * @param responseHandler
 * The block to invoke when the callback URL has been encountered
 * 
 * @discussion
 * The delegate should listen for the callback URL without including query parameters (only the base URL and path).
 */
- (void)authorizationProvider:(PCConnectionAuthorizationProvider *)provider presentURLRequest:(NSURLRequest *)request callbackURL:(NSURL *)callbackURL responseHandler:(void (^)(NSURL *responseURL, void(^authorizationCompletionHandler)(void)))responseHandler;

@end
