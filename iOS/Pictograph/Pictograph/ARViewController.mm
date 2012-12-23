//
//  ARViewController.m
//  Pictograph
//
//  Created by Max on 22.12.12.
//  Copyright (c) 2012 Max Tymchii. All rights reserved.
//

#import "ARViewController.hpp"
#import "LayarPlayer.hpp"
#import <QuartzCore/QuartzCore.h>
#import "Definitions.h"
#import <MobileCoreServices/UTCoreTypes.h>
#import "AFNetworking/AFHTTPClient.h"
#import "AFNetworking/AFHTTPRequestOperation.h"
#import "Vkontakte/Vkontakte.h"
#import "NSString+Gender.h"

@interface ARViewController ()<LayarPlayerDelegate, UITextViewDelegate, UITextFieldDelegate, UIActionSheetDelegate, UIImagePickerControllerDelegate, UINavigationControllerDelegate, VkontakteDelegate, VkontakteViewControllerDelegate, UIAlertViewDelegate, MBProgressHUDDelegate>
@property (strong, nonatomic) IBOutlet UIButton *openReality;
@property (strong, nonatomic) IBOutlet UIButton *photoButton;
@property (strong, nonatomic) IBOutlet UITextView *messageView;
@property (nonatomic, strong) LPAugmentedRealityViewController *layarController;
@property (strong, nonatomic) IBOutlet UIButton *sendGreetings;
@property (strong, nonatomic) UIActionSheet *actionSheet;
@property (nonatomic, strong) UIImagePickerController *pickerController;
@property (strong, nonatomic) IBOutlet UIImageView *currentImage;
@property (nonatomic) BOOL isAddPhoto;
@property (strong, nonatomic) IBOutlet UILabel *greetingsLabel;
@property (nonatomic, strong) Vkontakte *vkontakte;
@property (nonatomic, strong) NSDictionary *userInfo;
@property (nonatomic, strong) GRAlertView *alert;
@property (nonatomic, strong) MBProgressHUD *hud;

- (void)initLayar;
- (void)initPicker;
- (void)initActionSheet;
- (void)initVkontakte;
- (void)openAlbum;
- (BOOL)isDataCorrect;
- (void)sendGreetingsRequest;
- (void)postToVKWall;

@end

@implementation ARViewController
@synthesize openReality = _openReality;
@synthesize photoButton = _photoButton;
@synthesize messageView = _messageView;
@synthesize layarController = _layarController;
@synthesize sendGreetings = _sendGreetings;
@synthesize actionSheet = _actionSheet;
@synthesize pickerController = _pickerController;
@synthesize currentImage = _currentImage;
@synthesize isAddPhoto = _isAddPhoto;
@synthesize greetingsLabel = _greetingsLabel;
@synthesize userInfo = _userInfo;
@synthesize alert = _alert;
@synthesize hud = _hud;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    self.currentImage.layer.cornerRadius = 15;
    self.currentImage.layer.borderWidth = 2;
    self.currentImage.layer.borderColor = [UIColor blueColor].CGColor;
    
    self.messageView.layer.cornerRadius = 15;
    self.messageView.layer.borderWidth = 2;
    self.messageView.layer.borderColor = [UIColor blueColor].CGColor;
    
    self.openReality.layer.cornerRadius = 10;
    self.sendGreetings.layer.cornerRadius = 10;

    [self.openReality setTitle:REALITY_BUTTON_TITLE forState:UIControlStateNormal];
    [self.sendGreetings setTitle:GREETINGS_BUTTON_TITLE forState:UIControlStateNormal];
    
    self.currentImage.image = DEFAULT_IMAGE;
    self.messageView.delegate = self;
    self.greetingsLabel.text = GREETINGS_LABEL_TITLE;
    [self initLayar];
    [self initPicker];
    [self initActionSheet];
    [self initVkontakte];
    
    
    self.hud =  [[MBProgressHUD alloc] initWithView:self.view];
    [self.view addSubview:_hud];
	_hud.dimBackground = YES;
    _hud.delegate = self;
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
}

- (IBAction)playClick:(UIButton *)sender {
    [_messageView resignFirstResponder];
    [self initLayar];
    [self presentModalViewController:_layarController animated:YES];
}

- (void)viewDidUnload {
    [self setOpenReality:nil];
    [self setPhotoButton:nil];
    [self setMessageView:nil];
    [self setSendGreetings:nil];
    [self setCurrentImage:nil];
    [self setGreetingsLabel:nil];
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}
- (IBAction)takePicture:(UIButton *)sender {
    [DELEGATE startUpdatePosition];
    [_messageView resignFirstResponder];
    [_actionSheet showInView:self.view];
}

#pragma mark - UIAction Delegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    if (alertView.cancelButtonIndex == buttonIndex) {
        return;
    }
    [_vkontakte authenticate];
}

#pragma mark -Vkontakte Delegate methods
- (void)initVkontakte{
    _vkontakte = [Vkontakte sharedInstance];
    _vkontakte.delegate = self;
}

#pragma mark - Getting photos

- (void)openCamera{
    _pickerController.sourceType=UIImagePickerControllerSourceTypeCamera;
    [self presentModalViewController:_pickerController animated:YES];
}

- (void)openAlbum{
    _pickerController.sourceType=UIImagePickerControllerSourceTypePhotoLibrary;
    [self presentModalViewController:_pickerController animated:YES];
}

#pragma mark - Picker Delegate methods
-(void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{   
    NSString *mediaType = [info objectForKey: UIImagePickerControllerMediaType];
    UIImage *originalImage, *editedImage, *imageToSave;
    
    // Handle a still image capture
    if (CFStringCompare ((__bridge CFStringRef) mediaType, kUTTypeImage, 0)
        == kCFCompareEqualTo) {
        
        editedImage = (UIImage *) [info objectForKey:
                                   UIImagePickerControllerEditedImage];
        originalImage = (UIImage *) [info objectForKey:
                                     UIImagePickerControllerOriginalImage];
        
        if (editedImage) {
            imageToSave = editedImage;
        } else {
            imageToSave = originalImage;
        }
        
        //        // Save the new image (original or edited) to the Camera Roll
        if (_pickerController.sourceType == UIImagePickerControllerSourceTypeCamera) {
          UIImageWriteToSavedPhotosAlbum (imageToSave, nil, nil , nil);  
        }
        self.currentImage.image = imageToSave;
        [self.currentImage reloadInputViews];
    }
    
    // Handle a movie capture
    if (CFStringCompare ((__bridge CFStringRef) mediaType, kUTTypeMovie, 0)
        == kCFCompareEqualTo) {
        
        NSString *moviePath = [[info objectForKey:
                                UIImagePickerControllerMediaURL] path];
        
        if (UIVideoAtPathIsCompatibleWithSavedPhotosAlbum (moviePath)) {
            UISaveVideoAtPathToSavedPhotosAlbum (
                                                 moviePath, nil, nil, nil);
        }
    }
    [self dismissViewControllerAnimated:YES completion:^{
        
    }];
}

#pragma mark - UIActionSheet  methods
-(void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == actionSheet.cancelButtonIndex) {
        [DELEGATE finishUpdatePosition];
        return;
    }
    else if (buttonIndex == 0) {
        [self openCamera];
    }
    else if (buttonIndex == 1) {
        [self openAlbum];
    }
}


- (void)initActionSheet{
    _actionSheet = [[UIActionSheet alloc] initWithTitle:SELECT_PHOTO_MESSAGE_DEFENITION delegate:self cancelButtonTitle:@"Cancel" destructiveButtonTitle:nil otherButtonTitles: CAMERA_BUTTON_TITLE, PHOTO_LIBRARY_BUTTON_TITLE, nil];
}

- (void)initPicker{
    _pickerController = [[UIImagePickerController alloc] init];
    // _pickerController.sourceType=UIImagePickerControllerSourceTypePhotoLibrary;
    _pickerController.delegate = self;
    _pickerController.allowsEditing = NO;
}


#pragma mark - Init layar
- (void)initLayar{
    NSString *layerName = @"cherkassytest";//cherkasy2013///cherkassytest
    NSString *consumerKey = @"1234";//@"cherkasy2013";
    NSString *consumerSecret = @"4321";//@"2013cherkasy";
    
    
//    NSString *layerName = @"cherkasy2013";//cherkasy2013
//    NSString *consumerKey = @"cherkasy2013";//@"cherkasy2013";
//    NSString *consumerSecret = @"2013cherkasy";//@"2013cherkasy";
    
    NSArray *oauthKeys = [NSArray arrayWithObjects:LPConsumerKeyParameterKey, LPConsumerSecretParameterKey, nil];
    NSArray *oauthValues = [NSArray arrayWithObjects:consumerKey, consumerSecret, nil];
    NSDictionary *oauthParameters = [NSDictionary dictionaryWithObjects:oauthValues forKeys:oauthKeys];
    NSArray *layerKeys = [NSArray arrayWithObject:@"radius"];
    NSArray *layerValues = [NSArray arrayWithObject:@"5000"];
    NSDictionary *layerFilters = [NSDictionary dictionaryWithObjects:layerValues forKeys:layerKeys];
    
    LPAugmentedRealityViewController *augmentedRealityViewController = [[LPAugmentedRealityViewController alloc] init];  // NOTE that here we do not use "autorelease" because we enabled " Use Automatic Reference Counting" when the project      was created. If this option is disabled, you need to manage resource yourself in the code.
    
    augmentedRealityViewController.delegate = self;
    //    [augmentedRealityViewController setShowGrid:YES];
    augmentedRealityViewController.skipSettingsOnLaunch = YES;
    [augmentedRealityViewController loadLayerWithName:layerName oauthParameters:oauthParameters parameters:layerFilters options:LPAllViewsEnabled];
    self.layarController = augmentedRealityViewController;
    self.isAddPhoto = YES;
    [DELEGATE finishUpdatePosition];
}

#pragma mark - UITextField delegate methods
- (BOOL)textView:(UITextView *)textView
shouldChangeTextInRange:(NSRange)range
 replacementText:(NSString *)text
{
    if ([text isEqualToString:@"\n"])
    {
        [textView resignFirstResponder];
    }
    return YES;
}

#pragma mark - Send request method
- (IBAction)sendRequests:(UIButton *)sender {    
    if ([self isDataCorrect]) {
        if ([_vkontakte isAuthorized]){
             [self postToVKWall];
        }
        else{
           _alert = [[GRAlertView alloc] initWithTitle:APP_NAME
                                                message:VK_MESSAGE
                                               delegate:self
                                      cancelButtonTitle:@"Cancel"
                                      otherButtonTitles:@"OK", nil];
            
//           /* [_alert setTopColor:[UIColor colorWithRed:0.7 green:0 blue:0 alpha:1]
//                    middleColor:[UIColor colorWithRed:0.5 green:0 blue:0 alpha:1]
//                    bottomColor:[UIColor colorWithRed:0.4 green:0 blue:0 alpha:1]
//                      lineColor:[UIColor colorWithRed:0.7 green:0 blue:0 alpha:1]];
//            */
//            alert.style = GRAlertStyleAlert;            // set UIAlertView style
//            alert.animation = GRAlertAnimationLines;
//           /* [_alert setFontName:@"Cochin-BoldItalic"
//                      fontColor:[UIColor greenColor]
//                fontShadowColor:[UIColor colorWithRed:0.8 green:0 blue:0 alpha:1]];
//            */
//            
//            [alert setImage:@"alert.png"];
//            [alert show];
            
            _alert.style = GRAlertStyleInfo;            // set UIAlertView style
            /*[_alert setTopColor:[UIColor colorWithRed:0.7 green:0 blue:0 alpha:1]
                   middleColor:[UIColor colorWithRed:0.5 green:0 blue:0 alpha:1]
                   bottomColor:[UIColor colorWithRed:0.4 green:0 blue:0 alpha:1]
                     lineColor:[UIColor colorWithRed:0.7 green:0 blue:0 alpha:1]];
             */
            [_alert setFontName:@"Cochin-BoldItalic"
                     fontColor:[UIColor greenColor]
               fontShadowColor:[UIColor colorWithRed:0.8 green:0 blue:0 alpha:1]];
            _alert.animation = GRAlertAnimationBorder;    // set animation type
            [_alert setImage:@"santa.png"];              // add icon image
            [_alert show];

        }
    }
    else{
        GRAlertView *alert = [[GRAlertView alloc] initWithTitle:APP_NAME
                                                        message:NOT_ALL_DATA_ADDED
                                                       delegate:self
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles: nil];
        alert.style = GRAlertStyleAlert;            // set UIAlertView style
        alert.animation = GRAlertAnimationLines;    // set animation type
        [alert setImage:@"alert.png"];              // add icon image
        [alert show];
    }   
}

- (BOOL)isDataCorrect{
    if ([_messageView.text isEqualToString:@""] || !_messageView.text) {
        return NO;
    }
    return _isAddPhoto;
}

- (void)sendGreetingsRequest{
    [_hud show:YES];
    NSData *imageToUpload = UIImageJPEGRepresentation(_currentImage.image, 90);
    AFHTTPClient *client= [AFHTTPClient clientWithBaseURL:[NSURL URLWithString:BASE_URL]];    
     CLLocationCoordinate2D loc = DELEGATE.getCurrentLocation.coordinate;
    
    NSString *photoUrl = [_userInfo objectForKey:@"photo_big"];
     NSString *userName = [NSString stringWithFormat:@"%@ %@", [_userInfo objectForKey:@"first_name"],  [_userInfo objectForKey:@"last_name"]];
    NSString *userBDate = [_userInfo objectForKey:@"bdate"];
    NSString *userGender = [NSString stringWithGenderId:[[_userInfo objectForKey:@"sex"] intValue]];
    NSString *userEmail = [_userInfo objectForKey:@"email"];
    
    NSDictionary *paramaters = [NSDictionary dictionaryWithObjectsAndKeys:
                                [NSString stringWithFormat:@"%f", loc.latitude], @"lat",
                                [NSString stringWithFormat:@"%f", loc.longitude], @"lng",
                                _messageView.text, @"message",
                                userName, @"author",
                                userBDate, @"birthday",
                                userGender, @"sex",
                                userEmail, @"email",
                                photoUrl, @"userImage",
                                [Settings setMUUID], @"deviceId",
                                nil];
    NSLog(@"P{arams %@", paramaters);
    
    NSMutableURLRequest *request = [client multipartFormRequestWithMethod:@"POST" path:POST_URL_PATH parameters:paramaters constructingBodyWithBlock: ^(id <AFMultipartFormData>formData) {
        [formData appendPartWithFileData: imageToUpload name:@"photo" fileName:@"temp.jpeg" mimeType:@"image/jpeg"];
    }];
    
    AFHTTPRequestOperation *operation = [[AFHTTPRequestOperation alloc] initWithRequest:request];
    
    [operation setCompletionBlockWithSuccess:^(AFHTTPRequestOperation *operation, id responseObject) {
        NSString *response = [operation responseString];
        dispatch_async(dispatch_get_main_queue(), ^{
            [_hud hide:YES];
        });
        if ([response integerValue] == 200) {
            [self cleareData];
        }
        NSLog(@"response: [%@]",response);
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        if([operation.response statusCode] == 403){
            GRAlertView *alert = [[GRAlertView alloc] initWithTitle:APP_NAME
                                                            message:SERVER_NOT_AVAILABLE
                                                           delegate:self
                                                  cancelButtonTitle:@"OK"
                                                  otherButtonTitles: nil];
            alert.style = GRAlertStyleAlert;            // set UIAlertView style
            alert.animation = GRAlertAnimationLines;    // set animation type
            [alert setImage:@"alert.png"];              // add icon image
            [alert show];
            return;
        }
        NSLog(@"error: %@", [operation error]);
        
    }];    
    [operation start];
}

- (void)cleareData{
    self.currentImage.image = DEFAULT_IMAGE;
    self.messageView.text = @"";
}


#pragma mark - VKONTAKTE DELEGATE METHODS
- (void)vkontakteDidFailedWithError:(NSError *)error
{
    [self dismissModalViewControllerAnimated:YES];
}

- (void)showVkontakteAuthController:(UIViewController *)controller
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        controller.modalPresentationStyle = UIModalPresentationFormSheet;
    }
    
    [self presentModalViewController:controller animated:YES];
}

- (void)vkontakteAuthControllerDidCancelled
{
    [self dismissModalViewControllerAnimated:YES];
}

- (void)vkontakteDidFinishLogin:(Vkontakte *)vkontakte
{
    [self dismissModalViewControllerAnimated:YES];
    [_vkontakte getUserInfo];
    [self postToVKWall];
  //  [self refreshButtonState];
}

- (void)vkontakteDidFinishLogOut:(Vkontakte *)vkontakte
{
   // [self refreshButtonState];
}

- (void)vkontakteDidFinishGettinUserInfo:(NSDictionary *)info
{
    self.userInfo = info;
}

- (void)vkontakteDidFinishPostingToWall:(NSDictionary *)responce
{
    NSLog(@"%@", responce);
    [self sendGreetingsRequest];    
}

- (void)postToVKWall{
    [_vkontakte postImageToWall:_currentImage.image
                           text:_messageView.text
                           link:[NSURL URLWithString:BASE_URL]];
}


//Feature post on wall dont post on wall

//Twitter Account implementation geted from http://eflorenzano.com/blog/2012/04/18/using-twitter-ios5-integration-single-sign-on/
//ACAccountStore *store = [[ACAccountStore alloc] init]; // Long-lived
//ACAccountType *twitterType = [store accountTypeWithAccountTypeIdentifier:ACAccountTypeIdentifierTwitter];
//[store requestAccessToAccountsWithType:twitterType withCompletionHandler:^(BOOL granted, NSError *error) {
//    if(granted) {
//        NSArray *twitterAccounts = [store accountsWithAccountType:twitterType];
//        
//        // If there are no accounts, we need to pop up an alert
//        if(twitterAccounts != nil && [twitterAccounts count] > 1) {
//            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"No Twitter Accounts"
//                                                            message:@"There are no Twitter accounts configured. You can add or create a Twitter account in Settings."
//                                                           delegate:nil
//                                                  cancelButtonTitle:@"OK"
//                                                  otherButtonTitles:nil];
//            [alert show];
//        } else {
//            ACAccount *account = [twitterAccounts objectAtIndex:0];
//            NSURL *url = [NSURL URLWithString:@"http://api.twitter.com/1/account/verify_credentials.json"];
//            TWRequest *req = [[TWRequest alloc] initWithURL:url
//                                                 parameters:nil
//                                              requestMethod:TWRequestMethodGET];
//            
//            // Important: attach the user's Twitter ACAccount object to the request
//            req.account = account;
//            
//            [req performRequestWithHandler:^(NSData *responseData,
//                                             NSHTTPURLResponse *urlResponse,
//                                             NSError *error) {
//                
//                // If there was an error making the request, display a message to the user
//                if(error != nil) {
//                    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Twitter Error"
//                                                                    message:@"There was an error talking to Twitter. Please try again later."
//                                                                   delegate:nil
//                                                          cancelButtonTitle:@"OK"
//                                                          otherButtonTitles:nil];
//                    [alert show];
//                    return;
//                }
//                
//                // Parse the JSON response
//                NSError *jsonError = nil;
//                id resp = [NSJSONSerialization JSONObjectWithData:responseData
//                                                          options:0
//                                                            error:&jsonError];
//                
//                // If there was an error decoding the JSON, display a message to the user
//                if(jsonError != nil) {
//                    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Twitter Error"
//                                                                    message:@"Twitter is not acting properly right now. Please try again later."
//                                                                   delegate:nil
//                                                          cancelButtonTitle:@"OK"
//                                                          otherButtonTitles:nil];
//                    [alert show];
//                    return;
//                }
//                
//                NSString *screenName = [resp objectForKey:@"screen_name"];
//                NSString *fullName = [resp objectForKey:@"name"];
//                NSString *location = [resp objectForKey:@"location"];
//                NSLog(@"Geted Data %@ %@ %@", screenName, fullName, location);
//                
//                // Make sure to perform our operation back on the main thread
//                dispatch_async(dispatch_get_main_queue(), ^{
//                    // Do something with the fetched data
//                });
//            }];            }
//    }
//    // Handle any error state here as you wish
//}];

//post image

//TWRequest *postRequest = [[TWRequest alloc] initWithURL:[NSURL URLWithString:@"https://upload.twitter.com/1/statuses/update_with_media.json"] parameters:nil requestMethod:TWRequestMethodPOST];
//
//UIImage * image = [UIImage imageNamed:@"myImage.png"];
//
////add text
//[postRequest addMultiPartData:[@"I just found the secret level!" dataUsingEncoding:NSUTF8StringEncoding] withName:@"status" type:@"multipart/form-data"];
////add image
//[postRequest addMultiPartData:UIImagePNGRepresentation(image) withName:@"media" type:@"multipart/form-data"];
//
//// Set the account used to post the tweet.
//[postRequest setAccount:twitterAccount];
//
//// Perform the request created above and create a handler block to handle the response.
//[postRequest performRequestWithHandler:^(NSData *responseData, NSHTTPURLResponse *urlResponse, NSError *error) {
//    NSString *output = [NSString stringWithFormat:@"HTTP response status: %i", [urlResponse statusCode]];
//    [self performSelectorOnMainThread:@selector(displayText:) withObject:output waitUntilDone:NO];
//}];

@end
