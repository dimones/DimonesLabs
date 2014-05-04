//
//  songCell.h
//  vkMusicPlayer
//
//  Created by Дмитрий Богомолов on 23.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface songCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *artistLabel;
@property (weak, nonatomic) IBOutlet UILabel *durLabelCur;
@property (weak, nonatomic) IBOutlet UILabel *durLabelMax;
@property (weak, nonatomic) IBOutlet UIImageView *coverImage;
@property (weak, nonatomic) IBOutlet UILabel *titleLabel; 



@end
