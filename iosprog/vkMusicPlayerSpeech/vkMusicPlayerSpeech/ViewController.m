//
//  ViewController.m
//  vkMusicPlayerSpeech
//
//  Created by Дмитрий Богомолов on 31.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

static NSString *const NEXT_CONTROLLER_SEGUE_ID = @"START_WORK";

@implementation ViewController
{
    UIWebView *_webView;
}
- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}




- (IBAction)btn_login:(id)sender
{
    CGRect frame = [[UIScreen mainScreen] bounds];
    _webView = [[UIWebView alloc] initWithFrame:frame];
    [self.view addSubview:_webView];
    
    
    if([VKUser currentUser].accessToken.token!=nil)
    {
        _webView.hidden=YES;
        [self performSegueWithIdentifier:NEXT_CONTROLLER_SEGUE_ID sender:self];
    }
    else {
        _webView.hidden=NO;
        [[VKConnector sharedInstance] startWithAppID:@"4258201"
                                          permissons:@[@"audio"]
                                             webView:_webView
                                            delegate:self];
    }
}

- (IBAction)btn_clear_acc:(id)sender {
}





@end
