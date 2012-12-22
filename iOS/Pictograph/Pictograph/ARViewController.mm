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

@interface ARViewController ()<LayarPlayerDelegate, UITextViewDelegate, UITextFieldDelegate, UIActionSheetDelegate, UIImagePickerControllerDelegate, UINavigationControllerDelegate>
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

- (void)initLayar;
- (void)initPicker;
- (void)initActionSheet;
- (void)openAlbum;
- (BOOL)isDataCorrect;
- (void)sendGreetingsRequest;

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
    NSString *layerName = @"cherkassytest";//cherkasy2013
    NSString *consumerKey = @"1234";//@"cherkasy2013";
    NSString *consumerSecret = @"4321";//@"2013cherkasy";
    
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
        [self sendGreetingsRequest];
    }
    else{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:APP_NAME message:NOT_ALL_DATA_ADDED delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil];
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
    NSData *imageToUpload = UIImageJPEGRepresentation(_currentImage.image, 90);
    AFHTTPClient *client= [AFHTTPClient clientWithBaseURL:[NSURL URLWithString:BASE_URL]];    
     CLLocationCoordinate2D loc = DELEGATE.getCurrentLocation.coordinate;
    NSDictionary *paramaters = [NSDictionary dictionaryWithObjectsAndKeys:
                                [NSString stringWithFormat:@"%f", loc.latitude], @"lat",
                                [NSString stringWithFormat:@"%f", loc.longitude], @"lng",
                                _messageView.text, @"message",
                                @"Max", @"author",
                                [Settings setMUUID], @"deviceId",
                                nil];
    NSLog(@"P{arams %@", paramaters);
    
    NSMutableURLRequest *request = [client multipartFormRequestWithMethod:@"POST" path:POST_URL_PATH parameters:paramaters constructingBodyWithBlock: ^(id <AFMultipartFormData>formData) {
        [formData appendPartWithFileData: imageToUpload name:@"photo" fileName:@"temp.jpeg" mimeType:@"image/jpeg"];
    }];
    
    AFHTTPRequestOperation *operation = [[AFHTTPRequestOperation alloc] initWithRequest:request];
    
    [operation setCompletionBlockWithSuccess:^(AFHTTPRequestOperation *operation, id responseObject) {
        NSString *response = [operation responseString];
        if ([response integerValue] == 200) {
            [self cleareData];
        }
        NSLog(@"response: [%@]",response);
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        if([operation.response statusCode] == 403){
            NSLog(@"Upload Failed");
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:APP_NAME message:SERVER_NOT_AVAILABLE delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
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

@end
