//
//  LPExtendedBIW.h
//  layarplayer
//
//  Created by Lawrence Lee on 11/13/10.
//  Copyright (c) 2010 Layar B.V. All rights reserved.
//

#import "LPClassicBIW.h"

#define LPExtendedBIWActionFired	@"LPExtendedBIWActionFired"

@class LSAction;

@interface LPExtendedBIWButton : UIControl
{
	LSAction *action;
	UIImageView *imageView;
	UILabel *title;
	UIColor *color;
	UIColor *highlightedColor;
	float leftBorderWidth;
	UIColor *leftBorderColor;
	float rightBorderWidth;
	UIColor *rightBorderColor;
	BOOL drawHighlighted;
}

@property (nonatomic, retain) LSAction *action;
@property (nonatomic, readonly) UIImageView *imageView;
@property (nonatomic, readonly) UILabel *title;
@property (nonatomic, retain) UIColor *color;
@property (nonatomic, retain) UIColor *highlightedColor;
@property (nonatomic, assign) float leftBorderWidth;
@property (nonatomic, retain) UIColor *leftBorderColor;
@property (nonatomic, assign) float rightBorderWidth;
@property (nonatomic, retain) UIColor *rightBorderColor;

@end

@interface LPExtendedBIWButtonShelf : UIView
{

}

@end

@class CAGradientLayer;

@interface LPExtendedBIWButtonContainer : UIView
{
	CAGradientLayer *shadowGradient;
}

@end

@class LPExtendedBIW;

@protocol LPExtendedBIWDelegate <NSObject>

- (void)extendedBiwShowMoreActions:(NSArray*)actions;
- (void)extendedBiwWillClose:(LPExtendedBIW*)extendedBiw;

@end

@class LPCloseButton;

@interface LPExtendedBIW : LPBIW
{
	id <LPExtendedBIWDelegate> delegate;
	UILabel *distance;
	LPCloseButton *closeButton;
	UIView *buttonContainer;
	NSArray *moreActions;
}

@property (nonatomic, assign) id <LPExtendedBIWDelegate> delegate;

- (void)actionFired:(id)sender;
- (void)moreActionsFired:(id)sender;
- (void)close;

@end
