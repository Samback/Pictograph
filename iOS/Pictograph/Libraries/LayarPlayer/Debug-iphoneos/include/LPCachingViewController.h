//
//  LPCachingViewController.h
//  layarplayerinternal
//
//  Created by Matteo Manferdini on 06/12/11.
//  Copyright (c) 2011 Layar. All rights reserved.
//

#import <UIKit/UIKit.h>

@class LCImageManager;
@class LCResourceManager;

@interface LPCachingViewController : UIViewController

@property (nonatomic, retain) LCImageManager *imageManager;
@property (nonatomic, retain) LCResourceManager *resourceManager;

@end
