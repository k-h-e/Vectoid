//
//  GLViewController.m
//  MacZarch
//
//  Created by Kai Hergenröther on 07.05.17.
//  Copyright © 2017 Kai Hergenröther. All rights reserved.
//

#import "GLViewController.h"

#include <memory>
#import <GameController/GameController.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/Zarch.h>
#include <kxm/Zarch/ControlsState.h>
#import "GLView.h"


using namespace std;
using namespace kxm::Vectoid;
using namespace kxm::Zarch;

@interface GLViewController () {
    shared_ptr<Zarch>         zarch;
    shared_ptr<ControlsState> controlsState;
    NSTimer                   *timer;
    bool                      haveGamePad;
    GCControllerAxisInput     *xAxis,      // Valid <=> haveGamePad.
                              *yAxis;      // Valid <=> haveGamePad.
    GCControllerButtonInput   *buttonA,    // Valid <=> haveGamePad.
                              *buttonB;    // Valid <=> haveGamePad.
}

@end

@implementation GLViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    zarch         = make_shared<Zarch>();
    controlsState = make_shared<ControlsState>();
    [(GLView *)self.view setZarch: zarch controlsState: controlsState];
    
    timer = [NSTimer timerWithTimeInterval: 1.0/60.0 target: self selector: @selector(handleTimer) userInfo: nil
                     repeats: YES];
    [[NSRunLoop currentRunLoop] addTimer: timer forMode: NSDefaultRunLoopMode];
}


- (void)handleTimer {
    if (haveGamePad) {
        float x = xAxis.value,
              y = yAxis.value;
        controlsState->orientation = Vector(x, y, 0.0f);
        controlsState->thruster    = buttonB.pressed;
        controlsState->trigger     = buttonA.pressed;
    }
    else {
        NSArray<GCController *> *controllers = [GCController controllers];
        if (controllers.count) {
            GCExtendedGamepad *gamePad = controllers[0].extendedGamepad;
            if (gamePad) {
                if (gamePad.leftThumbstick) {
                    xAxis = gamePad.leftThumbstick.xAxis;
                    yAxis = gamePad.leftThumbstick.yAxis;
                }
                buttonA = gamePad.buttonA;
                buttonB = gamePad.buttonB;
                haveGamePad = xAxis && yAxis && buttonA && buttonB;
                if (!haveGamePad) {
                    xAxis   = nil;
                    yAxis   = nil;
                    buttonA = nil;
                    buttonB = nil;
                }
            }
        }
    }

    ((GLView *)self.view).needsDisplay = YES;
}

@end
