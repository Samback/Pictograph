//
//  LPShowDialog.h
//  layarplayer
//
//  Created by Nikita Ivanyushchenko on 01/25/11.
//  Copyright (c) 2011 Layar B.V. All rights reserved.
//

//System imports
#import <UIKit/UIKit.h>

#define LPShowDialogActionFired	@"LPShowDialogActionFired"


@class LPShowDialog;

@protocol LPShowDialogDelegate <NSObject>
- (void)showDialogWillClose:(LPShowDialog*)aShowDialog;
@end


@class LSAction;
@class LSShowDialogData;
@class LCImageManager;
@class LPCloseButton;
@class LPExtendedBIWButtonContainer;

@interface LPShowDialog : UIView <UIActionSheetDelegate>
{	
	LSShowDialogData *showDialogData;

	UILabel *titleLabel;
	UILabel *descriptionLabel;
	UIImage *placeholder;
	UIImageView *imageView;
	
	NSArray *moreActions;
	
	UIView *centerContainer;
	LPCloseButton *closeButton;
	LPExtendedBIWButtonContainer * buttonContainer;
	
	id<LPShowDialogDelegate> delegate;
		
	UIWindow * backWindow; // It is suposed that no other windows management is done while dialog is shown (between calls to setShowDialogData: and close).
}
@property (nonatomic, assign) id<LPShowDialogDelegate> delegate;
@property (nonatomic, retain) LCImageManager *imageManager;


- (id)init;
- (void)setShowDialogData:(LSShowDialogData*)aShowDialogData;
- (void)close;

@end
