//
//  LayarPlayerDelegate.h
//  layarplayer
//
//  Created by Lawrence Lee on 11/26/10.
//  Copyright 2010 Layar. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol LayarPlayerDelegate <NSObject>

@optional

- (void)layarPlayerWillClose;
- (void)layarPlayerDidClose;

@end
