#import "PCFSOperation.h"

@class PCFileNode;

@interface PCLocalRenameOperation : PCFSOperation

@property (copy) NSString* originalFilename;

- (PCLocalRenameOperation*)initWithNode:(PCFileNode*)node name:(NSString*)name;

@end


@interface PCLocalRenameOperation (PreventUnnecessaryCasting)

+ (PCLocalRenameOperation*)alloc;

@end
