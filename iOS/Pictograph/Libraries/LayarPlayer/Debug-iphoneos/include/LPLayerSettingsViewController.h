//
//  LPLayerSettingsViewController.h
//  layarplayer
//
//  Created by Lawrence Lee on 11/10/10.
//  Copyright (c) 2010 Layar B.V. All rights reserved.
//

//System imports
#import <UIKit/UIKit.h>

//Local imports
#import "LPCachingViewController.h"
#import "LPSearchBoxCellView.h"

#if !defined(LPINTERNALBUILD) && !defined(WHITELABEL)

@interface LPAboutLayarLabel : UILabel

@end

@interface LPAboutLayarControl : UIControl
{
	LPAboutLayarLabel *label;
}

@property (nonatomic, retain) LPAboutLayarLabel *label;

@end

#endif

@interface BirdsEysTableViewCell : UITableViewCell
{
	UISwitch *switchBox;
}

@property (nonatomic, retain) UISwitch *switchBox;

@end


@class LSLayer;

@class LPLayerSettingsViewController;

@protocol LPLayerSettingsViewControllerDelegate <NSObject>

- (void)layerSettingsViewControllerCancelled:(LPLayerSettingsViewController*)viewController forceRefresh:(BOOL)force;
- (void)layerSettingsViewControllerDone:(LPLayerSettingsViewController*)viewController;

/**
 * @brief Get back to app callback
 */
- (void)webViewControllerGetBackToApp:(NSDictionary*)userInfo;

/**
 * @brief Respond to load layer intent
 */
- (void)webViewControllerLoadLayer:(NSDictionary*)userInfo;

@end
    
@interface LPLayerSettingsViewController : LPCachingViewController <UITableViewDelegate, UITableViewDataSource, LPSearchBoxCellViewDelegate>
{
	id <LPLayerSettingsViewControllerDelegate> delegate;
	LSLayer *layer;
	NSArray *filters;
	NSString *countryCode;
	NSString *localCountryCode;
    UITableView *tableViewHelper;
	UIBarButtonItem *cancel;
	UIBarButtonItem *done;
	
	NSIndexPath *activeTextFieldIndexPath;
	BOOL keyboardVisible;
}

@property (nonatomic, assign) id <LPLayerSettingsViewControllerDelegate> delegate;
@property (nonatomic, retain) LSLayer *layer;
@property (nonatomic, readonly) NSArray *filters;
@property (nonatomic, copy) NSString *countryCode;
@property (nonatomic, copy) NSString *localCountryCode;

- (void)cancel;
- (void)done;

@end
