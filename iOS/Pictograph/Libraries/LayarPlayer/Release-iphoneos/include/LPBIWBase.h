//
//  LPBIWBase.h
//  layarplayer
//
//  Created by Lawrence Lee on 10/23/10.
//  Copyright (c) 2010 Layar B.V. All rights reserved.
//

//System imports
#import <UIKit/UIKit.h>


#define LPBIW_BANNER_LABEL_HEIGHT		26.0f
#define BANNERFONT						[UIFont fontWithName:@"Helvetica-Bold" size:15.0f]


@class LPBIWBase;

@protocol LPBIWDelegate <NSObject>

- (void)biwClicked:(LPBIWBase *)biw;

@end


@class LSPOI;
@class LCImageManager;

@interface LPBIWBase : UIView
{
	LSPOI *poi;
	UIView *container;
	UIView *poiContainer;
	UIView *bannerView;
	UILabel *bannerLabel;
}

@property (nonatomic, retain) LSPOI *poi;
@property (nonatomic, retain) UIView *container;
@property (nonatomic, retain) UIView *poiContainer;
@property (nonatomic, retain) UIView *bannerView;
@property (nonatomic, retain) UILabel *bannerLabel;
@property (nonatomic, retain) LCImageManager *imageManager;

@end
