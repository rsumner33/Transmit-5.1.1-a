#import "PCFolderNode.h"


@interface PCSmartFolderNode : PCFolderNode
{
	MDQueryRef	query;
}

@property (assign, getter=isFinished) BOOL finished;

- (void)startQuery;
- (void)stopQuery;

@end
