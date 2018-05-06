#import "FTPKitConstants.h"
#import "FTPKitProtocols.h"

#import <PanicSSHKit/PanicSSHKit.h>


@class FilePermissions, PCRemoteFileNode;

@interface PCCredentials : NSObject <NSCopying, NSSecureCoding, PCCredentialsProvider>

- (instancetype)initWithURL:(NSURL*)aURL;
- (instancetype)initWithUUID:(NSString*)UUID;

@property (copy) NSString *UUID;

@property (nonatomic, copy) NSString *address;

@property (nonatomic, assign) uint16_t port;
- (uint16_t)portUsingDefaultPort;

@property (nonatomic, assign) FTPKitProtocol protocol;
@property FTPKitServerType serverType;

@property (nonatomic, copy) NSString *username;
@property (nonatomic, copy) NSString *password;
- (void)setPassword:(NSString *)password saveInKeychain:(BOOL)flag;

@property (copy) NSString *initialPath; // unicode string, not remotely enocoded because of dynamic encoding changes at login
@property (nonatomic, assign) NSStringEncoding encoding; // setter calls through to encodingUsingConnectionDefault: using YES for useConnectionEncoding
@property (nonatomic, assign) BOOL usePassiveMode;

@property (nonatomic, copy) NSString *OAuthCode;
@property (nonatomic, copy) NSString *OAuthAccessToken;
@property (nonatomic, copy) NSString *OAuthEndpoint;
@property (nonatomic, copy) NSDate *expiryDate;

@property (nonatomic, copy) NSString *mostRecent2FACode; // attempt to use last code again for the next connection, otherwise user gets prompted many times in a single operation
@property (nonatomic, copy) NSString *authenticatedKeyPassphrase; // key passphrase that successfully unlocked the ssh key, not saved
@property (nonatomic, copy) NSString *mostRecentPK11Code; // attempt to use last code again for the next connection, otherwise user gets prompted many times in a single operation

@property (copy) NSString* proxyAddress;
@property (copy) NSString* proxyPassword;
@property uint16_t proxyPort;
@property (copy) NSString* proxyUsername;
@property int proxyType;

@property (copy) NSString* proxySFTPPassword;

@property NSUInteger maximumConnections;
@property NSUInteger maximumTransferConnections;
@property BOOL preserveModificationDates;

@property FTPUNIXParserNameDateSpacing nameDateSpacing;

@property int redialDelay;
@property int maxDials;
@property int timeout;

@property BOOL useFEAT;
@property BOOL useMLST;
@property BOOL useCCC;
@property BOOL usePRET;
@property BOOL useTLSv12;
@property BOOL useVerboseLogging;

@property FTPKitCompositionType characterCompositionType;

@property BOOL shouldTransferDSStore;

@property BOOL shouldKeepConnectionsAlive;
@property NSTimeInterval keepConnectionsAliveDelay;
@property BOOL shouldKeepTransfersAlive;
@property NSTimeInterval keepTransfersAliveDelay;

@property (nonatomic, copy) NSArray *asciiFiles;

@property (copy) NSDictionary *customUploadPermissions;
@property (copy) NSArray *customS3UploadHeaders;

@property (assign) BOOL usesTempauthAuthentication; // Used in some Swift connections

// Set when settings change that require a reconnect but the connection is active so the connection cannot be terminated right away
@property BOOL needsToExpire;

// flag to indicate if the advanced settings have been applied
@property BOOL configured;

@property (readonly) NSString *key;

// The amount of time a remote folder listing is valid, default is 5 minutes
@property (atomic, assign) NSTimeInterval contentExpirationInterval;


- (FilePermissions *)customPermissionsForNode:(PCRemoteFileNode *)node;

// kFTPKitEncodingAutomatic if connection should use its default encoding determined by the connection type
- (NSStringEncoding)encodingUsingConnectionDefault:(BOOL)useConnectionEncoding;

@property (retain) NSObject <PCKeyItem> *representedKeyObject; // A private key wrapper containing the data, passphrase, and an optional path and nickname

- (NSData*)identity; // Legacy method to support key auth in transmit disk

@end


@interface PCCredentials (PCCredentialsConveniences)

// Returns YES if `protocol` is conformant or compatible with `otherProtocol`, such as the various flavors of FTP.
// This is useful for determining which features or user interface should be exposed that is specific to
// a certain protocol, without having to explicitly specify each protocol.
+ (BOOL)isProtocol:(FTPKitProtocol)protocol compatibleWithProtocol:(FTPKitProtocol)otherProtocol;
- (BOOL)isProtocolCompatibleWithProtocol:(FTPKitProtocol)otherProtocol;
- (BOOL)isCloudProtocol;

- (NSString*)unicodeStringForRemoteString:(NSString*)string;
- (NSString*)remoteStringForUnicodeString:(NSString*)string;

- (void)sanitizeCredentials; // reformats the credential objects if required by the protocol

BOOL IsSOCKSProxyType(unsigned int proxyType);

@end

