//
//  settViewController.m
//  vkMusicPlayer
//
//  Created by Дмитрий Богомолов on 09.04.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#import "settViewController.h"
#import <YandexSpeechKit/SpeechKit.h>

@interface settViewController ()<YSKSpeechRecognitionViewControllerDelegate>
@property(nonatomic, retain) YSKSpeechRecognitionViewController *recognizerViewController;
@end

@implementation settViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
- (IBAction)recogBtn:(id)sender {
    [self startSpeechRecognition];
}



- (void)startSpeechRecognition {
    self.recognizerViewController = [[YSKSpeechRecognitionViewController alloc] initWithLangauge:@"ru-RU" model:@"general"];
    self.recognizerViewController.delegate = self;
    
    [self presentViewController:self.recognizerViewController animated:YES completion:^{}];
    
    [self.recognizerViewController start];
}

- (void)speechRecognitionViewControllerDidCancel:(YSKSpeechRecognitionViewController *)speechRecognitionViewController
{
    UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"Error"
                                                    message:@"Recognition cancelled by user"
                                                   delegate:nil
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles: nil];
    [alert show];
    
    [self dismissViewControllerAnimated:YES completion:^{}];
    
    self.recognizerViewController = nil;
}

- (void)speechRecognitionViewController:(YSKSpeechRecognitionViewController *)speechRecognitionViewController didFinishWithResult:(NSString *)result
{
    [self.resultView setText:result];
    
    [self dismissViewControllerAnimated:YES completion:^{}];
    
    self.recognizerViewController = nil;
}

- (void) speechRecognitionViewController:(YSKSpeechRecognitionViewController *)speechRecognitionViewController didFailWithError:(YSKError *)error {
    [self.resultView setText:[error localizedDescription]];
    
    [self dismissViewControllerAnimated:YES completion:^{}];
    
    self.recognizerViewController = nil;
}










- (void)viewDidLoad
{
    [super viewDidLoad];
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
