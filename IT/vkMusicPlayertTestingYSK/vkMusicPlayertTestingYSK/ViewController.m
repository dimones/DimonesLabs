//
//  ViewController.m
//  vkMusicPlayertTestingYSK
//
//  Created by Дмитрий Богомолов on 09.04.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#import "ViewController.h"

@interface ViewController () <YSKRecognizerDelegate>
{
    YSKRecognizer *recognizer;
    YSKRecognition *result;
}

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    if (self) {
        [[YSKSpeechKit sharedInstance] configureWithAPIKey:@"21a3c568-00c9-4bdb-9543-01672a3ca357"];
    }
	// Do any additional setup after loading the view, typically from a nib.
}
- (IBAction)start:(id)sender {
    NSLog(@"Start button pressed");
    if (result) {
        result = nil;
    }
    
    self->recognizer = [[YSKRecognizer alloc] initWithLanguage:@"ru-RU" model:@"general"];
    self->recognizer.delegate = self;
    
    [recognizer start];
    
}


- (IBAction)stop:(id)sender {
    
    
}


- (IBAction)cancelBtn:(id)sender {
    
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
