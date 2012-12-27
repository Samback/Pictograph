//
//  ARSettingsController.m
//  Pictograph
//
//  Created by Max on 25.12.12.
//  Copyright (c) 2012 Max Tymchii. All rights reserved.
//

#import "ARSettingsController.h"
#import "GRButtons.h"

@interface ARSettingsController ()<UITableViewDelegate, UITableViewDataSource, VkontakteDelegate, VkontakteViewControllerDelegate>
@property (strong, nonatomic) IBOutlet UISwitch *vkLogin;
@property (strong, nonatomic) IBOutlet UISwitch *postOnVKWall;
@property (strong, nonatomic) IBOutlet UISwitch *twitterLogin;
@property (strong, nonatomic) IBOutlet UISwitch *postOnTwitterWall;


- (void)setInitialParametersOfSwittchers;

@end

@implementation ARSettingsController
@synthesize vkLogin = _vkLogin;
@synthesize postOnVKWall = _postOnVKWall;
@synthesize twitterLogin = _twitterLogin;
@synthesize postOnTwitterWall = _postOnTwitterWall;


- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setInitialParametersOfSwittchers];    
	// Do any additional setup after loading the view.
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    DELEGATE.vkontakte.delegate = self;
}

- (void)viewDidUnload
{
    [self setVkLogin:nil];
    [self setPostOnVKWall:nil];
    [self setTwitterLogin:nil];
    [self setPostOnTwitterWall:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction)vkLoginSwitch:(UISwitch *)sender {
    if (sender.on) {
        [DELEGATE.vkontakte authenticate];
    }
    else{
        [DELEGATE.vkontakte logout];
    }
}

- (IBAction)postOnVKWallSwitch:(UISwitch *)sender {
    [Settings saveValueForValue:@(sender.on) withKey:VK_POST_ON_WALL_KEY];
}

- (IBAction)loginToTwitterSwitch:(UISwitch *)sender {
}

- (IBAction)postOnTwitterWall:(UISwitch *)sender {
    [Settings saveValueForValue:@(sender.on) withKey:TWITTER_POST_ON_WALL_KEY];
}

- (void)setInitialParametersOfSwittchers{
    if ([DELEGATE.vkontakte isAuthorized]) {
         _postOnVKWall.on = [[[Settings valueForKey:VK_POST_ON_WALL_KEY] description] boolValue];
          _postOnVKWall.enabled = YES;
        _vkLogin.on = YES;
    }
      else{
          _vkLogin.on = NO;
          _postOnVKWall.enabled = NO;
          _postOnVKWall.on = NO;
    }
    _postOnTwitterWall.on = (BOOL)[Settings valueForKey:TWITTER_POST_ON_WALL_KEY];
    
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
    [self setInitialParametersOfSwittchers];
//    //  [self refreshButtonState];
}

- (void)vkontakteDidFinishLogOut:(Vkontakte *)vkontakte
{
    [self setInitialParametersOfSwittchers];
    // [self refreshButtonState];
}


@end
