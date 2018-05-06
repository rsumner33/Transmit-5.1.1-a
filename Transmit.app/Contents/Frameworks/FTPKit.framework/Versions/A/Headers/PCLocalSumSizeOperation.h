#import "PCFSOperation.h"

// operation result is an NSArray with item 0 being total size and item 1 being total physical size
@interface PCLocalSumSizeOperation : PCFSOperation

@property (nonatomic, assign) BOOL sumTransferSizes;

- (BOOL)sizeOfNodeContents:(PCNode*)node size:(unsigned long long*)sizeOfContents physicalSize:(unsigned long long*)physicalSizeOfContents;

@end
