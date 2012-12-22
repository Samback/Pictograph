/**
 * @file LPAugmentedRealityViewController.hpp
 *
 * @author Lawrence Lee, Layar B.V.
 * @date 25th October 2010
 */

//System imports
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

//LayarCommon imports
#import <LCTrackingManager.hpp>

//Local imports
#import "LPBIW.h"
#import "LPExtendedBIW.h"
#import "LPShowDialog.h"
#import "LPViewControllerBase.h"
#import "LPAugmentedRealityViewBase.h"
#import "LPAugmentedRealityDetailsView.h"

#define kBirdsEyeViewCheckedNotification	@"BirdsEyeViewCheckedNotification"

@class AVCaptureSession;
@class AVCaptureDevice;
@class AVCaptureDeviceInput;
@class AVCaptureVideoPreviewLayer;

@class LSAction;
@class LCResourceManager;
@class LCFeatureSet;
@class LPAugmentedRealityOverlayView;

/**
 * @class LPAugmentedRealityViewController
 * @brief UIViewController subclass that manages the Augmented Reality View
 *
 * The most important functionality of this class is to facilitate the loading
 * of a layer. This can be done using the loadLayerWithName method. When an
 * instance of this class is presented, it will request that the location
 * services and accelerometer services be enabled. It will also initialize
 * the camera and various overlay views for the Augmented Reality view, and
 * create the underlying OpenGL contexts for rendering.
 * The class also manages the various resources needed to render the scene,
 * and if necessary will also download any resources the POIs in the scene
 * require.
 */
@interface LPAugmentedRealityViewController : LPViewControllerBase <AVCaptureVideoDataOutputSampleBufferDelegate, 
LPBIWDelegate, LPExtendedBIWDelegate, LPShowDialogDelegate, LCTrackingManagerDelegate, LPAugmentedRealityDetailsViewDelegate>
{
	LCTrackingManager *trackingManager;
	
	LCFeatureSet *lastDetectedFeatureSet;
	NSTimeInterval lastDetectionTime;
	NSTimer *fadeoutTimer;
	
	dispatch_queue_t videoQueue;
	BOOL videoQueueRunning;
    
	AVCaptureSession *captureSession;
	AVCaptureDevice *videoDevice;
	AVCaptureVideoDataOutput *videoDataOutput;
    AVCaptureStillImageOutput *stillImageOutput;
    AVCaptureVideoPreviewLayer *previewLayer;
	
	dispatch_semaphore_t videoBufferSemaphore;
	BOOL bufferCreated;
	unsigned char *yData;
	
	size_t cameraFeedWidth;
	size_t cameraFeedHeight;
    
	UIView<LPAugmentedRealityView> *arView;
	LPAugmentedRealityOverlayView *overlayView;
	
	LPShowDialog *showDialog;
	
	BOOL needsPois;
	BOOL needsDetails;
    
    NSMutableDictionary *analyticsTimers;
	
	id lastClickedPOI;
}

#if defined(LPINTERNALBUILD)

@property (nonatomic, readonly) LPAugmentedRealityOverlayView *overlayView;

- (void)deviceOrientationChanged:(NSNotification*)notification;

#endif

- (BOOL)isBirdsEyeToggled;

/**
 * @brief Use this function to load a layer
 *
 * The layer @p layerName will be loaded and the POIs will be downloaded for the layer.
 * The @p oauthParameters dictionary must contain the consumer key and consumer secret required
 * by the layer. These must be added to @p oauthParameters using the LPConsumerKeyParameterKey
 * and LPConsumerSecretParameterKey respectively.
 * Any filter options for the layer that differ from the default values can be passed using the @p layerFilters dictionary.
 * The @p options parameter can be used to pass any options to the program.
 *
 * @param layerName The name of the layer to load
 * @param oauthParameters The oauth consumer key and consumer secret required by the layer.
 * These must be added using the LPConsumerKeyParameterKey and LPConsumerSecretParameterKey respectively.
 * @param parameters The layer filters/parameters to pass with the request. If nil or an empty dictionary the default values for all filters for the layer will be used.
 * @param options Options to pass to the program
 */
-(void)loadLayerWithName:(NSString*)layerName
		 oauthParameters:(NSDictionary*)oauthParameters
              parameters:(NSDictionary*)parameters
				 options:(LPOptions)options;

@end
