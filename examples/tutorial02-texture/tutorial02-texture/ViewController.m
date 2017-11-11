//
//  ViewController.m
//  OpenGL-Texture
//
//  Created by Mr_zhang on 17/4/18.
//  Copyright © 2017年 Mr_zhang. All rights reserved.
//

#import "ViewController.h"
#import "MyOpenGLView.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    MyOpenGLView *myOpenGLView = [[MyOpenGLView alloc] initWithFrame:self.view.frame];
    [self.view addSubview:myOpenGLView];
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
