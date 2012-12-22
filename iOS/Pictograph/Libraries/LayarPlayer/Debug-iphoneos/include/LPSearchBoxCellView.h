//
//  SearchBoxCellView.h
//  layar
//
//  Created by Lawrence Lee on 2/4/10.
//  Copyright 2010 Layar BV. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol LPSearchBoxCellViewDelegate <NSObject>

- (void)searchboxEditingBegan:(id)sender;

@end

@class LSTextboxFilter;

@interface LPSearchBoxCellView : UITableViewCell
{
	id<LPSearchBoxCellViewDelegate> delegate;
	LSTextboxFilter *textboxFilter;
	UITextField *searchBox;
}

@property (nonatomic, assign) id<LPSearchBoxCellViewDelegate> delegate;
@property (nonatomic, retain) LSTextboxFilter *textboxFilter;
@property (nonatomic, readonly) UITextField *searchBox;

@end
