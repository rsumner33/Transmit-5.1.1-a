#import <PanicCore/PanicCore.h>

#import <FTPKit/PCFSEventManager.h>

@interface FTPKitFSEventManager : PCFSEventManager
{
	
}

- (BOOL)addWatchFolder:(NSString*)path;
- (void)removeWatchFolder:(NSString*)path;

@end
