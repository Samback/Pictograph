//
//  LPBIW.h
//  layarplayer
//
//  Created by Lawrence Lee on 10/23/10.
//  Copyright (c) 2010 Layar B.V. All rights reserved.
//

#import "LPBIWBase.h"

#define LPBIW_HEIGHT					100.0f
#define LPBIW_BANNER_ICON_VIEW_HEIGHT	26.0f
#define LPBIW_BANNER_ICON_VIEW_WIDTH	60.0f
#define LINEFONT						[UIFont fontWithName:@"Helvetica" size:12.0f]

@interface LPBIW : LPBIWBase 
{
	UIImageView *bannerIconView;
	UIImageView *imageView;
	UILabel *description;
	UILabel *footnote;
	UIImage *placeholder;
}

@property (nonatomic, retain) UIImageView *bannerIconView;
@property (nonatomic, retain) UIImageView *imageView;
@property (nonatomic, retain) UILabel *description;
@property (nonatomic, retain) UILabel *footnote;
@property (nonatomic, retain) UIImage *placeholder;


@end
