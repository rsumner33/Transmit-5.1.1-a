#import <Foundation/Foundation.h>


@interface NSString (FilePermissions)

// this should eventually live elsewhere as it is more generally useful, hence the pc_ prefix
- (NSInteger)pc_integerValue; // respects literal prefixes (0, 0x)

@end


@interface NSNumber (FilePermissions)

+ (NSNumber*)ftp_numberWithModeValue:(mode_t)mode;

- (mode_t)ftp_modeValue;

@end


@interface FilePermissions : NSObject <NSCopying, NSCoding>
{
}

@property (nonatomic) mode_t mode;
@property (nonatomic) int octalValue; // decimal-coded octal, eg: 755

@property (nonatomic, getter=isUserReadable) BOOL userReadable;
@property (nonatomic, getter=isUserWritable) BOOL userWritable;
@property (nonatomic, getter=isUserExecutable) BOOL userExecutable;
@property (nonatomic, getter=isGroupReadable) BOOL groupReadable;
@property (nonatomic, getter=isGroupWritable) BOOL groupWritable;
@property (nonatomic, getter=isGroupExecutable) BOOL groupExecutable;
@property (nonatomic, getter=isWorldReadable) BOOL worldReadable;
@property (nonatomic, getter=isWorldWritable) BOOL worldWritable;
@property (nonatomic, getter=isWorldExecutable) BOOL worldExecutable;

+ (BOOL)isValidOctalValue:(int)octal;
+ (FilePermissions *)filePermissionsWithOctalValue:(int)octal;

- (id)initWithMode:(mode_t)mode;
- (id)initWithOctalValue:(int)octal;
- (id)initWithString:(NSString *)string;

@property (nonatomic, readonly) NSString *stringValue;  // "rwxr-wr-w"
@property (nonatomic, copy) NSString *octalStringValue; // "755"

@property (nonatomic, readonly) NSNumber *filePosixPermissions;

@end
