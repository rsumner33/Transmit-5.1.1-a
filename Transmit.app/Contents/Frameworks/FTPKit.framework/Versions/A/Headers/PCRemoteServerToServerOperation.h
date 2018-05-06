#import "PCRemoteUploadOperation.h"
#import "FTPKitProtocols.h"

@class PCRemoteFileManager;

@interface PCRemoteServerToServerOperation : PCRemoteUploadOperation <PCSpooledTransferOperation>

//@property (strong) PCRemoteFileManager *sourceFileManager;

@end
