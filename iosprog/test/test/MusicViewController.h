//
//  MusicViewController.h
//  test
//
//  Created by Дмитрий Богомолов on 31.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MusicViewController : UIViewController<UITableViewDataSource,UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableSongs;
@property (strong, nonatomic) IBOutlet UIView *progressBar;
@property (retain, nonatomic) NSMutableData *receivedData;


@end
