//
//  PCConnectionConfiguration.h
//  FTPKit
//
//  Created by Logan Collins on 11/4/14.
//  Copyright (c) 2014 Panic Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FTPKit/FTPKitConstants.h>
#import <FTPKit/FTPKitDefines.h>


NS_ASSUME_NONNULL_BEGIN


@class PCCredentials;
@protocol PCConnectionConfigurationDelegate;


// Keys for protocol feature keys
FTPKIT_EXTERN NSString * const PCConnectionFeatureMoveKey;						// default YES
FTPKIT_EXTERN NSString * const PCConnectionFeatureUploadResumeKey;				// default NO
FTPKIT_EXTERN NSString * const PCConnectionFeatureUploadEmptyFileKey;			// default YES
FTPKIT_EXTERN NSString * const PCConnectionFeatureUploadOverwriteExistingKey;	// default YES
FTPKIT_EXTERN NSString * const PCConnectionFeatureDownloadResumeKey;			// default YES
FTPKIT_EXTERN NSString * const PCConnectionFeatureDeleteRecursiveKey;			// default NO, can delete non-empty folders
FTPKIT_EXTERN NSString * const PCConnectionFeatureGeneratePublicURLKey;			// default NO
FTPKIT_EXTERN NSString * const PCConnectionFeatureRemoteCopyKey;                // default NO
FTPKIT_EXTERN NSString * const PCConnectionFeatureRequiresDirectoryTraversalKey;// default NO, must navigate to folders from root
FTPKIT_EXTERN NSString * const PCConnectionFeatureNodeAttributesKey;			// default NO
FTPKIT_EXTERN NSString * const PCConnectionFeatureRemoteCopyRecursiveKey;		// default NO
FTPKIT_EXTERN NSString * const PCConnectionFeatureRateLimitingKey;				// default NO
FTPKIT_EXTERN NSString * const PCConnectionFeatureBlindDownloadKey;				// default NO

// S3 features
FTPKIT_EXTERN NSString * const PCConnectionFeatureS3BucketRegionPrefixesKey;
FTPKIT_EXTERN NSString * const PCConnectionFeatureS3BucketLocalizedRegionNamesKey;


/*!
 * @class PCConnectionConfiguration
 * @abstract Specified connection-specific configuration options
 */
@interface PCConnectionConfiguration : NSObject <NSCopying>

/*!
 * @method defaultConfiguration
 * @abstract The default connection configuration
 * 
 * @discussion
 * Applications can customize this configuration before making any connections to apply defaults
 * for options not overridden by more specific configurations.
 */
+ (PCConnectionConfiguration *)defaultConfiguration;


// Configurations for protocols
// Connection subclasses should register their default configuration in +initialize
+ (PCConnectionConfiguration *)configurationForProtocol:(FTPKitProtocol)protocol;


@property (readonly) FTPKitProtocol protocol;


// Features
- (nullable id)valueForFeature:(NSString *)feature;
- (void)setValue:(nullable id)value forFeature:(NSString *)feature;

+ (BOOL)protocol:(FTPKitProtocol)protocol supportsFeature:(NSString *)featureKey;

+ (BOOL)isValidContainerName:(NSString *)name forProtocol:(FTPKitProtocol)protocol;

// Localized Strings
+ (nullable NSString *)defaultLocalizedStringForKey:(NSString *)key;
- (nullable NSString *)localizedStringForKey:(NSString *)key;
- (void)setLocalizedString:(nullable NSString *)string forKey:(NSString *)key;


// Whether connections require authorization through means other than username-password (such as OAuth).
// If YES, authorization should be handled through PCOperationGroupDelegate
@property (assign) BOOL requiresOpaqueAuthorization;
@property (nullable, assign) Class authorizationProviderClass;

@property (copy) NSString *OAuthConsumerKey;
@property (copy) NSString *OAuthConsumerSecret;


// Remote Observation
@property (nullable, assign) Class remoteObservationProviderClass;

@end


@interface PCConnectionConfiguration (ConfigurationDelegate)

// Configuration delegate
// Applications can set an object to allow the kit to delegate certain configuration to that object
+ (id <PCConnectionConfigurationDelegate>)configurationDelegate;
+ (void)setConfigurationDelegate:(nullable id <PCConnectionConfigurationDelegate>)delegate;

// Loads userland configuration into the given credentials
+ (void)loadConfigurationForCredentials:(PCCredentials *)credentials;

// Load userland configuration and dispatches notifications to specific kit objects
// to inform them that the configuration of the credentials has changed
+ (void)loadConfigurationForCredentials:(PCCredentials *)credentials expireConnections:(BOOL)expire;

@end


@protocol PCConnectionConfigurationDelegate <NSObject>

@optional

// Allows the delegate to load application-specific configuration for a set of credentials
// (Such as options specified in the application's preferences)
- (void)loadConfigurationForCredentials:(PCCredentials *)credentials;

@end


// Localized string keys

FTPKIT_EXTERN NSString * const PCConnectionLocalizedUsernameKey;    // The username credential
FTPKIT_EXTERN NSString * const PCConnectionLocalizedPasswordKey;    // The password credential


NS_ASSUME_NONNULL_END

