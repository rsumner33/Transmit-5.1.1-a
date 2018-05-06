#import "PCFolderNode.h"
#import "PCRemoteFileNode.h"
#import "FTPKitConstants.h"
#import <pthread.h>

@class PCCredentials;

@interface PCRemoteFolderNode : PCRemoteFileNode <PCNodeContainerCreating, PCFolderNode, PCOperationPathProvider>
{
	PCFolderNodeContents* iContents;
}

@property (assign) Class containerClass; // The container class to vend

@property (nonatomic, getter=isExpired) BOOL expired;
@property (nonatomic, readonly) BOOL isPackage;

+ (id)folderNodeWithPath:(NSString*)path credentials:(PCCredentials*)inCredentials;

// accessors

- (PCRemoteFileNode*)nodeWithFilename:(NSString*)name; // Munged into ISO-Latin1
- (PCRemoteFileNode*)nodeWithUnicodeFilename:(NSString*)name; // local file system encoding, UTF-8
- (PCRemoteFileNode*)nodeWithFilename:(NSString*)name createWithType:(PCFileSystemType)type credentials:(PCCredentials*)aCredentials; // Munged into ISO-Latin1

- (PCRemoteFileNode*)nodeWithFilename:(NSString*)name useContentsLock:(BOOL)flag; // Only call this method if you have already obtained the contents lock manually.

// redeclared from PCFolderNode protocol for proper argument type specialization and checking

- (void)addNode:(PCRemoteFileNode*)node;
- (void)childNodeWasRenamed:(PCRemoteFileNode*)node oldName:(NSString*)oldName;
- (void)removeNode:(PCRemoteFileNode*)node;

// observing
- (void)addContentObserver:(NSObject<PCFolderContentObserver> *)object;
- (void)removeContentObserver:(NSObject<PCFolderContentObserver> *)object;
- (void)flushBufferedChanges;

// misc

- (void)noteContentAttributesChanged;
- (NSSet*)contentsSet; // observable

@end
