#import "PCRemoteOperation.h"

// in order to match PCLocalSumSizeOperation, operation result is an NSArray with item 0 being total size and item 1 being total physical size
@interface PCRemoteSumSizeOperation : PCRemoteOperation

@property (nonatomic, assign) BOOL sumTransferSizes; // only sums files that will be transfered with current rules

@end
