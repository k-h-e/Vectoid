//
//  KXMGLView.m
//  kxm
//
//  Created by Kai Hergenroether on 6/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#import "KXMGLView.h"

#include <boost/shared_ptr.hpp>

#include <kxm/Zarch/ControlsState.h>

using namespace kxm::Zarch;


@interface KXMGLView () {
    ControlsState *controlsState;
    UITouch       *leftTouch, *rightTouch;
}
@end


@implementation KXMGLView

- (void)setControlsState: (void *)aControlsState {
    controlsState = (ControlsState *)aControlsState;
}

- (void)touchesBegan: (NSSet *)touches withEvent: (UIEvent *)event {
    for (UITouch *touch in touches) {
        CGPoint position = [touch locationInView: self];
        if (position.x < self.frame.size.width / 2.0f) {
            if (!leftTouch) {
                leftTouch = touch;
                controlsState->firingRequested = true;
            }
        }
        else {
            if (!rightTouch) {
                rightTouch = touch;
                controlsState->thrusterRequested = true;
            }
        }
    } 
}

- (void)touchesMoved: (NSSet *)touches withEvent: (UIEvent *)event {
    // nop
}

- (void)touchesEnded: (NSSet *)touches withEvent: (UIEvent *)event {
    for (UITouch *touch in touches) {
        if (touch == leftTouch) {
            leftTouch = nil;
            controlsState->firingRequested = false;
        }
        else if (touch == rightTouch) {
            rightTouch = nil;
            controlsState->thrusterRequested = false;
        }
    }
}

- (void)touchesCancelled: (NSSet *)touches withEvent: (UIEvent *)event {
    [self touchesEnded: touches withEvent: event];
}


@end
