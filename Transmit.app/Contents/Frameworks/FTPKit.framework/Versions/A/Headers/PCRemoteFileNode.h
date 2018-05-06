#import "PCFileNode.h"

@class BucketLoggingStatus;
@class PCCredentials;
@class PCFileNode;

@interface PCRemoteFileNode : PCNode 
{
	PCCredentials* iCredentials;
}

@property(retain) PCCredentials* credentials;

#if ! TARGET_OS_IPHONE
+ (NSImage*)iconWithKey:(NSString*)inKey withSize:(PCFileSystemIconSize)iconSize;
#endif

+ (id)fileNodeWithPath:(NSString*)inPath credentials:(PCCredentials*)inCredentials;


- (id)initWithPath:(NSString*)inPath credentials:(PCCredentials*)inCredentials;

- (NSString*)urlStringWithPassword:(BOOL)flag;

@property(retain, nonatomic) PCFileNode* cachedNode;

@end
