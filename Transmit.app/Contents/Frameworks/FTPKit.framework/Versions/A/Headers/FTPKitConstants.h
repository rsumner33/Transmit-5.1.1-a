#import <Foundation/Foundation.h>
#import "FTPKitDefines.h"


// types

typedef NS_ENUM(uint32_t, PCFileSystemType) {
	PCFS_GenericItem =  UINT32_C(0x464b6769), // 'FKgi'
	PCFS_File =         UINT32_C(0x464b6669), // 'FKfi'
	PCFS_Folder =       UINT32_C(0x464b666f), // 'FKfo'
	PCFS_Alias =        UINT32_C(0x464b616c), // 'FKal'
#if !TARGET_OS_IPHONE
	PCFS_SmartFolder =  UINT32_C(0x464b736d) // 'FKsm'
#endif
};

typedef NS_ENUM(NSUInteger, PCFileSystemIconSize) {
#if TARGET_OS_IPHONE
	PCFS_SmallIcon = 32,
	PCFS_ShelfIcon = 71,
	PCFS_ThumbnailIcon = 210
#else
	PCFS_SmallIcon = 16,
	PCFS_NormalIcon = 32,
	PCFS_ThumbnailIcon = 128,
	PCFS_256Icon = 256,
	PCFS_512Icon = 512,
	PCFS_1024Icon = 1024
#endif
};


typedef NS_ENUM(NSInteger, PCFileSystemOperationType) {
	PCFS_OperationTypeUnknown = -1,
	PCFS_OperationTypeGeneric = 0,
	
	PCFS_LocalCopy = 1,
	PCFS_LocalListDirectory,
	PCFS_LocalMove,
	PCFS_LocalRename,
	PCFS_LocalNewFile,
	PCFS_LocalNewFolder,
	PCFS_LocalTrash,
	PCFS_LocalArchive,
	PCFS_LocalUnarchive,
	PCFS_LocalSumSize,
	PCFS_LocalChangeAttributes,
	PCFS_RemoteChangeDirectory,
	PCFS_RemoteListDirectory,
	PCFS_RemoteCacheNodes,
	PCFS_RemoteChangeAttributes,
	PCFS_RemoteConnect,
	PCFS_RemoteGetAttributes,
	PCFS_RemoteNewFile,
	PCFS_RemoteNewFolder,
	PCFS_RemoteTrash,
	PCFS_RemoteRename,
	PCFS_ResolveSymlink,
	PCFS_RemoteMove,
	PCFS_RemoteSumSize,
	PCFS_RemoteDownload,
	PCFS_RemoteUpload,
	PCFS_HTTPDownload,
	//PCFS_RemotePublish,
	PCFS_RemoteCopy,
	PCFS_RawCommand,
	//PCFS_RemoteReversePublish,
	//PCFS_RemoteSynchronize,
	//PCFS_RemoteFXP,
	PCFS_RemoteSeverToServer,
	PCFS_Comparison,
	PCFS_RemotePublicURL,
	PCFS_OperationSpooler,
	PCFS_RemoteTimeOffset,
	PCFS_RemoteMount
};


typedef NS_ENUM(NSUInteger, PCOperationState) {
	PCOperationStateReady = 0,
	PCOperationStateExecuting,
	PCOperationStateCancelled,
	PCOperationStateFinished
};


// notifications

//FTPKIT_EXTERN NSString * const PCFSOperationWillStartNotification;
//FTPKIT_EXTERN NSString * const PCFSOperationDidStartNotification;
//FTPKIT_EXTERN NSString * const PCFSOperationDidEndNotification;

FTPKIT_EXTERN NSString * const PCExpireCredentialsNotification;

FTPKIT_EXTERN NSString * const PCFSFolderContentsDidChangeNotification;
FTPKIT_EXTERN NSString * const PCFSNodeAttributesChangedNotification;
FTPKIT_EXTERN NSString * const PCFSDidDeleteNodesNotification;
FTPKIT_EXTERN NSString * const PCFSFolderNeedsDisplayNotification;
FTPKIT_EXTERN NSString * const PCFSDidOverwriteNodeNotification;
FTPKIT_EXTERN NSString * const PCFSNodeNameChangedNotification;

FTPKIT_EXTERN NSString * const PCOAuthValueChangedNotification;

// constants

FTPKIT_EXTERN NSString * const PCFSSortAscending;
FTPKIT_EXTERN NSString * const PCFSSortDescending;
FTPKIT_EXTERN NSString * const PCFSFileNode;
FTPKIT_EXTERN NSString * const PCFSFilePath;
FTPKIT_EXTERN NSString * const PCFSErrorNode;
FTPKIT_EXTERN NSString * const PCFSErrorNodes;
FTPKIT_EXTERN NSString * const PCFSConnection;
FTPKIT_EXTERN NSString * const PCFSNotifyingOperation;
FTPKIT_EXTERN NSString * const PCFSNotifyingOperationGroup;
FTPKIT_EXTERN NSString * const PCFSRemovedNodes;
FTPKIT_EXTERN NSString * const PCFSDeletedNodes;
FTPKIT_EXTERN NSString * const PCFSAddedNodes;
FTPKIT_EXTERN NSString * const PCFSNodeStatus;
FTPKIT_EXTERN NSTimeInterval const PCTimeOffsetAutomatic;
FTPKIT_EXTERN NSString * const PCFSTransient;
FTPKIT_EXTERN NSString * const PCTransmitSFTPProxyUser;

// Drag types for interapplication remote drag & drop

FTPKIT_EXTERN NSString * const PCRemoteURLPboardType;

// user info keys for conflict resolution & other notifications

FTPKIT_EXTERN NSString * const PCFSSourceNode;
FTPKIT_EXTERN NSString * const PCFSDestinationNode;
FTPKIT_EXTERN NSString * const PCFSCachedNode;

FTPKIT_EXTERN NSString * const PCFSConflictBehavior;
FTPKIT_EXTERN NSString * const PCFSName;
FTPKIT_EXTERN NSString * const PCFSAlert;
FTPKIT_EXTERN NSString * const PCFSAlertError; 	// NSError, the error generating the alert (may be nil)
FTPKIT_EXTERN NSString * const PCFSAlertResponse; // NSNumber (NSInteger)
FTPKIT_EXTERN NSString * const PCFSAlertUserInfo;


// transfer mode
enum {
	kFTPKitTransferModeAutomatic = -1
};

// OAuth notification constants which are KVO compliant in TRConnectionItem

FTPKIT_EXTERN NSString * const kOAuthAccessToken;
FTPKIT_EXTERN NSString * const kOAuthCode;
FTPKIT_EXTERN NSString * const kOAuthEndpoint;
FTPKIT_EXTERN NSString * const kExpiryDate;


/* FTPKitProtocol
 * These are the types of server protocols that FTPKit supports.  Use these to 
 * create a connection with the proper subclass.
 */

typedef NS_ENUM(uint32_t, FTPKitProtocol) {
	kFTPKitProtocolFTP					= UINT32_C(0x46545020), // 'FTP ', "FTP"
	kFTPKitProtocolFTPSSL				= UINT32_C(0x4653534c), // 'FSSL', "FTP with Implicit SSL"
	kFTPKitProtocolFTPTLS				= UINT32_C(0x46545053), // 'FTPS', "FTP with TLS/SSL"
	kFTPKitProtocolSFTP					= UINT32_C(0x53465450), // 'SFTP', "SFTP"
	kFTPKitProtocolWebDAV				= UINT32_C(0x57444156), // 'WDAV', "WebDAV"
	kFTPKitProtocolWebDAVS				= UINT32_C(0x53444156), // 'SDAV', "WebDAV with HTTPS"
	kFTPKitProtocolS3					= UINT32_C(0x53332020), // 'S3  ', "Amazon S3"
	kFTPKitProtocolDreamObjects			= UINT32_C(0x444d4f42), // 'DMOB', "DreamHost DreamObjects"
	kFTPKitProtocolSwift				= UINT32_C(0x53574654), // 'SWFT', "Swift"
	kFTPKitProtocolCloudFiles			= UINT32_C(0x52534346), // 'RSCF', "Rackspace Cloud Files"
	kFTPKitProtocolDropbox				= UINT32_C(0x44425820), // 'DBX ', "Dropbox"
    kFTPKitProtocolAzure				= UINT32_C(0x415a5552), // 'AZUR', "Microsoft Azure"
    kFTPKitProtocolSMB					= UINT32_C(0x534D4220), // 'SMB ', "Server Message Block"
	kFTPKitProtocolAmazonCloudDrive		= UINT32_C(0x415a4344), // 'AZCD', "Amazon Cloud Drive"
	kFTPKitProtocolBBB2					= UINT32_C(0x42424232), // 'BBB2', "BackBlaze B2 Cloud Storage"
	kFTPKitProtocolOneDrive				= UINT32_C(0x31445256), // '1DRV', "Microsoft OneDrive"
	kFTPKitProtocolOneDriveForBusiness	= UINT32_C(0x31445242), // '1DRB', "Microsoft OneDrive for Business"
	kFTPKitProtocolGoogleDrive			= UINT32_C(0x47445256), // 'GDRV', "Google Drive"
	kFTPKitProtocolBox					= UINT32_C(0x424f5820), // 'BOX ', "Box"
	kFTPKitProtocolSlack				= UINT32_C(0x534c434b), // 'SLCK', "Slack"
	kFTPKitProtocolUnknown				= UINT32_C(0x3F3F3F3F), // '????', "Testing Only - Unknown Type"

};


/* FTPKitServerType
* These types are used with the the server specific option
* "kFTPConnectionServerType".
*/

typedef NS_ENUM(uint32_t, FTPKitServerType) {
	// do not change existing values as they are saved in preferences
	// FTP
	kFTPKitServerTypeUnknown = 0,
	kFTPKitServerTypeUNIX = 1,
	kFTPKitServerTypePetersServer = 2,
	kFTPKitServerTypeWebStar = 3,
	kFTPKitServerTypeVMS = 4,
	kFTPKitServerTypeAppleShareIP = 5,
	kFTPKitServerTypeLukemftpd = 6,
	kFTPKitServerTypeWebStarUNIX = 7,
	kFTPKitServerTypeWindowsNT = 8,
	kFTPKitServerTypeWarFTPd = 9,
	kFTPKitServerTypeDiskXtender = 10,
	kFTPKitServerTypeFileZilla = 11,
	kFTPKitServerTypeBSD44 = 12,
	kFTPKitServerTypeSnapOS	= 13,
	kFTPKitServerTypeHummingBird = 14, // C:\\WINDOWS\\ paths
	kFTPKitServerTypeTCPWareVMSUnix = 16,
	kFTPKitServerTypeNetware = 17,
	kFTPKitServerTypeConnectEnterprise = 18,
	kFTPKitServerTypeDriveHQ = 19,
	kFTPKitServerTypeGoogleUploads = 20,
	kFTPKitServerTypeDawningSNI = 21,
	kFTPKitServerTypeOS400 = 22,
	kFTPKitServerTypeYahooSmallBusiness = 23,
	kFTPKitServerTypeTViX = 24,
	kFTPKitServerTypePersonalFTPServerPro = 25,
	kFTPKitServerTypeKnownUnknown = 26,
	kFTPKitServerTypeMultiNetUnixEmulation = 27,
	kFTPKitServerTypeMicrosoftOffice365 = 28,
	
	// SFTP
	kFTPKitServerTypeGenericSFTP = 100,
	
	// Cloud
	kFTPKitServerTypeAmazonS3 = 300,
	kFTPKitServerTypeGoogleCloudStorage = 301,
	kFTPKitServerTypeDreamObjects = 302,
	
	// Other
	kFTPKitServerGenericLastResort = 15,
};

/* FTPKitCompositionType
 * Constants used when encoding UTF8 strings
 */
typedef NS_ENUM(NSInteger, FTPKitCompositionType) {
	kFTPKitCompositionTypePrecomposed = 0,
	kFTPKitCompositionTypeDecomposed = 1
};


/* FTPKitModalResponseType
 * Constants used when presenting modal requests
 */
typedef NS_ENUM(NSUInteger, FTPKitModalResponse) {
	kFTPKitModalResponseCancel = 0,
	kFTPKitModalResponseOK = 1,
	kFTPKitModalResponseAborted = 2
};

#pragma mark - FTPKit Functions

/**
 * FTPKitProtocolIsValid
 * Returns whether a given FTPKitProtocol value is supported in the current framework
 */
FTPKIT_EXTERN BOOL FTPKitProtocolIsSupported(FTPKitProtocol protocol);

FTPKIT_EXTERN FTPKitProtocol FTPKitProtocolFromURL(NSURL *URL);
FTPKIT_EXTERN NSString * FTPKitProtocolToScheme(FTPKitProtocol protocol);
FTPKIT_EXTERN uint16_t FTPKitSuggestedPortForFTPKitProtocol(FTPKitProtocol protocol);
FTPKIT_EXTERN CFTypeRef FTPKitProtocolToCFTypeRef(FTPKitProtocol protocol);

FTPKIT_EXTERN FTPKitProtocol FTPKitProtocolFromString(NSString *string);
FTPKIT_EXTERN NSString * FTPKitProtocolToString(FTPKitProtocol protocol);

FTPKIT_EXTERN NSString * FTPKitProtocolDisplayName(FTPKitProtocol protocol);

#if !TARGET_OS_IPHONE
FTPKIT_EXTERN uint32_t FTPKitProtocolToSecProtocol(FTPKitProtocol protocol);
#endif

#pragma mark -
FTPKIT_EXTERN Class FTPKitClassForFTPKitProtocol(FTPKitProtocol protocol);

FTPKIT_EXTERN NSString * FTPKitConvertEncodings(NSString* string, NSStringEncoding from, NSStringEncoding to);

/* FTPUNIXParserNameDateSpacing
 * These keys are for name date line spacing under
 * advanced prefs
 */

typedef NS_ENUM(NSUInteger, FTPUNIXParserNameDateSpacing) {
	FTPUNIXParserNameDateSpacingUnknown = 0,
	FTPUNIXParserNameDateSpacingOne = 1,
	FTPUNIXParserNameDateSpacingTwo = 2,
	FTPUNIXParserNameDateSpacingOneOrTwo = 3
};


/* FTPSortType
 * These keys are for sorting folder contents. Order should remain constant, values can be tags.
 */

typedef NS_ENUM(NSUInteger, FTPSortType) {
	kFTPSortTypeNone = 0,
	kFTPSortTypeModificationDate,
	kFTPSortTypeDescendant,
	kFTPSortTypeDisplayName,
	kFTPSortTypeFolderAboveFile,
	kFTPSortTypeGroup,
	kFTPSortTypeKind,
	kFTPSortTypeOwner,
	kFTPSortTypePermissions,
	kFTPSortTypeSize,
	kFTPSortTypeCreationDate
};


#define DECLARE_KEY(key) FTPKIT_EXTERN NSString * const key
#define DECLARE_VALUE(value) FTPKIT_EXTERN NSString * const value

/* File Attributes
 * These attributes can be set on individual files via setAttributes:forItems:
 */

// Generic
DECLARE_KEY(kFTPKitAttributeOwner); // NSString or NSNull if not applicable
DECLARE_KEY(kFTPKitAttributeGroup); // NSString or NSNull if not applicable
DECLARE_KEY(kFTPKitAttributeOwnerAccountID); // NSNumber
DECLARE_KEY(kFTPKitAttributeGroupAccountID); // NSNumber
DECLARE_KEY(kFTPKitAttributePermissions); // FilePermissions

// S3
DECLARE_KEY(kFTPKitAttributeS3CanonicalOwner); // NSString
DECLARE_KEY(kFTPKitAttributeS3BucketRegionIndex); // NSNumber
DECLARE_KEY(kFTPKitAttributeS3BucketLocationConstraint); // NSString
DECLARE_KEY(kFTPKitAttributeS3BucketLoggingStatus); // BucketLoggingStatus
DECLARE_KEY(kFTPKitAttributeS3BucketLoggingEnabled); // NSNumber (BOOL)
DECLARE_KEY(kFTPKitAttributeS3BucketLoggingDestination); // NSString
DECLARE_KEY(kFTPKitAttributeS3BucketLoggingPrefix); // NSString
DECLARE_KEY(kFTPKitAttributeS3StorageClass); // NSString
DECLARE_KEY(kFTPKitAttributeS3ServerSideEncryption); // NSString
DECLARE_KEY(kFTPKitAttributeS3WebsiteRedirectLocation); // NSString
DECLARE_KEY(kFTPKitAttributeS3ReadPermissions); // NSString
DECLARE_KEY(kFTPKitAttributeS3WritePermissions); // NSString
DECLARE_KEY(kFTPKitAttributeS3ContentType); // NSString

DECLARE_KEY(kFTPKitAttributeCloudFrontEnabled); // NSNumber (BOOL)
DECLARE_KEY(kFTPKitAttributeCloudFrontDistributions); // NSArray of CloudFrontDistribution
DECLARE_KEY(kFTPKitAttributeCloudFrontDomainName); // NSString
DECLARE_KEY(kFTPKitAttributeCloudFrontCNAMEs); // NSString

// WebDAV
DECLARE_KEY(kFTPKitAttributeWebDAVExecutable); // NSNumber (BOOL)

// Swift
DECLARE_KEY(kFTPKitAttributeContainerCDNEnabled); // NSNumber (BOOL)
DECLARE_KEY(kFTPKitAttributeContainerLogRetentionEnabled); // NSNumber (BOOL)
DECLARE_KEY(kFTPKitAttributeContainerCDNURI); // NSString
DECLARE_KEY(kFTPKitAttributeContainerCDNSSLURI); // NSString
DECLARE_KEY(kFTPKitAttributeReadACL); // NSString
DECLARE_KEY(kFTPKitAttributeWriteACL); // NSString

// Dropbox
DECLARE_KEY(kFTPKitAttributeDropboxRevision); // NSString
DECLARE_KEY(kFTPKitAttributeDropboxIsReadOnly); // NSNumber (BOOL)
DECLARE_KEY(kFTPKitAttributeDropboxSharedFolderIdentifier); // NSString
DECLARE_KEY(kFTPKitAttributeDropboxParentSharedFolderIdentifier); // NSString
DECLARE_KEY(kFTPKitAttributeDropboxLastModifiedByUserName); // NSString
DECLARE_KEY(kFTPKitAttributeDropboxLastModifiedByUserIdentifier); // NSString
DECLARE_KEY(kFTPKitAttributeDropboxMediaDateTaken); // NSDate
DECLARE_KEY(kFTPKitAttributeDropboxMediaDuration); // NSString
DECLARE_KEY(kFTPKitAttributeDropboxMediaDimensions); // NSValue (CGSize)
DECLARE_KEY(kFTPKitAttributeDropboxMediaLocation); // CLLocation

// B2
DECLARE_KEY(kFTPKitAttributeB2BucketType); // NSNumber (int)
DECLARE_KEY(kFTPKitAttributeB2BucketID); // NSString
DECLARE_KEY(kFTPKitAttributeB2FileID); // NSString

// OneDrive
DECLARE_KEY(kFTPKitAttributeOneDriveItemID); // NSString
DECLARE_KEY(kFTPKitAttributeOneDriveLastModifiedByUserName); // NSString
DECLARE_KEY(kFTPKitAttributeOneDrivePublicURL); // NSString

// Google Drive
DECLARE_KEY(kFTPKitAttributeGoogleDriveIsStarred); // NSNumber (BOOL)
DECLARE_KEY(kFTPKitAttributeGoogleDriveIsReadOnly); // NSNumber (BOOL)
DECLARE_KEY(kFTPKitAttributeGoogleDrivePublicURL); // NSString
DECLARE_KEY(kFTPKitAttributeGoogleDriveLastModifiedByUserName); // NSString
DECLARE_KEY(kFTPKitAttributeGoogleDriveMediaDateTaken); // NSDate
DECLARE_KEY(kFTPKitAttributeGoogleDriveMediaDuration); // NSString
DECLARE_KEY(kFTPKitAttributeGoogleDriveMediaDimensions); // NSValue (CGSize)
DECLARE_KEY(kFTPKitAttributeGoogleDriveMediaLocation); // CLLocation
DECLARE_KEY(kFTPKitAttributeGoogleDriveID); //NSString
DECLARE_KEY(kFTPKitAttributeGoogleDriveParents); //NSArray
DECLARE_KEY(kFTPKitAttributeGoogleDriveIsAuthenticatedUser); // NSNumber (BOOL)
DECLARE_KEY(kFTPKitAttributeGoogleDriveExportURL); // NSString

// Amazon Cloud Drive
DECLARE_KEY(kFTPKitAttributeAmazonCloudDriveVersion); // NSString
DECLARE_KEY(kFTPKitAttributeAmazonCloudDriveMD5Checksum); // NSString
DECLARE_KEY(kFTPKitAttributeAmazonCloudDriveMediaDateTaken); // NSDate
DECLARE_KEY(kFTPKitAttributeAmazonCloudDriveMediaDuration); // NSString
DECLARE_KEY(kFTPKitAttributeAmazonCloudDriveMediaDimensions); // NSValue (CGSize)
DECLARE_KEY(kFTPKitAttributeAmazonCloudDriveMediaLocation); // CLLocation
DECLARE_KEY(kFTPKitAttributeAmazonCloudDriveFileID); // NSString

// Box
DECLARE_KEY(kFTPKitAttributeBoxDescription); // NSString
DECLARE_KEY(kFTPKitAttributeBoxSharedLink); // NSString
DECLARE_KEY(kFTPKitAttributeBoxShared); // NSNumber (BOOL)
DECLARE_KEY(kFTPKitAttributeBoxID); // NSString
DECLARE_KEY(kFTPKitAttributeBoxParent); // NSDictionary

// Slack
DECLARE_KEY(kFTPKitAttributeSlackPublicURL); // NSString
DECLARE_KEY(kFTPKitAttributeSlackDownloadURL); // NSString
DECLARE_KEY(kFTPKitAttributeSlackChannelID); // NSString
DECLARE_KEY(kFTPKitAttributeSlackID); // NSString


/* Custom file upload preference Keys */

DECLARE_KEY(kFTPKitPrefKeyDefaultFile); // NSDictionary - Also in TSPrefKeys
DECLARE_KEY(kFTPKitPrefKeyDefaultFolder); // NSDictionary - Also in TSPrefKeys
DECLARE_KEY(kFTPKitPrefKeyEnabled); // NSNumber (bool) - Also in TSPrefKeys
DECLARE_KEY(kFTPKitPrefKeyFTPPermissions); // NSNumber (octal) - Also in TSPrefKeys
DECLARE_KEY(kFTPKitPrefKeyS3Permissions); // NSNumber (octal) - Also in TSPrefKeys
DECLARE_KEY(kFTPKitPrefKeyWebDAVPermissions); // NSNumber (octal) - Also in TSPrefKeys


DECLARE_KEY(kFTPKitPrefKeyCustomS3UploadHeaders); // NSArray of NSDictionary with keys:
DECLARE_KEY(kS3CustomUploadHeadersKeyExtension); // NSString, kS3CustomUploadHeadersValueDefaultExtension for default
DECLARE_KEY(kS3CustomUploadHeadersKeyHeaders); // NSArray of NSDictionary with keys:
DECLARE_KEY(kS3HeaderKeyEnabled); // NSNumber (bool)
DECLARE_KEY(kS3HeaderKeyName); // NSString
DECLARE_KEY(kS3HeaderKeyValue); // NSString

DECLARE_KEY(kS3HeaderKeyServerSideEncryption); // NSString
DECLARE_KEY(kS3HeaderValueServerSideEncryptionKMS); // NSString
DECLARE_KEY(kS3HeaderValueServerSideEncryptionAES256); // NSString
DECLARE_KEY(kS3HeaderValueServerSideEncryptionNone); // NSString

DECLARE_KEY(kS3HeaderKeyStorageClass); // NSString
DECLARE_KEY(kS3HeaderValueStorageClassStandard); // NSString
DECLARE_KEY(kS3HeaderValueStorageClassInfrequent); // NSString
DECLARE_KEY(kS3HeaderValueStorageClassReduced); // NSString
DECLARE_KEY(kS3HeaderValueStorageClassGlacier); // NSString

DECLARE_KEY(kS3HeaderKeyWebsiteRedirectLocation); // NSString

DECLARE_VALUE(kS3CustomUploadHeadersValueDefaultExtension);

/* custom file node property keys */

DECLARE_KEY(kCachedNode);

/* HTTP header keys */

DECLARE_KEY(kHTTPHeaderContentType);
DECLARE_KEY(kHTTPHeaderContentLength);
DECLARE_KEY(kHTTPHeaderContentDisposition);
DECLARE_KEY(kHTTPHeaderCacheControl);
DECLARE_KEY(kHTTPHeaderDestination);
DECLARE_KEY(kHTTPHeaderTransferEncoding);
DECLARE_KEY(kHTTPHeaderDate);
DECLARE_KEY(kHTTPHeaderEtag);
DECLARE_KEY(kHTTPHeaderAuthorization);

/* Swift et al */
DECLARE_KEY(kHTTPHeaderXAuthKey); 
DECLARE_KEY(kHTTPHeaderXAuthUser);
DECLARE_KEY(kHTTPHeaderXAuthToken);
DECLARE_KEY(kHTTPHeaderXCDNManagementURL);
DECLARE_KEY(kHTTPHeaderXStorageURL);
DECLARE_KEY(kHTTPHeaderOffset);
DECLARE_KEY(kHTTPHeaderXLogRetention);
DECLARE_KEY(kHTTPHeaderXCDNEnabled);
DECLARE_KEY(kHTTPHeaderLastModified);
DECLARE_KEY(kHTTPHeaderXCDNURI);
DECLARE_KEY(kHTTPHeaderXCDNSSLURI);
DECLARE_KEY(kHTTPHeaderXContainerRead);
DECLARE_KEY(kHTTPHeaderXContainerWrite);
DECLARE_KEY(kHTTPHeaderXContainerObjectCount);


/* Notifications
 * Notifications not related to the File System
 */

DECLARE_KEY(kFTPKitNotificationCredentialOptionsDidChange);

/* NSError Domains
 * These are the domains which FTPKit will report errors on via the NSError API
 */

DECLARE_KEY(kFTPKitErrorDomain);

/* Exceptions
 */

DECLARE_KEY(kFTPKitParserFallback);

/*
 * Data is an id and error is NSError returned from operations
 */

DECLARE_KEY(kFTPKitOperationResult);
DECLARE_KEY(kFTPKitOperationContextInfo);
DECLARE_KEY(kFTPKitOperationError);

/*
 * Used as an NSError userInfo dictionary key with an NSString value for a server's response message.
 */

DECLARE_KEY(kFTPKitErrorKeyServerMessage);


#undef DECLARE_VALUE
#undef DECLARE_KEY


/* FTPKit Error Codes
 * These codes are used to define particular error states on callbacks.
 * 0 - 100 are used by the virtual file managers.
 * Note: When adding errors, make sure to add the conversion to the
 * abstraction connection subclasses' kitErrorForCode: class method.
 */

typedef NS_ENUM(NSInteger, FTPKitErrorCode) {
	kFTPKitErrorNoError = 0,
	kFTPKitErrorCancelled = 1,
	kFTPKitErrorGeneric = 2,
	kFTPKitErrorUnknown = 3,
	kFTPKitErrorDisconnectBadAuth = 4,
	kFTPKitErrorDisconnectServerReset = 5,
	kFTPKitErrorConnectionRefused = 6,
	kFTPKitErrorCouldNotChangeDirectory = 7,
	kFTPKitErrorCouldNotListDirectory = 8,
	kFTPKitErrorPasswordRequired = 9,
	kFTPKitErrorFileAlreadyExists = 11,
	kFTPKitErrorCouldNotDelete = 12,
	kFTPKitErrorCouldNotCreate = 13,
	kFTPKitErrorFileNotFound = 14,
	kFTPKitErrorCouldNotAcquireConnection = 15,		/* error when the connection acquisition times out */
	kFTPKitErrorFXPFailure = 16,					/* error when specific FXP commands fail */
	kFTPKitErrorServerCommandNotSupported = 17,		/* error when not trying commands for specific servers */
	kFTPKitErrorPermissionDenied = 18,
	kFTPKitErrorConnectionError = 19,				/* generic error case for any sort of connection problems */
	kFTPKitErrorReadFailed = 20,
	kFTPKitErrorWriteFailed = 21,
	kFTPKitErrorHelperProcessFailed = 22,
	kFTPKitErrorMalformedResponse = 23,
	kFTPKitErrorSymlinkEncountered = 24,
	kFTPKitErrorAtomicSizeMismatch = 25,			/* error when the uploaded file isn't the same size as the source file */
	kFTPKitErrorCouldNotParseLine = 26,
	kFTPKitErrorCouldNotDetermineTimeOffset = 27,
	kFTPKitErrorCertificateVerificationFailed = 28,
	kFTPKitErrorCouldNotChangeAttributes = 29,		/* error when connection can't set all requested attributes */
	kFTPKitErrorNetworkOffline = 30,				/* Used on iOS in airplane mode, or otherwise when no connection is available. */
	kFTPKitErrorRateLimited = 31,					/* error when the connection is rate-limiting requests from the client */
	kFTPKitErrorRegionError = 32,					/* Couldn't get the region, or the region specified doesn't match what's expected */
	kFTPKitErrorInvalidValue = 33,					/* Used by PCProtocolExtensions to specify invalid settings */
	kFTPKitErrorCouldNotParseIdentity = 34,			/* Used by connections using libssh2 to perform key-based authentication */
	kFTPKitErrorStorageQuotaExceeded = 35,			/* If the user's storage quota has been exceeded */
	kFTPKitErrorUnsupportedProtocol = 36,			/* If the version of FTPKit doesn't support a communication protocol */
	kFTPKitErrorReauthorizationRequired = 37,		/* This could be necessary for OAuth reauthorization if Transmit was deauthorized or for non-oauth connections like b2, ftp, etc where no password was provided */
	kFTPKitErrorInvalidDestinationDirectory = 38	/* The target folder does not satisfy requirements for the operation destination EG: destination is parent of source */
};


/* NSConditionLock constants
*/

#define	kConditionIdle  0
#define kConditionBusy  1
#define kConditionDone  2

/* FTPKitConflictModes
 * These defines use the lower 8 bits of a UInt16 to represent the resume
 * mode for files.  The upper 8 bits are used to represent the resume mode for
 * folders.
 */

typedef NS_ENUM(uint16_t, FTPKitConflictMode) {
	kFTPKitConflictModeFileMask =				UINT16_C(0x00FF),
	kFTPKitConflictModeFileAsk =				UINT16_C(0x0001),
	kFTPKitConflictModeFileSkip =				UINT16_C(0x0002),
	kFTPKitConflictModeFileResume =				UINT16_C(0x0004),
	kFTPKitConflictModeFileOverwrite =			UINT16_C(0x0008),
	kFTPKitConflictModeFileBoth =				UINT16_C(0x0010),
	kFTPKitConflictModeFileCancel =				UINT16_C(0x0020),
	
	kFTPKitConflictModeFileDoForRemaining =		UINT16_C(0x0080), // 'OR' this value with an existing conflict type to get "apply to all" behavior
	
	kFTPKitConflictModeFolderMask =				UINT16_C(0xFF00),
	kFTPKitConflictModeFolderAsk =				UINT16_C(0x0100),
	kFTPKitConflictModeFolderSkip =				UINT16_C(0x0200),
	kFTPKitConflictModeFolderMerge =			UINT16_C(0x0400),
	kFTPKitConflictModeFolderOverwrite =		UINT16_C(0x0800),
	kFTPKitConflictModeFolderBoth =				UINT16_C(0x1000),
	kFTPKitConflictModeFolderCancel =			UINT16_C(0x2000),
	
	kFTPKitConflictModeFolderDoForRemaining =	UINT16_C(0x8000),  // 'OR' this value with an existing conflict type to get "apply to all" behavior
	
	kFTPKitConflictModeNone =					UINT16_C(0x0000)
};

// The following macros are provided for convenience.  Feel free to bit
// twiddle FTPKitConflictMode's yourself.

// FTPKitConflictModeSetFolderMode(m, f)
// Sets the given folder mode on m (clears existing folder mode).
// m: A valid FTPKitConflictMode variable
// f: A folder conflict mode to set on m.
#define FTPKitConflictModeSetFolderMode(m, f) (m = (m & ~kFTPKitConflictModeFolderMask) | (f & kFTPKitConflictModeFolderMask))

// FTPKitConflictModeSetFileMode(m, f)
// Sets the given file mode on m (clears existing file mode).
// m: A valid FTPKitConflictMode variable
// f: A file conflict mode to set on m.
#define FTPKitConflictModeSetFileMode(m, f) (m = (m & ~kFTPKitConflictModeFileMask) | (f & kFTPKitConflictModeFileMask))

// FTPKitConflictModeIsSet(m, f)
// Returns true if the given mode is set on m.
// m: A valid FTPKitConflictMode variable
// f: A resume mode to check on m
#define FTPKitConflictModeIsSet(m, f) ((m & f) != 0)


// kFTPKitEncodingAutomatic indicates that the native connection encoding should be used or a reasonable default if none exists
#define kFTPKitEncodingAutomatic kCFStringEncodingInvalidId

// Default timeout when acquiring connections for use in operations
#define kFTPKitAcquireConnectionTimeout 600

// FTPKit creator code
#define kFTPKitCreatorCode 'FTPk'
