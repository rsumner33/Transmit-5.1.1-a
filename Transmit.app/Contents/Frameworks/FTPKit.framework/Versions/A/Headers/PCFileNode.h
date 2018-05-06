#import "PCNode.h"
#import "FTPKitConstants.h"

#include <sys/attr.h>
//#include <sys/vnode.h>
#include <sys/mount.h>

#define countof(x) (sizeof(x) / sizeof(0[x]))

extern NSArray *gFileAttributeKeys;
extern NSArray *gAllAttributeKeys;

typedef struct  
{
	u_int32_t size;
	uid_t uid;
	gid_t gid;
	u_int32_t mode;
}
PCPermissionAttributes;

typedef struct
{
	u_int32_t size;
	struct timespec created;
	struct timespec modified;
	off_t logicalSize;
	off_t physicalSize;
	
}
PCIOSAttributes;

typedef struct  
{
	u_int32_t size;
	attrreference_t ref;
	char name[766]; //Amit says this can be up to 766 instead of NAME_MAX + 1
}
PCCanonicalName;

typedef struct  
{
	u_int32_t size;
	struct timespec ref;
}
PCModificationDate;


@class PCFolderNode;

@interface PCFileNode : PCNode <NSCoding>
{
@private
    NSArray *iTags;
	NSArray *iTagColors;
}

@property (retain, nonatomic) NSURL *fileReferenceURL;
@property (retain, nonatomic) NSArray *tags;

+ (NSString*)canonicalFilenameAtPath:(NSString*)aPath;

// NOTICE - DO NOT USE: you should use the file manager to create new nodes unless you know what you're doing

// This method will check file type and return either a PCAliasNode,
// PCFileNode, or a PCSmartFolder node.

+ (id)nodeWithPath:(NSString*)inPath;

- (id)initWithPath:(NSString*)path;
- (id)initWithURL:(NSURL*)url attributes:(NSDictionary*)attrs;
// END NOTICE

//NOTE: not canonical, don't use for path comparing or node creation
- (NSString*)fileReferencePath;

@end

@interface PCFileNode (Private)

- (void)loadFileAttributes;
- (void)setFileAttributes:(NSDictionary*)attrs forPath:(NSString*)path;

@end
