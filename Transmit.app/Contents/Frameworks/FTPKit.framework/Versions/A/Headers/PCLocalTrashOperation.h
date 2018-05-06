#import "PCFSOperation.h"


@interface PCLocalTrashOperation : PCFSOperation

- (id)initWithNode:(PCFileNode*)node toTrash:(BOOL)toTrash;
- (id)initWithNodes:(NSArray*)nodes toTrash:(BOOL)toTrash;

@end
