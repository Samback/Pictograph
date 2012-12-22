//
//  LPStatusView.h
//  layarplayer
//
//  Created by Lawrence Lee on 11/17/10.
//  Copyright (c) 2010 Layar B.V. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface LPStatusMessage : NSObject
{
    BOOL showActivity;
	NSString *message;
}

@property (nonatomic, assign) BOOL showActivity;
@property (nonatomic, copy) NSString *message;

+ (LPStatusMessage*)statusMessage:(NSString*)text showActivity:(BOOL)activity;

@end

@protocol LPStatusViewDelegate <NSObject>

- (int)numberOfObjectsForStatusView;
- (int)numberOfPOIsForStatusView;

@end

@interface LPStatusView : UIView
{
	id <LPStatusViewDelegate> delegate;
	NSString *errorMessage;
	LPStatusMessage *message;
	UIActivityIndicatorView *activityView;
	UILabel *messageLabel;
	NSTimeInterval timeOfLastMessageUpdate;
	
	UIColor *glowColor;
}

@property (nonatomic, assign) id <LPStatusViewDelegate> delegate;
@property (nonatomic, copy) NSString *errorMessage;
@property (nonatomic, retain) LPStatusMessage *message;
@property (nonatomic, retain) NSString *messageText;

- (id)initWithFrame:(CGRect)frame activityIndicatorCenter:(CGPoint)activityIndicatorCenter;

- (void)setActivityIndicatorCenter:(CGPoint)activityIndicatorCenter;

@end
