#import <Foundation/Foundation.h>


@interface NSNotificationCenter (PCThreadedNotifications)

// generic methods, allow posting on an arbitrary thread
- (void)pc_postNotification:(NSNotification*)notification onThread:(NSThread*)thread waitUntilDone:(BOOL)waitUntilDone;
- (void)pc_postNotificationName:(NSString*)name onThread:(NSThread*)thread object:(id)object userInfo:(NSDictionary*)userInfo waitUntilDone:(BOOL)waitUntilDone;

// convenience methods for posting on main thread
- (void)pc_postNotificationOnMainThread:(NSNotification*)notification waitUntilDone:(BOOL)waitUntilDone;
- (void)pc_postNotificationNameOnMainThread:(NSString*)name object:(id)object userInfo:(NSDictionary*)userInfo waitUntilDone:(BOOL)waitUntilDone;

@end
