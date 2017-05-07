//
//  GLViewController.m
//  MacZarch
//
//  Created by Kai Hergenröther on 07.05.17.
//  Copyright © 2017 Kai Hergenröther. All rights reserved.
//

#import "GLViewController.h"

#include <memory>
#include <kxm/Zarch/Zarch.h>
#include <kxm/Zarch/ControlsState.h>
#import "GLView.h"

using namespace std;
using namespace kxm::Zarch;

@interface GLViewController () {
    shared_ptr<Zarch>         zarch;
    shared_ptr<ControlsState> controlsState;
    NSTimer                   *timer;
}

@end

@implementation GLViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    zarch         = make_shared<Zarch>();
    controlsState = make_shared<ControlsState>();
    [(GLView *)self.view setZarch: zarch controlsState: controlsState];
    
    timer = [NSTimer timerWithTimeInterval: 1.0/60.0 target: self selector: @selector(handleTimer) userInfo: nil repeats: YES];
    [[NSRunLoop currentRunLoop] addTimer: timer forMode: NSDefaultRunLoopMode];
}


- (void)handleTimer {
    ((GLView *)self.view).needsDisplay = YES;
}

@end
