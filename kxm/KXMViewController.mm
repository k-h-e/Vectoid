//
//  KXMViewController.m
//  kxm
//
//  Created by Kai Hergenroether on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#import "KXMViewController.h"

#include <string>
#include <sstream>

#include <boost/shared_ptr.hpp>

#import <CoreMotion/CMMotionManager.h>

#include <kxm/Core/logging.h>
#include <kxm/Core/POSIXThreadingFactory.h>
#include <kxm/Game/FrameTimeProcess.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/Zarch.h>

#import "KXMGLView.h"

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;
using namespace kxm::Zarch;

using boost::shared_ptr;


@interface KXMViewController () {
    EAGLContext                                       *glContext;
    CGFloat                                           width, height;
    CMMotionManager                                   *motionManager;
    Transform                                         calibrationTransform;
    bool                                              accelerometerOverride;
    float                                             accelerometerOverrideStartX,
                                                      accelerometerOverrideStartY;
    
    shared_ptr<Zarch>                                 zarch;
    FrameTimeProcess                                  timeProcess;
    shared_ptr<const FrameTimeProcess::FrameTimeInfo> frameTimeInfo;
    shared_ptr<ControlsState>                         controlsState;
}

- (void)setupGL;
- (void)tearDownGL;

@end


@implementation KXMViewController

- (void)dealloc {
    [motionManager release];
    [super dealloc];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    glContext = [[[EAGLContext alloc] initWithAPI: kEAGLRenderingAPIOpenGLES1] autorelease];
    if (!glContext) {
        NSLog(@"Failed to create ES context");
    }
    GLKView *view            = (GLKView *)self.view;
    view.context             = glContext;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    motionManager        = [[CMMotionManager alloc] init];
    calibrationTransform = Transform(XAxis, 40.0f);
    
    controlsState = shared_ptr<ControlsState>(new ControlsState());
    [(KXMGLView *)view setControlsState: controlsState.get()];
    view.multipleTouchEnabled = YES;
    
    [self setupGL];
    
    //self.preferredFramesPerSecond = 10;
    //accelerometerOverride = true;
}

- (void)viewDidUnload
{    
    [super viewDidUnload];
    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == glContext) {
        [EAGLContext setCurrentContext: nil];
    }
    glContext = nil;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc. that aren't in use.
}

- (BOOL)shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    }
    else {
        return YES;
    }
}

- (void)setupGL {
    [EAGLContext setCurrentContext: glContext];
    glEnable(GL_DEPTH_TEST);
    
    shared_ptr<ThreadingFactoryInterface> threadingFactory(new POSIXThreadingFactory());
    zarch = shared_ptr<Zarch>(new Zarch(threadingFactory));
    frameTimeInfo = timeProcess.TimeInfo();
    [motionManager startDeviceMotionUpdates];
}

- (void)tearDownGL {
    [EAGLContext setCurrentContext: glContext];
    
    zarch.reset();
    
    [motionManager stopDeviceMotionUpdates];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update {
    timeProcess.Execute(Process::Context());
    if (!accelerometerOverride) {
        CMAcceleration gravity = motionManager.deviceMotion.gravity;
        Vector orientationInput(gravity.x, gravity.y, gravity.z);
        calibrationTransform.ApplyTo(&orientationInput);
        controlsState->orientationInput = orientationInput;
    }
    
    zarch->Execute(*frameTimeInfo, *controlsState);
}

- (void)glkView: (GLKView *)view drawInRect: (CGRect)rect {
    CGSize size = rect.size;
    if ((size.width != width) || (size.height != height)) {
        width  = size.width;
        height = size.height;
        zarch->SetViewPort(width, height);
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    zarch->RenderFrame();
}

- (void)handlePress: (UIGestureRecognizer *)recognizer {
    UILongPressGestureRecognizer *pressRecognizer = (UILongPressGestureRecognizer *)recognizer;
    UIGestureRecognizerState state = pressRecognizer.state;
    switch (state) {
        case UIGestureRecognizerStateBegan:
            controlsState->thrusterRequested = true;
            if (accelerometerOverride) {
                CGPoint position = [pressRecognizer locationInView: self.view];
                accelerometerOverrideStartX = (float)position.x;
                accelerometerOverrideStartY = (float)position.y;
                controlsState->orientationInput = Vector(0.0f, 0.0f, -1.0f);
            }
            break;
        case UIGestureRecognizerStateChanged:
            if (accelerometerOverride) {
                CGPoint position = [pressRecognizer locationInView: self.view];
                controlsState->orientationInput = Vector(
                    (float)position.x - accelerometerOverrideStartX,
                    -((float)position.y - accelerometerOverrideStartY),
                    -200.0f);
                controlsState->orientationInput.TryNormalize();
            }
            break;
        case UIGestureRecognizerStateEnded:
        default:
            controlsState->thrusterRequested = false;
            break;
    }
}

@end
