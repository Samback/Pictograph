#import "ARAppDelegate.hpp"

#define DELEGATE ((ARAppDelegate *)([[UIApplication sharedApplication] delegate]))
#define SELECT_PHOTO_MESSAGE_DEFENITION @"Select source of images"
#define CAMERA_BUTTON_TITLE @"Camera"
#define PHOTO_LIBRARY_BUTTON_TITLE @"Photo Library"
#define APP_NAME @"Pictograph"
#define NOT_ALL_DATA_ADDED @"Please make sure that you add photo and message to your greetings"
#define VK_MESSAGE @"To add post at location you should be login via VK"

#define GREETINGS_BUTTON_TITLE @"Send greetings"
#define REALITY_BUTTON_TITLE @"Open reality"

#define BASE_URL @"http://h.localhome.in.ua"
#define POST_URL_PATH @"/index.php?task=upload"
#define SERVER_NOT_AVAILABLE @"Server not available at this moment, please try later"
#define DEFAULT_IMAGE [UIImage imageNamed:@"default_image"]
#define MUUID @"uuid"


#define GREETINGS_LABEL_TITLE @"Add your greetings:"

#define FACEBOOK_APP_ID @"232707360194482"
#define FACEBOOK_APP_SECRET_ID @"b995138f0f8ce634df205fa719800652"