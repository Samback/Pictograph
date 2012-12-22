//
//  LPViewControllerBase.h
//  layarplayer
//
//  Created by Lawrence Lee on 11/11/10.
//  Copyright (c) 2010 Layar B.V. All rights reserved.
//

//System imports
#import <UIKit/UIKit.h>
#import <CoreLocation/CLLocation.h>

//LayarCore imports
#import <LSPOIView.h>

//Local imports
#import "LayarPlayerDelegate.h"
#import "LPStatusView.h"
#import "LPCachingViewController.h"
#import "LPLayerSettingsViewController.h"

#define LPConsumerKeyParameterKey		@"LPConsumerKeyParameterKey"
#define LPConsumerSecretParameterKey	@"LPConsumerSecretParameterKey"

/**
 * @brief Options to govern the accessibility of various views in the program
 */
typedef enum LPOptions
{
	LPAllViewsEnabled  = 0,         /**< All views are enabled */
	LPMapViewDisabled  = (1 << 0),  /**< Disable access of the map view */
	LPListViewDisabled = (1 << 1),  /**< Disable access of the list view */
    LPCameraViewDisabled = (1 << 2) /**< Disable access of the camera view */
    
} LPOptions;

@class LSAction;
@class LSRequest;
@class LPViewControllerBase;
@class LSLayer;
@class LSPOI;
@class LSPOIModel;
@class LSPOIRenderable;
@class LSPOIParser;
@class LSLayerDetailsParser;

@class LCConnectionManager;

@class LPAudioPlayer;
@class LPActionRequest;
@class LPAsyncActionRequest;
@class LPWebViewController;
@class LPMessageView;

@interface LPViewControllerBase : LPCachingViewController <UIActionSheetDelegate, UIAlertViewDelegate, LSPOIView, LPStatusViewDelegate, LPLayerSettingsViewControllerDelegate>
{
	id <LayarPlayerDelegate> delegate;
	LSAction *layerAction;
	LPAsyncActionRequest *asyncRequest;
	LPActionRequest *textRequest;
	LCConnectionManager *connectionManager;
	
	LPOptions viewOptions;
    LSPOIModel *model;
	LSLayer *layer;
	LSRequest *layerDetailsRequest;
	LSRequest *poiRequest;
	BOOL needsLocation;
	BOOL listeningForGeolocation;
	BOOL parsePoisOnLocationUpdate;
	NSString *countryCode;
	NSString *localCountryCode;
    NSString *analyticsCityName; // Analytics stuff
	CLLocation *location;
	NSString *oauthConsumerKey;
	NSString *oauthConsumerSecret;
	NSMutableDictionary *initialFilters;
	NSMutableDictionary *customParametersForPOIRequest;
	
	NSTimer *poiRequestTimer;
	CLLocationCoordinate2D locationSinceLastPoiUpdate;
	int refreshInterval;
	int refreshDistance;
	BOOL fullRefresh;
	
	LPAudioPlayer *audioPlayer;
	LPMessageView *messageView;
	
	BOOL refreshPois;
	BOOL closing;
	BOOL visible;
	BOOL showLayerSettings;
	BOOL showLayerAuthenticationPage;
	BOOL showingSettingOnLaunch;
	BOOL skipSettingsOnLaunch;
	BOOL keepMessageOnScreen;
	
	UIActionSheet *layerActionSheet;
	UIActionSheet *poiActionSheet;
	NSArray *poiActions;
	
	BOOL transitionInProgress;
    
    NSString *recognizedReferenceImageId;
	
@protected
	NSTimer *messageViewTimer;
}

/**
 * @brief The program delegate
 */
@property (nonatomic, assign) id <LayarPlayerDelegate> delegate;

/**
 * @brief Async request
 */
@property (nonatomic, retain) LPAsyncActionRequest *asyncRequest;

/**
 * @brief Text request
 */
@property (nonatomic, retain) LPActionRequest *textRequest;

/**
 * @brief The select view options
 */
@property (nonatomic, assign) LPOptions viewOptions;

/**
 * @brief Layer details request
 */
@property (nonatomic, retain) LSRequest *layerDetailsRequest;

/**
 * @brief POI request
 */
@property (nonatomic, retain) LSRequest *poiRequest;

/**
 * @brief The POI model
 */
@property (nonatomic, retain) LSPOIModel *model;

/**
 * @brief The currently loaded layer
 */
@property (nonatomic, retain) LSLayer *layer;

/**
 * @brief The country code parameter for Layar API requests
 */
@property (nonatomic, copy) NSString *countryCode;

/**
 * @brief The local country code parameter for Layar API requests
 */
@property (nonatomic, copy) NSString *localCountryCode;

/**
 * @brief The fixed location
 */
@property (nonatomic, retain) CLLocation* location;

/**
 * @brief The OAuth consumer key
 *
 * All network requests are signed using this key
 */
@property (nonatomic, copy) NSString *oauthConsumerKey;

/**
 * @brief The OAuth consumer secret
 *
 * All network requests are signed using this key
 */
@property (nonatomic, copy) NSString *oauthConsumerSecret;

/**
 * @brief The layer parameters
 *
 * These are the parameters that are sent with the POI request
 */
@property (nonatomic, copy) NSDictionary *initialFilters;

/**
 * @brief Custom getPoi request parameters
 *
 * These are the custom parameters that are sent with the POI request
 */
@property (nonatomic, retain) NSMutableDictionary *customParametersForPOIRequest;

/**
 * @brief The audio player
 */
@property (nonatomic, retain) LPAudioPlayer *audioPlayer;

/**
 * @brief If set to YES the grid is rendered in the Augmented Reality View. Default is NO.
 */
@property (nonatomic, assign) BOOL showGrid;

/**
 * @brief If set to YES the showSettingsOnLaunch option is ignore. Default is NO. Should be set before setting layer.
 */
@property (nonatomic, assign) BOOL skipSettingsOnLaunch;

/**
 * @brief Recognized Reference Image 
 *
 * Reference image id which triggered launching layer from visual search. Can be nil if layer wasn't launched from visual search.
 */
@property (nonatomic, copy) NSString *recognizedReferenceImageId;

/**
 * @brief View controller that presented modal view controller
 */
@property (nonatomic, readonly) UIViewController *presentingParentViewController;


/**
 * @brief Close the view
 *
 * This dismissed the modally presented view controller
 */
- (void)close:(id)sender;

/**
 * @brief Internet connection not available
 */
- (void)internetConnectionNotAvailable;

/**
 * @brief Request geolocation
 */
- (void)requestGeolocation;

/**
 * @brief Call when application will background
 */
- (void)applicationWillResignActive;

/**
 * @brief Call when application did background
 */
- (void)applicationDidEnterBackground;

/**
 * @brief Call when application will enter foreground
 */
- (void)applicationWillEnterForeground;

/**
 * @brief Call when application resumes from background
 */
- (void)applicationDidBecomeActive;

/**
 * @brief Call when the application will terminate
 */
- (void)applicationWillTerminate;

/**
 * @brief Number of buttons in the select view popup
 */
- (int)viewButtons;

/**
 * @brief Show layer settings
 */
- (void)showLayerSettings;

/**
 * @brief Show layer settings
 */
- (void)showLayerAuthenticationPage;

/**
 * @brief Show layer actions
 */
- (void)showLayerActions;

/**
 * @brief Show camera view
 */
- (void)showCameraView;

/**
 * @brief Show map view
 */
- (void)showMapView;

/**
 * @brief Show list view
 */
- (void)showListView;

/**
 * @brief Show a message popup
 */
- (void)showMessage:(NSString*)message;

/**
 * @brief Close message popup
 */
- (void)closeMessageView:(NSTimer*)timer;

/**
 * @brief Message popup closed
 */
- (void)messageViewClosed;

/**
 * @brief Invalidate the refresh pois timer
 */
- (void)invalidateRefreshPoisTimer;

/**
 * @brief Initialize the refresh pois timer
 */
- (void)initializeRefreshPoisTimerWithInterval:(NSTimeInterval)interval timerRepeats:(BOOL)repeats;

/**
 * @brief Parse error code for a request
 */
- (void)parseErrorForRequest:(LSRequest*)request;

/**
 * @brief Parse error code for a poi request
 */
- (void)parseErrorForPoiRequest:(LSRequest*)request;

/**
 * @brief Refresh pois by force (getPois with a few checks)
 */
- (void)forceRefreshPOIs;

/**
 * @brief Callback for poi refresh timer
 */
- (void)refreshPois:(NSTimer*)timer;

/**
 * @brief Perform a GetPOI request for the current layer
 *
 * This will issue a refresh request for POI's for the current layer.
 * When the request completes, it will replace all currently loaded POI's
 */
- (BOOL)getPois;

/**
 * @brief Perform a GetPOI request with a layer action
 */
- (BOOL)getPoisWithLayerAction:(LSAction*)action;

/**
 * @brief Helper function called by poiRequestCompleted
 */
- (void)handleCompletedGetPoisRequest;

/**
 * @brief Parse GetPOI request
 *
 * @param request The request to parse
 * @param parser The parser with which to parse the request
 */
- (void)parseGetPoisRequest:(LSRequest*)request withParser:(LSPOIParser*)parser;

/**
 * @brief The get poi request completion callback
 */
- (void)poiRequestCompleted:(NSNotification*)notification;

/**
 * @brief The get poi request failure callback
 */
- (void)poiRequestFailed:(NSNotification*)notification;

/**
 * @brief The get poi request cancelation callback
 */
- (void)poiRequestCancelled:(NSNotification*)notification;

/**
 * @brief Send a layer details request
 */
- (BOOL)sendLayerDetailsRequest;

/**
 * @brief Parse Layer details request
 *
 * @param request The request to parse
 * @param parser The parser with which to parse the request
 */
- (void)parseLayerDetailsRequest:(LSRequest*)request withParser:(LSLayerDetailsParser*)parser;

/**
 * @brief The layer details request completion callback
 */
- (void)layerDetailsRequestCompleted:(NSNotification*)notification;

/**
 * @brief The layer details request failure callback
 */
- (void)layerDetailsRequestFailed:(NSNotification*)notification;

/**
 * @brief The layer details request cancelation callback
 */
- (void)layerDetailsRequestCancelled:(NSNotification*)notification;

/**
 * @brief The text request completion callback
 */
- (void)textRequestCompleted:(NSNotification*)notification;

/**
 * @brief The text request failure callback
 */
- (void)textRequestFailed:(NSNotification*)notification;

/**
 * @brief The text request cancelation callback
 */
- (void)textRequestCancelled:(NSNotification*)notification;

/**
 * @brief Handle POI click event
 */
- (void)handlePoiClick:(LSPOI *)poi;

/**
 * @brief The async request completion callback
 */
- (void)asyncRequestCompleted:(NSNotification*)notification;

/**
 * @brief The async request failure callback
 */
- (void)asyncRequestFailed:(NSNotification*)notification;

/**
 * @brief The async request cancelation callback
 */
- (void)asyncRequestCancelled:(NSNotification*)notification;

/**
 * @brief The heading available callback
 */
- (void)headingAvailable:(NSNotification*)notification;

/**
 * @brief The location update available callback
 */
- (void)locationUpdateAvailable:(NSNotification*)notification;

/**
 * @brief The geolocation update available callback
 */
- (void)geolocationAvailable:(NSNotification*)notification;

/**
 * @brief The geolocation lookup failed callback
 */
- (void)geolocationLookupFailed:(NSNotification*)notification;

/**
 * @brief Reciever for action fired notification
 */
- (void)actionFired:(NSNotification*)notification;

/**
 * @brief Perform an action
 */
- (void)performAction:(LSAction*)action userInfo:(NSDictionary*)userInfo;

/**
 * @brief Perform triggered action
 */
- (void)performTriggeredAction:(LSAction*)action userInfo:(NSDictionary*)userInfo;

/**
 * @brief Perform an audio action
 */
- (void)performAudioActionWithUrl:(NSString*)url;

/**
 * @brief Perform a video action
 */
- (void)performVideoActionWithUrl:(NSString*)url;

/**
 * @brief Perform a web action
 */
- (void)performWebAction:(LSAction*)action;

/**
 * @brief Perform a text action
 */
- (void)performTextAction:(LSAction*)action;

/**
 * @brief Perform a take me there aciton
 */
- (void)performTakeMeThereAction:(LSAction*)action;

/**
 * @brief Perform a async action
 */
- (void)performAsyncAction:(LSAction*)action;

/**
 * @brief Perform a layer action
 */
- (void)performLayerAction:(LSAction*)action;

/**
 * @brief Perform an internal action
 */
- (void)performInternalAction:(LSAction*)action;

/**
 * @brief Perform the first  action for a poi
 *
 * This is normally used for a poi that has showBiwOnClick set to false
 */
- (void)performFirstTriggerAction:(LSPOI*)poi;

/**
 * @brief Calculate the triggered action due to a position update or inserted/updated POI's
 *
 * @parame aModel The model the indexes belong to
 * @param indexes The indexes of the POI's to calculate the triggered action
 */
- (void)calculateTriggeredActionForPois:(NSArray *)pois withOldLocation:(CLLocation *)oldLocation newLocation:(CLLocation *)newLocation;

/**
 * @brief Audio player stopped playing callback
 */
- (void)audioPlayerStoppedPlaying:(NSNotification*)notification;

/**
 * @brief Video finished playing callback
 */
- (void)videoFinishedPlaying:(NSNotification*)notification;

/**
 * @brief Video exited fullscreen callback
 */
- (void)videoExitedFullscreen:(NSNotification*)notification;

/**
 * @brief Use this function to load a layer
 *
 * The layer @p layerName will be loaded and the POI's will be downloaded for the layer.
 * The @p oauthParameters dictionary must contain the consumer key and consumer secret required
 * by the layer. These must be added to @p oauthParameters using the LPConsumerKeyParameterKey
 * and LPConsumerSecretParameterKey respectively.
 * Any filter options for the layer that differ from the default values can be passed using the @p parameters dictionary.
 * The @p options parameter can be used to pass any options to the program.
 *
 * @param layerName The name of the layer to load
 * @param oauthParameters The oauth consumer key and consumer secret required by the layer.
 * These must be added using the LPConsumerKeyParameterKey and LPConsumerSecretParameterKey respectively.
 * @param parameters The layer filters/parameters to pass with the request. If nil or an empty dictionary the default values for all filters for the layer will be used.
 * @param options Options to pass to the program
 */
- (void)loadLayerWithName:(NSString*)layerName oauthParameters:(NSDictionary*)oauthParameters parameters:(NSDictionary*)parameters options:(LPOptions)options;

@end
