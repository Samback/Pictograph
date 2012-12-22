//
//  LPAugmentedRealityDetailsView.h
//  layarplayerinternal
//
//  Created by Yuriy Shevchuk on 9/7/11.
//  Copyright 2011 Layar. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * @brief Delegate protocol which provides LPAugmentedRealityDetailsView with needed info.
 */

@protocol LPAugmentedRealityDetailsViewDelegate <NSObject>

- (float)accuracyForDetailsView;
- (float)rangeForDetailsView;
- (CGPoint)latLonForDetailsView;

@end

/**
 * @brief View to show detailed information of current layer. Shows accuracy, range and geoposition.
 */
@interface LPAugmentedRealityDetailsView : UIView
{
    CGFloat pinX;
    UILabel *detailsLabel;
    
    NSTimer *timer;
    
    id<LPAugmentedRealityDetailsViewDelegate> delegate;
}

/**
 * @brief X axis coordinate to display center of arrow. Setting this property causes view to redraw itself.
 */
@property (nonatomic, assign) CGFloat pinX;

/**
 * @brief Message to display in view. Has to be properly formated with '\n' for 3 lines. 
 */
@property (nonatomic, retain) NSString *detailsMessage;

/**
 * @brief Delegate which provides info.
 */
@property (nonatomic, assign) id<LPAugmentedRealityDetailsViewDelegate> delegate;

@end
