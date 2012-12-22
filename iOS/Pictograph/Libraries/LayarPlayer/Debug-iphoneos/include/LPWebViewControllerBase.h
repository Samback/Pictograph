//
//  LPWebViewControllerBase.h
//  Layar
//
//  Created by Lawrence Lee on 7/23/10.
//  Copyright 2010 Layar B.V. All rights reserved.
//

//System imports
#import <UIKit/UIKit.h>

@interface LPWebViewControllerBase : UIViewController <UIWebViewDelegate>
{
	UIWebView *webView;
	UIActivityIndicatorView *activityIndicator;
}

@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *activityIndicator;

@end
