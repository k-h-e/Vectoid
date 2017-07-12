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
    GCControllerAxisInput     *xAxis,           // Valid <=> haveGamePad.
                              *yAxis;           // Valid <=> haveGamePad.
    GCControllerButtonInput   *rightTrigger,    // Valid <=> haveGamePad.
                              *buttonA;         // Valid <=> haveGamePad.
    bool                      mouseCaptured;
    float                     mouseDeltaX,
                              mouseDeltaY;
    bool                      mouseLeftButtonDown;
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

- (void)mouseDown: (NSEvent *)event {
    mouseLeftButtonDown = true;
}

- (void)mouseUp: (NSEvent *)event {
    mouseLeftButtonDown = false;
}

- (void)mouseDragged: (NSEvent *)event {
    mouseDeltaX += (float)event.deltaX;
    mouseDeltaY += (float)event.deltaY;
}

- (void)mouseMoved: (NSEvent *)event {
    mouseDeltaX += (float)event.deltaX;
    mouseDeltaY += (float)event.deltaY;
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
        const float maxLength = 1000.0f;
        
        Vector direction(mouseDeltaX, mouseDeltaY, 0.0f);
        float length = direction.Length();
        if (length > 0.0f) {
            float scale  = 1.0f/length;
            if (length > maxLength) {
                length = maxLength;
            }
            scale *= length/maxLength;
        
            controlsState->orientation = scale * direction;
            
            std::printf("length=%f\n", length/maxLength);
        }
        else {
            controlsState->orientation = Vector();
        }
    
        controlsState->thruster    = mouseLeftButtonDown;
        controlsState->trigger     = false;
    
        mouseDeltaX = 0.0f;
        mouseDeltaY = 0.0f;
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

    ((GLView *)self.view).needsDisplay = YES;
}

@end
