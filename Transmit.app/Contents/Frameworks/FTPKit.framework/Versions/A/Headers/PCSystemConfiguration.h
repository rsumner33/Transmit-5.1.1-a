#import <Foundation/Foundation.h>
#import <PanicCore/PanicCore.h>
#import <SystemConfiguration/SystemConfiguration.h>

extern NSString* const kPCProxyKeyType; // NSNumber (PCProxyType)
extern NSString* const kPCProxyKeyHost; // NSString
extern NSString* const kPCProxyKeyPortNumber; // NSNumber (unsigned)
extern NSString* const kPCProxyKeyUsername; // NSString
extern NSString* const kPCProxyKeyPassword; // NSString

// CF has an explicit "none" type but we do not: any such system proxies are simply not returned
typedef enum {
	kPCProxyTypeHTTP = 0,
	kPCProxyTypeHTTPS = 1,
	kPCProxyTypeFTP = 2,
	kPCProxyTypeSOCKS = 3
} PCProxyType;


@interface PCSystemConfiguration : PCSharedInstance
{
@private

#if !TARGET_OS_IPHONE
	/*__strong*/ SCDynamicStoreRef iDynamicStore;
	/*__strong*/ CFRunLoopSourceRef iRunLoopSource;

#endif
	BOOL iAppliedCFProxyWorkaround;
	NSDictionary* iProxies;	
}

@property(readonly, retain) NSDictionary* proxies; // as returned by SCDynamicStoreCopyProxies()

// returns an array of dictionaries with kPCProxyKey* keys
- (NSArray*)proxyServersForURL:(NSURL*)URL;
- (NSArray*)proxyServersForURL:(NSURL*)URL withProxies:(NSDictionary*)proxies; // for testing

- (BOOL)isHostInProxyServerExceptionList:(NSString*)host;

- (NSString*)computerName;
- (NSString*)localHostName;

@end

#if !TARGET_OS_IPHONE

@interface PCSystemConfigurationNotifier : NSObject
{
	SCDynamicStoreRef iDynamicStore;
	CFRunLoopSourceRef iRunLoopSource;
	id iDelegate;
}

+ (PCSystemConfigurationNotifier*)systemConfigurationIPAddressNotifierWithDelegate:(id)delegate;

- (id)initWithKeys:(NSArray*)notifyKeys patterns:(NSArray*)notifyPatterns delegate:(id)delegate;

@property (nonatomic, assign) id delegate;

@end

@interface NSObject (PCSystemConfigurationNotifierDelegate)
- (void)systemConfiguration:(PCSystemConfigurationNotifier*)notifier keysDidChange:(NSArray*)observedKeys;
@end

#endif
