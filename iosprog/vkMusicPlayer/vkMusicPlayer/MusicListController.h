//
//  MusicListController.h
//  vkMusicPlayer
//
//  Created by Дмитрий Богомолов on 23.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVPlayer.h>
#import <AVFoundation/AVAudioPlayer.h>
#import <AVFoundation/AVFoundation.h>

@interface MusicListController : UIViewController <UITableViewDataSource,UITableViewDelegate,NSURLConnectionDelegate,AVAudioPlayerDelegate>
{
    AVAudioPlayer *player;
}
@property (nonatomic, retain) AVAudioPlayer *player;
@property (weak, nonatomic) IBOutlet UITableView *tableSongs;
@property (weak, nonatomic) IBOutlet UIButton *playButton;
@property (strong, nonatomic) IBOutlet UIView *progressBar;
@property (retain, nonatomic) NSMutableData *receivedData;
@property (retain, nonatomic) NSURLConnection *connection;

@end
