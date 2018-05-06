#import <FTPKit/FTPKit.h>


@interface URLFactory : NSObject 
{
}

+ (NSURL*)URLWithScheme:(NSString*)scheme host:(NSString*)host port:(NSString*)port userName:(NSString*)userName password:(NSString*)password path:(NSString*)path;
+ (NSURL*)FTPURLWithInfo:(NSString*)host port:(NSString*)port userName:(NSString*)userName password:(NSString*)password path:(NSString*)path;

+ (NSString*)urlStringForNode:(PCNode*)node remoteFileManager:(PCRemoteFileManager*)remoteManager withPassword:(BOOL)includePassword;
+ (NSURL*)urlForNode:(PCNode*)node fileManager:(PCVirtualFileManager*)fileManager baseURL:(NSString*)baseURL initialPath:(NSString*)initalPath withPassword:(BOOL)includePassword;
+ (PCNode*)nodeForURL:(NSURL*)aURL fileManager:(PCVirtualFileManager*)fileManager remoteURL:(NSString*)remoteURL localURL:(NSString*)localURL basePath:(NSString*)basePath;

@end
