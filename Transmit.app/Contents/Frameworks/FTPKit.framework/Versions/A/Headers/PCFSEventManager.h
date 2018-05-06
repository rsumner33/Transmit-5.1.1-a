#import <Cocoa/Cocoa.h>

@interface PCFSEventManager : NSObject
{
	BOOL iEventStreamNeedsUpdate;	
	NSMutableDictionary* iWatchPaths; //key is path, object is counted set of delegates
	NSCountedSet* iSuppressedPaths;
	NSCountedSet* iManualWatchPaths;	
	FSEventStreamRef iEventStream;
}

@property (readonly) NSCountedSet *manualWatchPaths;

+ (id)defaultManager;

- (void)acceptNotificationsForPath:(NSString*)path;
- (void)acceptNotificationsForPath:(NSString*)path afterDelay:(NSTimeInterval)delay;
- (void)acceptNotificationsForPath:(NSString*)path afterDelay:(NSTimeInterval)delay reloadFolder:(BOOL)flag;
- (void)suppressNotificationsForPath:(NSString*)path;

- (BOOL)isPathUpdateAutomatic:(NSString*)path;
- (BOOL)isPathUpdateManual:(NSString*)path;
- (BOOL)isPathWatched:(NSString*)path;

- (BOOL)addPath:(NSString*)path delegate:(id)delegate;
- (void)removePath:(NSString*)path delegate:(id)delegate;

@end

@interface NSObject (PCFSEventManagerCallback)

- (void)fileSystemEventManager:(PCFSEventManager*)manager folderDidChange:(NSString*)path flags:(FSEventStreamEventFlags)flags;

@end
