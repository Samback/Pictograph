//
//  Settings.h
//  Baker
//
//  Created by Max on 19.11.12.
//
//

#import <Foundation/Foundation.h>

@interface Settings : NSObject
+ (NSString *)IPAddress;
+ (NSString *)deviceType;
+ (NSString *)systemName;
+ (NSString *)systemVersion;
+ (NSString *)setMUUID;
+ (void)saveShareText:(NSString *)shareText;
+ (NSDictionary *)downloadedAction:(NSString *)editionId;
+ (NSString *)convertDateStringToPrettyForm:(NSString *)string;
+ (UIImage*)imageWithImage:(UIImage*)image scaledToSize:(CGSize)newSize;
+ (UIImage*)imageWithImage:(UIImage*)sourceImage scaledToSizeWithSameAspectRatio:(CGSize)targetSize;
+ (UIImage*)imageWithImage:(UIImage*)sourceImage scaledToSizeKeepingAspect:(CGSize)targetSize;
@end
