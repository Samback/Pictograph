//
//  LPWebViewController.h
//  Layar
//
//  Created by Lawrence Lee on 7/23/10.
//  Copyright 2010 Layar B.V. All rights reserved.
//

#import "LPWebViewControllerBase.h"

#define LPWebViewControllerParameterKey	@"LPWebViewControllerParameterKey"
#define LPWebViewControllerActionKey	@"LPWebViewControllerActionKey"

typedef enum LPWebViewControllerEvent
{
	LPWebViewControllerActionGetBackToAppEvent = 0,
	LPWebViewControllerActionLayerEvent
} LPWebViewControllerEvent;

@class LPAudioPlayer;

@interface LPWebViewController : LPWebViewControllerBase
{
	NSMutableDictionary *targets;
	UIBarButtonItem *backButton;
	UIBarButtonItem *forwardButton;
	UIBarButtonItem *reloadButton;
    
    LPAudioPlayer *audioPlayer;
}
@property (nonatomic, retain) LPAudioPlayer *audioPlayer;

- (void)addTarget:(id)target action:(SEL)action forEvent:(LPWebViewControllerEvent)event;
- (void)removeTargetForEvent:(LPWebViewControllerEvent)event;
- (void)removeTarget:(id)target;
- (void)removeAllTargets;
- (void)loadRequest:(NSURLRequest*)request;
- (void)close;
- (void)goBack;
- (void)goForward;
- (void)reload;
//- (void)openInSafari;

- (void)videoFinishedPlaying:(NSNotification*)notification;
- (void)videoExitedFullscreen:(NSNotification*)notification;
- (void)audioPlayerStoppedPlaying:(NSNotification*)notification;

@end
