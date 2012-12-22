//
//  LPClassicBIW.h
//  layarplayerinternal
//
//  Created by shy on 7/12/11.
//  Copyright 2011 Layar. All rights reserved.
//

//Local imports
#import "LPBIW.h"

@interface LPClassicBIW : LPBIW
{
	id <LPBIWDelegate> delegate;
}

@property (nonatomic, assign) id <LPBIWDelegate> delegate;

//- (void)focusedPoiUpdated:(NSNotification*)notification;

@end
