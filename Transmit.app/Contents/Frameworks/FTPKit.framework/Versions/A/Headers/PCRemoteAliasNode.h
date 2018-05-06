#import "PCRemoteFileNode.h"
#import <pthread.h>

@interface PCRemoteAliasNode : PCRemoteFileNode
{
	NSString*			iTargetPath;
	NSString*			iResolvedPath;
	BOOL				iFolder;
	PCRemoteFileNode*	iAliasNode;
	pthread_rwlock_t	iAliasLock;
}

@property(copy) NSString* targetPath;
@property(copy) NSString* resolvedPath;
@property(readonly, getter=isFolder) BOOL folder;
@property(readonly, getter=isSymlink) BOOL symlink;
@property(retain) PCRemoteFileNode* aliasNode;

- (id)initWithPath:(NSString*)inPath targetPath:(NSString*)inTargetPath credentials:(PCCredentials*)inCredentials;

- (PCNode*)aliasNodeResolveIfNeeded:(BOOL)flag;

@end
