//
//  MusicListController.m
//  vkMusicPlayer
//
//  Created by Дмитрий Богомолов on 23.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#import "MusicListController.h"
#import "songCell.h"
#import "ViewController.h"
@interface MusicListController ()

@end

@implementation MusicListController
{
    NSMutableArray *nameArtist;
    NSMutableArray *title;
    NSMutableArray *maxduration;
    NSMutableArray *coverLinks;
    NSMutableArray *_tableData;
    NSMutableArray *songUrl;
    NSMutableArray *curDurArray;
    BOOL responsed;
    BOOL getImage;
    NSInteger curRow;
}
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
    }
    return self;
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Settings" style:UIBarButtonItemStyleDone target:self action:@selector(settings:)];
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"GET MUSIC =3" style:UIBarButtonItemStyleDone target:self action:@selector(getMusic:)];
    
    self.tableSongs.dataSource = self;
    self.tableSongs.delegate = self;
    _tableData = [[NSMutableArray alloc] init];
    VKRequestManager *rm = [[VKRequestManager alloc]
                            initWithDelegate:self
                            user:[VKUser currentUser]];
    
   [rm audioGet:@{
                   @"count"    : @"50"
                   }];
    //[rm audioGet:nil];
    
    title = [[NSMutableArray alloc] init];
    nameArtist = [[NSMutableArray alloc] init];
    songUrl = [[NSMutableArray alloc] init];
    maxduration = [[NSMutableArray alloc] init];
    curDurArray = [[NSMutableArray alloc] init];
    coverLinks = [[NSMutableArray alloc] init];
    if(responsed == true)
    {
        for(int i=0;i<[_tableData count];i++)
        {
            [nameArtist addObject:_tableData[i][@"artist"]];
            [maxduration addObject:_tableData[i][@"duration"]];
            [title addObject:_tableData[i][@"title"]];
            NSArray *tempArr = [_tableData[i][@"url"] componentsSeparatedByString:@"?"];
            [songUrl addObject:@[tempArr[0]]];
            
            //Parse url for cover image
            NSOperationQueue *queue =[[NSOperationQueue alloc]init];
            NSString *mainUrl = @"http://ws.audioscrobbler.com/2.0/?method=track.getInfo&api_key=25f6f1bea215239219597af58e4060a0&artist=";
            NSString *readyUrl = [NSString stringWithFormat:@"%@%@%@%@%@",mainUrl,nameArtist[i],@"&track=",title[i],@"&format=json"];
            NSString *finalUrl = [readyUrl stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding];
            NSURL *url = [NSURL URLWithString:finalUrl];
            NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
            
            
            [NSURLConnection sendAsynchronousRequest:request queue:queue completionHandler:^(NSURLResponse *response, NSData *respData, NSError *error){
                NSString *str = [[NSString alloc] initWithData:respData encoding:NSUTF8StringEncoding];
                @try {
                    NSDictionary *temp = [NSJSONSerialization JSONObjectWithData:respData options:1 error:nil];
                    NSDictionary *test = temp[@"track"];
                    NSDictionary *temp2 = test[@"album"];
                    NSDictionary *temp3 = temp2[@"image"];
                    NSArray *titles = [temp3 valueForKey:@"#text"];
                    [coverLinks addObject:titles[2]];
                }
                @catch (NSException *exception) {
                    NSLog(@"Don't find image");
                    [coverLinks addObject:@"blank.png"];
                }
            }];
        }
    }
    NSLog(@"LOADED");
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    NSLog(@"Low MEMORY");
}

-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (IBAction)playBtn:(id)sender {
    NSURL *url = [NSURL URLWithString:@"http://cs9-3v4.vk.me/p24/0b3d13df6f7fbe.mp3"];
    NSError *error;
    NSData *data = [NSData dataWithContentsOfURL:url];
    player = [[AVAudioPlayer alloc] initWithData:data error:&error];
    [player setNumberOfLoops:-1];
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayback error:nil];
    [[AVAudioSession sharedInstance] setActive: YES error: nil];
    [player prepareToPlay];
    [self.player play];
    
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    curRow = indexPath.row;    
}


-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return nameArtist.count;
}
-(UITableViewCell *) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    
    static NSString *CellIdentifier = @"SONG";
    songCell *Cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if(!Cell)
    {
        Cell = [[songCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier: CellIdentifier];
    }
    Cell.artistLabel.text = [nameArtist objectAtIndex:indexPath.row];
    Cell.titleLabel.text = [title objectAtIndex:indexPath.row];
  
    NSInteger temp = [maxduration  objectAtIndex:indexPath.row],i;
    while(temp>60)
    {
        temp/=60;
        i++;
    }
    NSInteger tempp =[maxduration  objectAtIndex:indexPath.row];
    NSInteger temp2 =tempp-60*i;
    i=0;
    NSString *maxDur = [NSString stringWithFormat:@"%d/%d",i,temp2];
    Cell.durLabelMax.text = maxDur;
    if([coverLinks containsObject:@"blank.png"])
           Cell.coverImage.image = [UIImage imageNamed:@"blank.png"];
    else
    {
        Cell.coverImage.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:[coverLinks objectAtIndex:indexPath.row]]]];}
    return Cell;
}

- (void) settings:(id) sender {
    NSLog(@"sett pressed");
    [self performSegueWithIdentifier:@"SETT_WORK" sender:self];
}
- (void) getMusic:(id) sender {
    NSLog(@"getMusic pressed =3");
    [_tableSongs reloadData];
 
    
}

- (void)VKRequest:(VKRequest *)request response:(id)response
{
    _tableData = response[@"response"];
    responsed = true;
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
