//
//  settVIewController.m
//  vkMusicPlayer
//
//  Created by Дмитрий Богомолов on 23.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#import "settVIewController.h"
#import "ViewController.h"
@interface settVIewController ()

@end

@implementation settVIewController
@synthesize tokenbox;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
- (IBAction)cleanVK:(id)sender {
    [[VKStorage sharedStorage] clean];
    [[VKConnector sharedInstance] clearCookies];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    tokenbox.text = [VKUser currentUser].accessToken.token;
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
