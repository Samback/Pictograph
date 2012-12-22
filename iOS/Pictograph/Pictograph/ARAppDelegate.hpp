//
//  ARAppDelegate.h
//  Pictograph
//
//  Created by Max on 22.12.12.
//  Copyright (c) 2012 Max Tymchii. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@interface ARAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
- (void)startUpdatePosition;
- (void)finishUpdatePosition;
- (CLLocation *)getCurrentLocation;
@end
