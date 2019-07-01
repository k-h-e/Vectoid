//
//  VideoViewController.m
//  MacZarch
//
//  Created by Kai Hergenröther on 07.05.17.
//  Copyright © 2017 Kai Hergenröther. All rights reserved.
//

#import "VideoViewController.h"

#include <memory>
#import <GameController/GameController.h>
#include <kxm/Core/logging.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/Zarch.h>
#include <kxm/Zarch/ControlsState.h>
#import "VideoView.h"

using namespace std;
using namespace kxm::Vectoid;
using namespace kxm::Zarch;

@interface VideoViewController () {
    shared_ptr<Zarch>         zarch;
    shared_ptr<ControlsState> controlsState;
    NSTimer                   *timer;
    bool                      haveGamePad;
    GCControllerAxisInput     *xAxis,           // Valid <=> haveGamePad.
                              *yAxis;           // Valid <=> haveGamePad.
    GCControllerButtonInput   *rightTrigger,    // Valid <=> haveGamePad.
                              *buttonA;         // Valid <=> haveGamePad.
    bool                      mouseCaptured;
    float                     mouseX,
                              mouseY;
    bool                      mouseLeftButtonDown,
                              mouseRightButtonDown;
}

@end

@implementation VideoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    zarch         = make_shared<Zarch>([(id<VideoView>)self.view getRenderTarget]);
    controlsState = make_shared<ControlsState>();
    [(id<VideoView>)self.view setZarch: zarch controlsState: controlsState];
    
    timer = [NSTimer timerWithTimeInterval: 1.0/60.0 target: self selector: @selector(handleTimer) userInfo: nil
                     repeats: YES];
    [[NSRunLoop currentRunLoop] addTimer: timer forMode: NSDefaultRunLoopMode];
}

- (void)mouseDown: (NSEvent *)event {
    mouseLeftButtonDown = true;
}
- (void)mouseUp: (NSEvent *)event {
    mouseLeftButtonDown = false;
}

- (void)rightMouseDown: (NSEvent *)event {
    mouseRightButtonDown = true;
}
- (void)rightMouseUp: (NSEvent *)event {
    mouseRightButtonDown = false;
}

- (void)mouseDragged: (NSEvent *)event {
    [self mouseMoved: event];
}
- (void)rightMouseDragged: (NSEvent *)event {
    [self mouseMoved: event];
}
- (void)mouseMoved: (NSEvent *)event {
    mouseX += (float)event.deltaX;
    mouseY += (float)event.deltaY;
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)handleTimer {
    /*
    if (haveGamePad) {
        float x = xAxis.value,
              y = yAxis.value;
        controlsState->orientation = Vector(x, y, 0.0f);
        controlsState->thruster    = rightTrigger.pressed;
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
                
                rightTrigger = gamePad.rightTrigger;
                buttonA = gamePad.buttonA;
                haveGamePad = xAxis && yAxis && rightTrigger && buttonA;
                if (!haveGamePad) {
                    xAxis        = nil;
                    yAxis        = nil;
                    rightTrigger = nil;
                    buttonA      = nil;
                }
            }
        }
    }
    */
    
    if (mouseCaptured) {
        const float maxRadius = 400.0f;
        Vector mouseVector(mouseX, -mouseY, 0.0f);
        float length = mouseVector.Length();
        if (length > maxRadius) {
            mouseVector = (maxRadius/length) * mouseVector;
        }
        mouseX = 0.0f;
        mouseY = 0.0f;
        
        controlsState->orientation = (1.0f/maxRadius) * mouseVector;
        controlsState->thruster    = mouseLeftButtonDown;
        controlsState->trigger     = mouseRightButtonDown;
    }
    else {
        NSWindow *window = [self.view window];
        if (window) {
            [window setAcceptsMouseMovedEvents: YES];
            CGAssociateMouseAndMouseCursorPosition(false);
            mouseCaptured = true;
            puts("mouse captured");
        }
    }

    kxm::Core::Log().Stream() << "triggering redraw" << endl;
    self.view.needsDisplay = YES;
}

@end
