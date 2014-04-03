//
//  MusicViewController.m
//  test
//
//  Created by Дмитрий Богомолов on 31.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#import "MusicViewController.h"
#import "songCell.h"
#import "ODRefreshControl.h"
#import "ViewController.h"
@interface MusicViewController ()

@end

@implementation MusicViewController
{
    BOOL responsed;
    NSMutableArray *_tableData;
    NSMutableArray *nameArtist;
    NSMutableArray *title;
    NSMutableArray *songUrl;//URI SONG
    NSInteger curRow;//for select song
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    ODRefreshControl *refreshControl = [[ODRefreshControl alloc] initInScrollView:self.tableSongs];
    [refreshControl addTarget:self action:@selector(dropViewDidBeginRefreshing:) forControlEvents:UIControlEventValueChanged];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Settings" style:UIBarButtonItemStyleDone target:self action:@selector(settings:)];
    self.tableSongs.dataSource = self;
    self.tableSongs.delegate = self;
    VKRequestManager *rm = [[VKRequestManager alloc]
                            initWithDelegate:self
                            user:[VKUser currentUser]];
    
    [rm audioGet:@{
                   @"count"    : @"250"
                   }];
    
    [rm startAllRequestsImmediately];
    title = [[NSMutableArray alloc] init];
    nameArtist = [[NSMutableArray alloc] init];
    songUrl = [[NSMutableArray alloc] init];
    if(responsed)
    {
        for(int i=0;i<[_tableData count];i++)
        {
            [nameArtist addObject:_tableData[i][@"artist"]];
            [title addObject:_tableData[i][@"title"]];
            NSArray *tempArr = [_tableData[i][@"url"] componentsSeparatedByString:@"?"];
            [songUrl addObject:@[tempArr[0]]];
        }
    }
    NSLog(@"LOADED");
}
- (void)VKRequest:(VKRequest *)request response:(id)response
{
    _tableData = response[@"response"];
    responsed = true; }
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void) settings:(id) sender {
    NSLog(@"sett pressed");
    [self performSegueWithIdentifier:@"SETT_WORK" sender:self];
}
- (void)dropViewDidBeginRefreshing:(ODRefreshControl *)refreshControl
{
    double delayInSeconds = 3.0;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, delayInSeconds * NSEC_PER_SEC);
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [refreshControl endRefreshing];
        [_tableSongs reloadData];
    });
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
    return Cell;
}

@end
