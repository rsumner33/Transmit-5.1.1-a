#import "FTPKitConstants.h"
#import "FTPKitProtocols.h"
#import <PanicCore/PanicCore.h>

@class PCMapTable;
@class PCSortController;

extern NSString * const PCSortControllerInsertedIndexesKey;
extern NSString * const PCSortControllerRemovedIndexesKey;


@interface PCSortController : NSObject <PCMessageQueueDelegate>
{
	PCMapTable* iCacheMap;
	NSPredicate *iShowFilesPredicate;
	NSPredicate *iHideFilesPredicate;
	BOOL iShowHiddenFiles;
}

@property(nonatomic, readonly, retain) PCMapTable* cacheMap;
@property(retain) NSPredicate* showFilesPredicate;
@property(retain) NSPredicate* hideFilesPredicate;
@property(assign) BOOL showHiddenFiles;

- (NSArray*)sortedArrayWithNodes:(NSArray*)nodes sortType:(FTPSortType)sortType subSortType:(FTPSortType)subSortType order:(NSComparisonResult)order;
- (void)sortArrayByInsertingNodes:(NSArray*)nodes intoArray:(NSMutableArray*)intoArray sortType:(FTPSortType)sortType subSortType:(FTPSortType)subSortType order:(NSComparisonResult)order;

- (NSArray*)setContentsBySortingNodes:(NSArray*)contents forKey:(id)key sortType:(FTPSortType)sortType subSortType:(FTPSortType)subSortType order:(NSComparisonResult)order;
- (void)setSortedContents:(NSArray*)contents forKey:(id)key sortType:(FTPSortType)sortType subSortType:(FTPSortType)subSortType order:(NSComparisonResult)order;

- (void)updateContentsByInsertingNodes:(NSArray*)inserted forKey:(id)key;
- (void)updateContentsByRemovingNodes:(NSArray*)removed forKey:(id)key ;

- (void)sortContentsForKey:(id)key sortType:(FTPSortType)sortType subSortType:(FTPSortType)subSortType order:(NSComparisonResult)order;

- (NSArray*)applyPredicatesToNodes:(NSArray*)nodes;

- (NSMutableArray*)contentsForKey:(id)key;
- (NSComparisonResult)orderForKey:(id)key;
- (FTPSortType)sortTypeForKey:(id)key;
- (FTPSortType)subSortTypeForKey:(id)key;

- (void)removeAllContents;
- (void)removeContentsForKey:(id)aKey;

@end
