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
}
@end


@implementation KXMGLView

- (void)setControlsState: (void *)aControlsState {
    controlsState = (ControlsState *)aControlsState;
}

- (void)touchesBegan: (NSSet *)touches withEvent: (UIEvent *)event {

    puts("touches began");
}

- (void)touchesMoved: (NSSet *)touches withEvent: (UIEvent *)event {
    puts("touches moved");
}

- (void)touchesEnded: (NSSet *)touches withEvent: (UIEvent *)event {
    puts("touches ended");
}

- (void)touchesCancelled: (NSSet *)touches withEvent: (UIEvent *)event {
    puts("touches cancelled");
}


@end
