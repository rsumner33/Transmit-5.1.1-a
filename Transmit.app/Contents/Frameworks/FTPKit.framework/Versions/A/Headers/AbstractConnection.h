#import "FTPKitConstants.h"
//#import "PCCredentials.h"
#import <PanicCore/PCTranscript.h>
#import <netdb.h>

@class PCNode;
@class PCRemoteFileNode;
@class PCRemoteFolderNode;
@class PCVirtualFileManager;
@class PCConnectionThrottle;
@class PCConnectionPool;
@class PCTrust;
@class PCUUID;
@class PCProtocolExtension;
@class PCConnectionConfiguration;
@class PCCredentials;
@class AbstractTransferItem;

@protocol ConnectionTranscriptDelegate;

@interface AbstractConnection : NSObject <TranscriptConnection>
{
	PCCredentials*		iCredentials;
	id<ConnectionTranscriptDelegate> iTranscriptDelegate;
	
@private
	__unsafe_unretained id			iDelegate;
	PCUUID*				iUUID;
	
	BOOL				iSecure;
	PCTrust*			iTrust;
	
	PCConnectionThrottle* iConnectionThrottle;
	__unsafe_unretained PCConnectionPool*	iConnectionPool;

	BOOL iDelegateMonitorsProgress; // conforms to AbstractConnectionProgressMonitoring
}

@property (retain) id transcriptDelegate;
@property (nonatomic, readonly, retain) PCCredentials* credentials;
@property (nonatomic, readonly, copy) NSString* loginPath;
@property (nonatomic, assign) id delegate;
@property (nonatomic, assign) BOOL shouldCancel;
@property (nonatomic, readonly, retain) PCUUID* UUID;
@property (readonly, retain) PCTrust* trust;
@property (retain) PCConnectionThrottle* connectionThrottle;
@property (assign) PCConnectionPool *connectionPool;
@property (nonatomic, assign) BOOL connectedOnce;
@property (assign,getter=isRateLimited) BOOL rateLimited; // private use, connection pool
@property (copy) NSString *remotePath;

@property (retain, nonatomic) AbstractTransferItem *transferItem;

@property(readonly, assign) NSInteger connectionAttemptFailureCount;
@property (readonly, getter=isSecure) BOOL secure; // initialized according to protocol but may change later

/* AbstractConnection is an abstract class: do not call initWithCredentials on AbstractConnection,
   use this constructor instead: */

+ (AbstractConnection*)connectionWithCredentials:(PCCredentials*)credentials;

// Default is NSISOLatin1StringEncoding
+ (NSStringEncoding)defaultDisplayEncoding;
+ (NSStringEncoding)defaultRemoteEncoding;

// Class methods for initalizing/destroying class objects
+ (void)initializeClassWithCredentials:(PCCredentials*)credentials;
+ (void)destroyClassWithCredentials:(PCCredentials*)credentials;

// Converts a standard HTTP status code into a localized description
+ (NSString *)localizedStringForHTTPStatusCode:(NSInteger)statusCode;

// Connection pool timeout interval for the connection
- (NSTimeInterval)idleConnectionTimeoutInterval;

// The following methods must be implemented by concrete subclasses:

- (BOOL)connect:(NSError**)error;
- (void)disconnect NS_REQUIRES_SUPER;

// Directories
- (PCRemoteFolderNode*)createFolderWithName:(NSString*)filename attributes:(NSDictionary<NSString *, id> *)attributes in:(PCRemoteFolderNode*)parentNode error:(NSError * __autoreleasing *)error;
- (BOOL)changeDir:(NSString*)path attributes:(NSDictionary<NSString *, id> * __autoreleasing *)outAttributes error:(NSError**)error;
- (BOOL)contentsOfNode:(PCRemoteFolderNode*)folderNode nodes:(NSArray**)newNodes error:(NSError**)error;
- (NSString*)pwd:(NSError**)error;

// Nodes
- (BOOL)changeAttributes:(NSDictionary*)attributes onNode:(PCRemoteFileNode*)node error:(NSError**)error;
- (BOOL)deleteNode:(PCRemoteFileNode*)node error:(NSError**)error;
- (BOOL)download:(PCRemoteFileNode*)node toFileHandle:(NSFileHandle*)fileHandle byteOffset:(unsigned long long)byteOffset bytesTransferred:(unsigned long long*)outBytesTransferred error:(NSError**)outError;
- (BOOL)moveNode:(PCRemoteFileNode*)node to:(PCRemoteFolderNode*)newParentNode name:(NSString*)filename error:(NSError**)outError;
- (BOOL)uploadFileHandle:(NSFileHandle*)fileHandle fromPath:(NSString*)fromPath to:(PCRemoteFolderNode*)newParentNode name:(NSString*)filename withAttributes:(NSDictionary*)attributes byteOffset:(unsigned long long)byteOffset bytesTransferred:(unsigned long long*)outBytesTransferred extendedAttributes:(NSDictionary**)outAttributes error:(NSError* __autoreleasing  *)outError;
- (PCRemoteFileNode*)remoteCopyNode:(PCRemoteFileNode*)node to:(PCRemoteFolderNode*)newParentNode name:(NSString*)filename error:(NSError**)outError;
- (BOOL)streamBytesWithFilename:(NSString*)filename toPath:(NSString*)toPath handler:(id)handler error:(NSError**)outError;

// Symlinks
- (BOOL)createSymbolicLinkAtPath:(NSString*)path resolvingToPath:(NSString*)toPath error:(NSError**)outError;
- (BOOL)resolvePath:(NSString*)path resolvedPath:(NSString**)outPath isDirectory:(BOOL*)isDirectory error:(NSError**)outError;

// Connection Attributes
- (BOOL)sendKeepAlive:(NSError**)error;

// End of required methods


// The following methods are optional for subclasses:

- (id)initWithCredentials:(PCCredentials*)credentials;
- (NSString*)sendRawCommand:(NSString*)command error:(NSError**)outError;
- (NSDictionary*)attributesOfNode:(PCRemoteFileNode*)node error:(NSError**)error;
- (BOOL)extendedAttributesOfLoginNode:(PCRemoteFolderNode*)loginNode;
- (NSDictionary*)fileSystemAttributesAtPath:(NSString*)path error:(NSError**)outError;
+ (NSArray*)protocolExtensions;
+ (NSArray*)protocolExtensionsUsingFileManager:(PCVirtualFileManager *)fileManager;
+ (NSArray*)permissionExtensions;
+ (NSArray*)permissionExtensionsUsingFileManager:(PCVirtualFileManager *)fileManager;
+ (void)hydrateConnectionConfiguration:(PCConnectionConfiguration *)configuration;

- (NSURL*)generatePublicURLForNode:(PCRemoteFileNode*)node siteURL:(NSString*)siteURL basePath:(NSString*)basePath makeSecure:(BOOL)secure includeLogin:(BOOL)includeLogin error:(NSError**)outError;

// End optional methods

// convenience methods that don't require a file descriptor
- (BOOL)download:(PCRemoteFileNode*)node toPath:(NSString*)toPath byteOffset:(unsigned long long)byteOffset bytesTransferred:(unsigned long long*)outBytesTransferred error:(NSError**)error;
- (BOOL)uploadFileAtPath:(NSString*)fromPath to:(PCRemoteFolderNode*)parentNode filename:(NSString*)filename attributes:(NSDictionary*)attributes byteOffset:(unsigned long long)byteOffset bytesTransferred:(unsigned long long*)outBytesTransferred extendedAttributes:(NSDictionary**)outAttributes error:(NSError**)error;

// the dateWith… methods allow a connection to adjust (or even ignore) the supplied date as is appropriate for the capabilities of the server
- (NSDate*)dateWithDate:(NSDate*)date;
- (NSDate*)dateWithModificationDateForNode:(PCNode*)node supported:(BOOL*)supported;

- (NSString*)address;
- (NSString*)password;
- (unsigned int)port;
- (FTPKitProtocol)protocol;
- (int)createAddrWithAddress:(const char*)address port:(int)port family:(int)family info:(struct addrinfo**)outAddrInfo IPAddress:(NSString**)outAddress;

- (void)flushTranscript;

- (BOOL)setError:(NSError**)error title:(NSString*)title code:(NSInteger)code;
- (BOOL)setError:(NSError**)error title:(NSString*)title message:(NSString*)message code:(NSInteger)code;
- (BOOL)setError:(NSError**)error title:(NSString*)title message:(NSString*)message code:(NSInteger)code userInfo:(NSDictionary*)userInfo;
- (BOOL)setError:(NSError**)error title:(NSString*)title message:(NSString*)message kitError:(FTPKitErrorCode)kitError;
- (BOOL)setError:(NSError**)error title:(NSString*)title message:(NSString*)message kitError:(FTPKitErrorCode)kitError underlyingError:(NSError*)underlyingError;
- (BOOL)setError:(NSError**)error title:(NSString*)title message:(NSString*)message kitError:(FTPKitErrorCode)kitError userInfo:(NSDictionary*)userInfo;

- (NSString*)username;
- (void)appendTranscript:(NSString*)text outgoingText:(BOOL)flag;
- (void)appendTranscript:(NSString*)message outgoingText:(BOOL)isOutgoing onNewLine:(BOOL)newLine;

- (NSString*)displayStringForRemoteString:(NSString*)string;
- (NSString*)remoteStringForDisplayString:(NSString*)string;

- (PCConnectionConfiguration*)configuration;

// Errors

void EscapePool(NSError** error);
void EnterPool(NSError** error);


@end


extern NSStringEncoding FTPKitDefaultStringEncodingForProtocol(FTPKitProtocol protocol);



@interface PCThrottleInfo : NSObject

@property double currentKBytes;
@property double maxKBytes;
@property NSTimeInterval lastSleepInterval;
@property BOOL isUpload;

- (void)reset;

@end


@interface PCConnectionThrottle : NSObject

@property (retain) PCThrottleInfo *downloadInfo;
@property (retain) PCThrottleInfo *uploadInfo;

- (void)reset;

@end


@interface NSString (PCLossyCString)

- (const char*)pc_lossyCStringUsingEncoding:(NSStringEncoding)encoding;

@end


@interface AbstractTransferItem : NSObject

- (instancetype)initWithNode:(PCNode*)node;
- (instancetype)initWithFileHandle:(NSFileHandle*)handle;

@property (assign, nonatomic) CFTimeInterval lastProgressUpdateInterval;
@property (assign, nonatomic) CFTimeInterval startTransferInterval;
@property (assign, nonatomic) CFTimeInterval lastStallInterval;

@property (assign, nonatomic) size_t fileSize;
@property (assign, nonatomic) size_t totalBytesTransferred;

@end
