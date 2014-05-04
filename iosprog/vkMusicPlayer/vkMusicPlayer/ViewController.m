//
//  ViewController.m
//  vkMusicPlayer
//
//  Created by Дмитрий Богомолов on 22.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end
NSString *token;
static NSString *const NEXT_CONTROLLER_SEGUE_ID = @"START_WORK";
@implementation ViewController
{
    UIWebView *_webView;
}
- (void)viewDidLoad
{
    //[self performSegueWithIdentifier:NEXT_CONTROLLER_SEGUE_ID sender:self];
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    
}
- (IBAction)loginBtn:(id)sender {
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
- (IBAction)cleanBtn:(id)sender {
    [[VKStorage sharedStorage] clean];
    [[VKConnector sharedInstance] clearCookies];
}
#pragma mark - VKConnectorDelegate

- (void)        VKConnector:(VKConnector *)connector
accessTokenRenewalSucceeded:(VKAccessToken *)accessToken
{
    NSLog(@"OK: %@", accessToken);
    _webView.hidden = YES;
    [self performSegueWithIdentifier:NEXT_CONTROLLER_SEGUE_ID sender:self];
}

- (void)VKRequest:(VKRequest *)request response:(id)response
{
    NSLog(@"response: %@", response);
}

- (void)     VKConnector:(VKConnector *)connector
accessTokenRenewalFailed:(VKAccessToken *)accessToken
{
    NSLog(@"User denied to authorize app.");
}

- (void)   VKConnector:(VKConnector *)connector
connectionErrorOccured:(NSError *)error
{
    NSLog(@"Connection error!");
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end