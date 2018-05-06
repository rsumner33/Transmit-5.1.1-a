#import "AbstractConnection.h"

@class PCRemoteFileManager;
@class PCCredentials;
@class PCWorkerThread;
@class PCUUID;

extern const int kPCConnectionPoolMaxConnectionLimit;

@interface PCConnectionPool : NSObject
{
	id <ConnectionTranscriptDelegate> iTranscriptDelegate;
    
@private
	PCCredentials*			iCredentials;
	
	NSMutableArray*			iIdleConnections;
	NSMutableSet*			iActiveConnections;
	PCWorkerThread*			iWorkerThread;
	NSMutableDictionary*	iTimeouts;
	NSMutableDictionary*	iKeepAliveTimers;
	
	NSUInteger				iMaxConnections;
	NSMutableArray*			iWaitingConnectionQueue; // dictionaries waiting for connections
	
	double					iMaxDownloadKBytesPerSecond;
	double					iMaxUploadKBytesPerSecond;
}

@property(retain) id <ConnectionTranscriptDelegate> transcriptDelegate;
@property(readonly, retain) PCCredentials* credentials;
@property NSUInteger maximumConnections;
@property NSUInteger maximumTransferConnections; // 0 is kPCConnectionPoolMaxConnectionLimit

// throughput per pool or zero for unlimited
+ (double)defaultMaximumDownloadThroughput;
+ (void)setDefaultMaximumDownloadThroughput:(double)kilobytesPerSecond;
+ (double)defaultMaximumUploadThroughput;
+ (void)setDefaultMaximumUploadThroughput:(double)kilobytesPerSecond;

/* To use this API, request a connection via -acquireConnection.
 * If a connection does not exist, one will be created.
 * After acquisition, the caller has exclusive rights to this connection until the
 * caller makes a releaseConnection: call to return this connection to the pool.
 * Acquisition will block until a connection becomes available so it's highly
 * recommended to only call these methods on a secondary thread.
 */

@property double maximumDownloadKBytesPerSecond; // zero for unlimited
@property double maximumUploadKBytesPerSecond; // zero for unlimited

- (AbstractConnection*)acquireConnection;
- (AbstractConnection*)acquireConnectionWithCancellation:(NSInvocation**)outCancellation /*can be NULL*/;
- (AbstractConnection*)acquireConnectionBeforeDate:(NSDate*)timeoutDate cancellation:(NSInvocation**)outCancellation rateLimit:(BOOL)transfer;
- (AbstractConnection*)acquireConnectionWithTimeout:(NSTimeInterval)timeout cancellation:(NSInvocation**)outCancellation rateLimit:(BOOL)transfer;

- (void)releaseConnection:(AbstractConnection*)connection;
- (void)expireIdleConnections;
- (void)expireIdleConnectionsAtPath:(NSString*)path;
//- (void)removeInterfaceDelegate:(id)delegate;

// throttling
- (void)updateThrottleWithIdlingConnection:(AbstractConnection*)connection;
- (NSTimeInterval)delayIntervalForConnection:(AbstractConnection*)connection bytesTransferred:(long long)bytesTransferred elapsed:(NSTimeInterval)elapsed isUpload:(BOOL)isUpload;
- (NSSet*)activeConnections;

- (id)initWithCredentials:(PCCredentials*)credentials;
- (void)teardown;

@end
