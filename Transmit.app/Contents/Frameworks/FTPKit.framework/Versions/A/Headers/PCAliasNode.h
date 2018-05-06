#import <Foundation/Foundation.h>
#import "PCFileNode.h"
#import "FTPKitConstants.h"

@class PCFolderNode;


@interface PCAliasNode : PCFileNode
{
	NSString*	iTargetPath;
	BOOL		iTargetIsFolder;
	BOOL		iSymlink;
	PCNode*		iAliasNode;
}

@property (nonatomic, readonly, copy) NSString *targetPath;
@property (nonatomic, readonly, getter=isSymlink) BOOL symlink;
@property (nonatomic, readonly, retain) PCNode *aliasNode;

- (PCNode *)aliasNodeResolveIfNeeded:(BOOL)flag;
- (BOOL)isFolder;

@end
