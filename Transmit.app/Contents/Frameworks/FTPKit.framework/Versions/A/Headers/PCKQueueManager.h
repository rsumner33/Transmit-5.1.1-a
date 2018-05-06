#import <Foundation/Foundation.h>

@class UKKQueue;

@interface PCKQueueManager : NSObject
{
	NSMutableDictionary* iQueuedCachePaths;
	NSMutableDictionary* iQueuedPaths;
	NSMutableDictionary* iSuppressedPaths;
	UKKQueue* iKQueue;
	NSMutableArray* iInheritedItems;
	NSMutableDictionary* iQueuedTimers;
	NSMutableDictionary* iQueuedTimerDeferCount;
	NSMutableSet* iManualQueuedPaths;
}

+ (id)defaultManager;

- (BOOL)addLocalFolderPathForCacheNotification:(NSString*)path;
- (void)removeLocalFolderPathForCacheNotification:(NSString*)path;

- (void)acceptCacheNotificationsForLocalPath:(NSString*)path;
- (void)acceptCacheNotificationsForLocalPath:(NSString*)path afterDelay:(NSTimeInterval)delay;
- (void)acceptCacheNotificationsForLocalPath:(NSString*)path afterDelay:(NSTimeInterval)delay reloadFolder:(BOOL)flag;
- (void)suppressCacheNotificationsForLocalPath:(NSString*)path;

- (BOOL)isPathUpdateAutomatic:(NSString*)path;
- (BOOL)isPathUpdateManual:(NSString*)path;
- (BOOL)isPathWatched:(NSString*)path;

- (BOOL)addPath:(NSString*)path notifyingAbout:(u_int)fflags delegate:(id)delegate;
- (void)removePath:(NSString*)path withDelegate:(id)delegate;

@end

@interface NSObject (PCKQueueManagerCallback)

- (void)KQueueManager:(PCKQueueManager*)manager receivedNotification:(NSString*)nm forFile:(NSString*)fpath;

@end
