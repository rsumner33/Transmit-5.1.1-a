#import "PCRemoteOperation.h"


@interface PCRemoteRawCommandOperation : PCRemoteOperation

@property (copy) NSString* command;

- (id)initWithCommand:(NSString*)inCommand;


@end
