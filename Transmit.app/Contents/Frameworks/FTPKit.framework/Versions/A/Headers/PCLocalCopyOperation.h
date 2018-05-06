#import "PCLocalMoveOperation.h"

@interface PCLocalCopyOperation : PCLocalMoveOperation <PCSpooledTransferOperation, NSFileManagerDelegate>

@property (copy) NSString *customFilename;

@end
