#import "FTPKitConstants.h"
#import <libkern/OSAtomic.h>
#if TARGET_OS_IPHONE
#import <CoreGraphics/CoreGraphics.h>
#else
#import <AppKit/NSColor.h>
#endif


@class FilePermissions;
@class PCUUID;
@class PCVirtualFileManager;
@class PCLocalFileManager;
@class PCRemoteFileManager;

@protocol PCFolderNode;

#if TARGET_OS_IPHONE
@class UIImage;
#endif


@interface PCNode : NSObject <NSCopying>
{
@protected
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    // OSSpinLock is deprecated in macOS 10.12+
	OSSpinLock			iPathLock;
#pragma clang diagnostic pop
	NSString *			iPath;				// Full absolute path to file, including name
	NSString *			iDisplayName;		// Localized name, used for display in interface

@private
	NSUUID *			iUUID;
	NSDate *			iCreationDate;		// When item was created, usually not applicable for remote items
	NSDate*				iModificationDate;	// Date of last modification
	id					iOwner;				// Owner this item belongs to or NSNull if not applicable
	id					iGroup;				// Group the item belongs to or NSNull if not applicable
	NSNumber *			iOwnerAccountID;
	NSNumber *			iGroupAccountID;
	NSString *			iKind;				// Document type
	FilePermissions *	iPermissions;		// Permissions
	NSNumber *			iSize;				// Logical size of file or nil for folders
	NSNumber *			iPhysicalSize;		// Physical size of file or logical size if not applicable
	BOOL				iVisible;

#if TARGET_OS_IPHONE
	BOOL				iIconLoaded;			// If the icon has been loaded or not.
#else
@protected
	NSImage *			iIconImage;
	IconRef				iIconRef;
#endif
    
	__unsafe_unretained PCNode *iParent;
}

@property (readonly) NSUUID *uuid;
@property (copy) NSString *path;
@property (copy) NSString *displayName;
@property (copy) NSDate *creationDate;
@property (copy) NSDate *modificationDate;
@property (copy) id owner;
@property (copy) id group;
@property (copy) NSNumber *groupAccountID;
@property (copy) NSNumber *ownerAccountID;
@property (copy) NSString *kind;
@property (strong) FilePermissions *permissions;
@property (copy) NSNumber *size;
@property (copy) NSNumber *physicalSize;
@property (getter=isVisible) BOOL visible;
//@property (assign) FTPKitConflictMode conflictMode; // XXX replace with configuration conflict mode
@property (unsafe_unretained) PCNode <PCFolderNode> *parent;
@property (readonly) NSDictionary *attributes;
@property (readonly) NSArray *tagColors;

@property (retain) NSMutableDictionary *extendedAttributes;

#if TARGET_OS_IPHONE
@property (assign) BOOL iconLoaded;
#else
@property (nonatomic, strong) NSImage *iconImage;
#endif 

// transformer conveniences
@property (readonly) NSString *prettySize; // "1,234,567" or "--" for folders
@property (readonly) NSString *prettyPhysicalSize;
@property (readonly) NSString *prettyOwner;
@property (readonly) NSString *prettyGroup;

- (id)initWithPath:(NSString*)path;

#if TARGET_OS_IPHONE
- (UIImage *)iconWithSize:(PCFileSystemIconSize)iconSize;
#else
- (IconRef)iconRef;
- (void)setIconRef:(IconRef)iconRef;
- (NSImage *)iconWithSize:(PCFileSystemIconSize)iconSize;
#endif

- (id)extendedAttributeForKey:(NSString *)key;
- (void)setExtendedAttribute:(id)value forKey:(NSString *)key;
- (void)addExtendedAttributes:(NSDictionary<NSString *, id> *)attributes;

+ (NSArray *)sortDescriptorsForSortType:(FTPSortType)sortType ascending:(BOOL)ascending;

// accessors

@property (nonatomic, readonly, getter=isRemote) BOOL remote;

@property (nonatomic, readonly) NSString *displayPath;
@property (nonatomic, readonly) PCFileSystemType type;
- (BOOL)isDescendantOf:(PCNode *)aNode;

@property (nonatomic, readonly) NSArray *ancestors;
@property (nonatomic, readonly) NSArray *ancestorsIncludingNode;

@property (nonatomic, readonly) NSString *filename;
@property (nonatomic, readonly) NSString *unicodeFilename;
@property (nonatomic, readonly) NSString *unicodePath;

@property (nonatomic, readonly) NSString *typeIdentifier;
@property (nonatomic, readonly, getter=isFilePackage) BOOL filePackage;

@property (nonatomic, readonly) BOOL canRename;

// for subclasses

- (void)determineVisibility;
- (BOOL)isExpiredAndReloadAttributes:(BOOL)loadDataFlag;
- (BOOL)hasModificationDateChanged;
- (void)loadIcon;


// sudo-private
- (void)setKind__:(NSString *)kind;

@end


extern CGSize ImageSizeForIconSize(PCFileSystemIconSize iconSize);


#if !TARGET_OS_IPHONE
@interface PCNode (AppleScript)

- (NSScriptObjectSpecifier *)objectSpecifier;
- (NSString *)uniqueID;

@end
#endif


@interface PCNodePrettySizeTransformer : NSValueTransformer

@end

@interface PCNodePrettyPhysicalSizeTransformer : NSValueTransformer

@end

@interface PCNodePrettyOwnerTransformer : NSValueTransformer

@end

@interface PCNodePrettyGroupTransformer : NSValueTransformer

@end

@interface PCNodeEncodedFilenameTransformer : NSValueTransformer

@end


@interface PCNode (FileManagerAdditions)

- (PCVirtualFileManager*)fileManager;
- (PCRemoteFileManager*)remoteFileManager;
- (PCLocalFileManager*)localFileManager;

@end
