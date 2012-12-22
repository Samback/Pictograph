//
//  LPViewController.h
//  layarplayer
//
//  Created by Lawrence Lee on 11/5/10.
//  Copyright (c) 2010 Layar B.V. All rights reserved.
//

//Local imports
#import "LPViewControllerBase.h"

@class LSPOIModel;
@class LSLayer;
@class LSRequest;

@class LPPopupView;

@interface LPViewController : LPViewControllerBase
{
	UIView *header;
	UILabel *layerTitle;
	UIImageView *bannerIconView;
	
	UIToolbar *toolbar;
	UIBarButtonItem *infoButton;
	UIBarButtonItem *actionButton;
	UIBarButtonItem *selectView;
	UIBarButtonItem *closeButton;
	LPPopupView *popupView;
	
	BOOL showGrid;
}

@property (nonatomic, retain) UIView *header;
@property (nonatomic, retain) UIToolbar *toolbar;
@property (nonatomic, retain) UIBarButtonItem *infoButton;
@property (nonatomic, retain) UIBarButtonItem *actionButton;
@property (nonatomic, retain) UIBarButtonItem *selectView;
@property (nonatomic, retain) UIBarButtonItem *closeButton;

- (void)createToolbarWithFrame:(CGRect)frame andImageData:(NSData*)imageData;
- (void)releaseViews;

@end
