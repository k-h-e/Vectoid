#import "GLView.h"

#include <OpenGL/gl.h>
#include <memory>
#include <kxm/Zarch/Zarch.h>
#include <kxm/Zarch/ControlsState.h>

using namespace std;
using namespace kxm::Zarch;

@interface GLView () {
    shared_ptr<Zarch>         zarch;
    shared_ptr<ControlsState> controlsState;
    CGSize                    size;
}
@end

@implementation GLView

- (void)setZarch: (const std::shared_ptr<kxm::Zarch::Zarch> &)aZarch
        controlsState: (const std::shared_ptr<kxm::Zarch::ControlsState> &)aControlsState {
    zarch         = aZarch;
    controlsState = aControlsState;
    size.width  = 0.0f;
    size.height = 0.0f;
}

- (void)drawRect: (NSRect)bounds {
    if (zarch.get()) {
        CGSize newSize = bounds.size;
        if ((newSize.width != size.width) || (newSize.height != size.height)) {
            NSLog(@"resizing...");
            size.width  = newSize.width;
            size.height = newSize.height;
            zarch->SetViewPort((int)(size.width +.5f), (int)(size.height + .5f));
            
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glEnable(GL_DEPTH_TEST);
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        zarch->PrepareFrame(*controlsState);
        zarch->RenderFrame();
        glFlush();
    }
}

/*
- (void)touchesBegan: (NSSet *)touches withEvent: (UIEvent *)event {
    for (UITouch *touch in touches) {
        CGPoint position = [touch locationInView: self];
        if (position.x < self.frame.size.width / 2.0f) {
            if (!leftTouch) {
                leftTouch = touch;
                controlsState->trigger = true;
            }
        }
        else {
            if (!rightTouch) {
                rightTouch = touch;
                controlsState->thruster = true;
            }
        }
    } 
}

- (void)touchesMoved: (NSSet *)touches withEvent: (UIEvent *)event {
    // Nop.
}

- (void)touchesEnded: (NSSet *)touches withEvent: (UIEvent *)event {
    for (UITouch *touch in touches) {
        if (touch == leftTouch) {
            leftTouch = nil;
            controlsState->trigger = false;
        }
        else if (touch == rightTouch) {
            rightTouch = nil;
            controlsState->thruster = false;
        }
    }
}

- (void)touchesCancelled: (NSSet *)touches withEvent: (UIEvent *)event {
    [self touchesEnded: touches withEvent: event];
}
*/

@end
