//
//  AugmentedRealityViewBase.h
//  LayarPlayer
//
//  Created by Nikita Ivaniushchenko on 7/3/11.
//  Copyright (c) 2011 Layar B.V. All rights reserved.
//

//System imports

#import <OpenGLES/ES1/gl.h>
#import <UIKit/UIKit.h>
#import <LSConstants.h>

typedef enum LPARRenderingMode
{
	AR_RENDERING_MODE_GEO,
	AR_RENDERING_MODE_FEATURE_TRACKING
} LPARRenderingMode;

@class CLHeading;
@class CLLocation;
@class EAGLContext;

@class LSPOIModel;
@class LS1DRenderable;
@class LSGeoObjectsRenderer;
@class LSTrackableObjectsRenderer;
@class LSRadarRenderer;
@class LSGridRenderer;
@class LSLayer;
@class LSRenderableManager;
@class LSTexture2D;
@class LSARObjectRenderable;
@class LSARGeoObjectRenderable;
@class LSARTrackableObjectRenderable;

@class LCTrackingManager;
@class LCResourceManager;

#define LPAugmentedRealityViewFPSNotification			@"LPAugmentedRealityViewFPSNotification"
#define LPAugmentedRealityViewFPS						@"LPAugmentedRealityViewFPS"

#define kAccelerometerSmoothing							0.9f
#define kMagnetometerSmoothing							0.95f
//#define kMagnetometerSmoothing							0.5f
#define kSLEPRSmoothing									0.99f

#define LPAugmentedRealityViewUpdatedFocusedRenderable	@"LPAugmentedRealityViewUpdatedFocusedRenderable"

@protocol LPAugmentedRealityView <NSObject>

@property (nonatomic, readonly) dispatch_semaphore_t renderingSemaphore;
@property (nonatomic, readonly) NSArray *deletedRenderables;
@property (nonatomic, assign) LPARRenderingMode renderingMode;
@property (nonatomic, retain) LSRenderableManager *renderableManager;
@property (nonatomic, retain) LSLayer *lslayer;
@property (nonatomic, assign) LSPOIModel *model;
@property (nonatomic, assign) UIDeviceOrientation deviceOrientation;
@property (nonatomic, readonly) GLint backingWidth;
@property (nonatomic, readonly) GLint backingHeight;
@property (nonatomic, retain) CLLocation *location;
@property (nonatomic, assign) LSGeolocation fixedLocation;
@property (nonatomic, assign) BOOL useFixedLocation;
@property (nonatomic, readonly, getter=isUsingDeviceMotion) BOOL usingDeviceMotion;
@property (nonatomic, assign) BOOL showGrid;
@property (nonatomic, readonly) LSGeoObjectsRenderer *geoObjectsRenderer;
@property (nonatomic, readonly) LSTrackableObjectsRenderer *trackableObjectsRenderer;
@property (nonatomic, retain) LSRadarRenderer *radar;
@property (nonatomic, retain) LSGridRenderer *grid;
@property (nonatomic, assign) BOOL showRadar;
@property (nonatomic, readonly) EAGLContext *mainContext;
@property (nonatomic, retain) LCTrackingManager *trackingManager;
@property (nonatomic, retain) LCResourceManager *resourceManager;

- (BOOL)initialize;
- (void)bindResources;
- (void)unbindResources;
- (void)startAnimating;
- (void)pauseAnimating;
- (void)stopAnimating;
- (void)drawView;
- (void)updateRadar;

- (LSMatrix4&)projectionMatrix;
- (LSMatrix4&)modelViewMatrix;

/**
 * @brief This function creates a CIW image resource.
 * @param color The inner color of the image resource
 * @return The billboard renderable for the image resource
 */
- (LS1DRenderable*)createCIWRenderableWithColor:(LSColor)color;

/**
 * @brief Calculate the update animations for POI renderables
 * @param poiRenderables The POI renderables to calculate the update animations for
 * @param originalRenderables The original POI renderables 
 */
- (void)calculateUpdateAnimationsForRenderables:(NSArray*)poiRenderables withOriginalRenderables:(NSArray*)originalRenderables;

/**
 * @brief Calculate the grid positions of POI renderables
 * @param poiRenderables The POI renderables to calculate the grid positions for
 */
- (void)calculatePOIRenderablePositionsForRenderables:(NSArray*)poiRenderables;

/**
 * @brief Update the resource for a POI renderable
 *
 * @param poiRenderable The POI renderable for which to update the resouce
 */
//- (void)updateRenderableResources:(LSARObjectRenderable*)poiRenderable;

/**
 * @brief Update the resources for multiple POI renderables
 *
 * @param poiRenderables The POI renderables to update the resources for
 */
//- (void)updateResourcesForRenderables:(NSArray*)poiRenderables;

/**
 * @brief Update the resources for multiple POI renderables
 *
 * @param poiRenderables The POI renderables to update the resources for
 */
- (void)updateResourcesForARGeoRenderables:(NSArray*)renderables;

/**
 * @brief Update the resource for a POI renderable
 *
 * @param poiRenderable The POI renderable for which to update the resouce
 */
- (void)updateARGeoObjectRenderableResources:(LSARGeoObjectRenderable*)geoRenderable;

/**
 * @brief Update the resources for multiple POI renderables
 *
 * @param poiRenderables The POI renderables to update the resources for
 */
- (void)updateResourcesForARTrackableRenderables:(NSArray*)renderables;

/**
 * @brief Update the resource for a POI renderable
 *
 * @param poiRenderable The POI renderable for which to update the resouce
 */
- (void)updateARTrackableObjectRenderableResources:(LSARTrackableObjectRenderable*)trackingRenderable;

/**
 * @brief Start device motion updates
 *
 * Call this when the view becomes visible
 */
- (void)startDeviceMotionUpdates;

/**
 * @brief Stop device motion updates
 *
 * Call this when the view disappears
 */
- (void)stopDeviceMotionUpdates;

- (void)setHeadingVector:(CLHeading*)newHeading;

/**
 * @brief Calculates view matrix using sensors`data
 *
 * @param matrix The matrix to save result to
 */
- (void)calculateModelViewMatrix:(LSMatrix4*)matrix;

/**
 * @brief Deleting a POI renderable using the onDelete animation
 */
- (void)animatedDeletePOIRenderable:(LSARObjectRenderable*)poiRenderable;

- (void)calculateTriggeredActionForARObject;

/**
 * @brief get the POI renderable at given coordinates
 */
- (LSARObjectRenderable*)getPOIRenderableAtCoordinatesWithX:(int)x andY:(int)y;

// for screenshot making purpose
- (void)setProjectionMatrixParameters:(int)surfaceWidth surfaceHeight:(int)surfaceHeight fx:(float)fx fy:(float)fy cx:(float)cx cy:(float)cy;

- (void)updateProjectionMatrixWithRenderingMode:(LPARRenderingMode)aRenderingMode;

@end
