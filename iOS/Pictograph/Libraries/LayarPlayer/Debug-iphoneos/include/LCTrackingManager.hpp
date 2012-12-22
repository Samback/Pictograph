//
//  LCTrackingManager.hpp
//  LayarCommon
//
//  Created by Lawrence Lee on 8/18/11.
//  Copyright 2011 Layar B.V. All rights reserved.
//

//Standard Library includes
#include <vector>

//System imports
#import <Foundation/Foundation.h>

@class LCFeatureSet;
@class LCTrackingManager;

namespace helios
{
	namespace img
	{
		template <typename T> class Image;
	}
	
	namespace tracking
	{
		struct TargetDetectionResult;
		class TargetDetector;
		class TargetDetectionController;
	}
}

@protocol LCTrackingManagerDelegate <NSObject>

@optional
- (void)targetDetectorDetectedNewTarget;
- (void)targetDetectorLostTrackOfTarget;

- (void)targetDetectorDetectedFeatureSet:(LCFeatureSet*)featureSet withDetectionResult:(const helios::tracking::TargetDetectionResult&)detectionResult;

- (void)trackingManager:(LCTrackingManager*)trackingManager willAddTargetFingerprintForURL:(NSString*)url;
- (void)trackingManager:(LCTrackingManager*)trackingManager didAddTargetFingerprintForURL:(NSString*)url;
- (void)trackingManager:(LCTrackingManager*)trackingManager willRemoveTargetFingerprintForURL:(NSString*)url;
- (void)trackingManager:(LCTrackingManager*)trackingManager didRemoveTargetFingerprintForURL:(NSString*)url;

@end

@interface LCTrackingManager : NSObject
{
	id<LCTrackingManagerDelegate> delegate;
	
    helios::tracking::TargetDetector* targetDetector_;
	helios::tracking::TargetDetectionController* targetDetectionController_;
	std::vector<helios::tracking::TargetDetectionResult>* detectionResults_;
	dispatch_queue_t targetDetectorQueue;
	
	NSMutableDictionary *featureSets_;
}

@property (nonatomic, assign) id<LCTrackingManagerDelegate> delegate;
@property (nonatomic, readonly) dispatch_queue_t targetDetectorQueue;
@property (nonatomic, readonly) NSDictionary *featureSets;

- (helios::tracking::TargetDetector&)targetDetector;
- (helios::tracking::TargetDetectionController&)targetDetectionController;

#pragma mark - Target fingerprint management
- (LCFeatureSet*)addTargetFingerprint:(NSData*)targetFingerprint forURL:(NSString*)url;
- (void)removeTargetFingerprintForURL:(NSString*)url;
- (LCFeatureSet*)featureSetForURL:(NSString*)url;

#pragma mark - Target Detection
- (void)detectTargets:(helios::img::Image<unsigned char>*)imL :(helios::img::Image<unsigned char>*)imV :(helios::img::Image<unsigned char>*)imU :(dispatch_semaphore_t)semaphore;

@end
