#import "PCFolderNode.h"

typedef struct
{
	u_int32_t size;
	attrreference_t ref;
	char path[MAXPATHLEN + 1];
}
PCMountPointPath;

@interface PCVolumeNode : PCFolderNode
{
	BOOL	iRemovable;
	BOOL	iIsSymlink;
	BOOL	iIsBootDisk;
}

@property(nonatomic, getter=isRemovable) BOOL removable;

@end


// Created for the /Volumes node
@interface PCRootVolumeNode : PCFolderNode
{

}

@end
