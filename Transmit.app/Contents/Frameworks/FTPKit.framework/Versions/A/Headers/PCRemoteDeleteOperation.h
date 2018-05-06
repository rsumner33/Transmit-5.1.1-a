#import "PCRemoteOperation.h"


@interface PCRemoteDeleteOperation : PCRemoteOperation <PCSpooledProcessingOperation>

+ (instancetype)operationWithNode:(PCRemoteFileNode*)node arguments:(NSDictionary*)args;

//- (id)initWithPath:(NSString*)inPath;
- (id)initWithPaths:(NSArray*)inPaths;

@end
