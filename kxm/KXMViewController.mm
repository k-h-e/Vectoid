//
//  KXMViewController.m
//  kxm
//
//  Created by Kai Hergenroether on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#import "KXMViewController.h"

#include <boost/shared_ptr.hpp>

#import <CoreMotion/CMMotionManager.h>

#include <kxm/Vectoid/PerspectiveProjection.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Vectoid/ParticlesGeometry.h>
#include <kxm/Game/TaskList.h>
#include <kxm/Game/FrameTimeTask.h>
#include <kxm/Zarch/LanderGeometry.h>
#include <kxm/Zarch/ZarchTerrain.h>
#include <kxm/Zarch/LanderTask.h>
#include <kxm/Zarch/CameraTask.h>
#include <kxm/Zarch/TerrainTask.h>
#include <kxm/Zarch/ThrusterParticlesTask.h>
#include <kxm/Zarch/ShotsTask.h>
#include <kxm/Zarch/StarFieldTask.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/ControlsState.h>

#import "KXMGLView.h"

using namespace kxm::Vectoid;
using namespace kxm::Game;
using namespace kxm::Zarch;
using boost::shared_ptr;


@interface KXMViewController () {
    EAGLContext                       *glContext;
    shared_ptr<PerspectiveProjection> projection;
    shared_ptr<TaskList>              taskList;
    shared_ptr<ControlsState>         controlsState;
    CGFloat                           width, height;
    CMMotionManager                   *motionManager;
    Transform                         calibrationTransform;
    bool                              accelerometerOverride;
    float                             accelerometerOverrideStartX, accelerometerOverrideStartY;
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
    GLKView *view = (GLKView *)self.view;
    view.context  = glContext;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    motionManager        = [[CMMotionManager alloc] init];
    calibrationTransform = Transform(XAxis, 40.0f);
    
    controlsState = shared_ptr<ControlsState>(new ControlsState());
    [(KXMGLView *)view setControlsState: controlsState.get()];
    view.multipleTouchEnabled = YES;
    
    [self setupGL];
    
    //self.preferredFramesPerSecond = 10;
    accelerometerOverride = true;
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
    
    shared_ptr<MapParameters> mapParameters(new MapParameters());    
    
    projection = shared_ptr<PerspectiveProjection>(new PerspectiveProjection());
    projection->SetWindowSize(11.0f);
    projection->SetViewingDepth(11.0f);
    projection->SetEyepointDistance(11.0f);
    shared_ptr<Camera> camera(new Camera());
    projection->AddChild(camera);
    shared_ptr<CoordSys> landerCoordSys(new CoordSys());
    camera->AddChild(landerCoordSys);
    shared_ptr<LanderGeometry> landerGeometry(new LanderGeometry());
    landerCoordSys->AddChild(shared_ptr<Geode>(new Geode(landerGeometry)));
    shared_ptr<ZarchTerrain> terrain(new ZarchTerrain(mapParameters));
    camera->AddChild(shared_ptr<Geode>(new Geode(terrain)));
    shared_ptr<Particles> thrusterParticles(new Particles()),
                          shotsParticles(new Particles()),
                          starFieldParticles(new Particles());
    camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesGeometry>(
        new ParticlesGeometry(thrusterParticles)))));
    camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesGeometry>(
        new ParticlesGeometry(shotsParticles)))));
    camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesGeometry>(
        new ParticlesGeometry(starFieldParticles)))));
    
    taskList = shared_ptr<TaskList>(new TaskList());
    shared_ptr<FrameTimeTask> timeTask(new FrameTimeTask());
    taskList->Add(timeTask);
    shared_ptr<LanderTask> landerTask(new LanderTask(
        landerCoordSys, timeTask->TimeInfo(), controlsState, terrain, mapParameters));
    taskList->Add(landerTask);
    shared_ptr<CameraTask> cameraTask(new CameraTask(camera, landerTask->LanderState(),
                                                     mapParameters));
    taskList->Add(cameraTask);
    taskList->Add(shared_ptr<TerrainTask>(new TerrainTask(terrain, landerTask->LanderState())));
    taskList->Add(shared_ptr<ThrusterParticlesTask>(new ThrusterParticlesTask(
        thrusterParticles, landerTask->LanderState(), timeTask->TimeInfo(), mapParameters)));
    taskList->Add(shared_ptr<ShotsTask>(new ShotsTask(
        shotsParticles, landerTask->LanderState(), timeTask->TimeInfo(), mapParameters)));
    taskList->Add(shared_ptr<StarFieldTask>(new StarFieldTask(
        starFieldParticles, cameraTask->CameraState(), mapParameters)));
    
    [motionManager startDeviceMotionUpdates];
}

- (void)tearDownGL {
    [EAGLContext setCurrentContext: glContext];
    
    taskList.reset();
    projection.reset();
    
    [motionManager stopDeviceMotionUpdates];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update {
    if (!accelerometerOverride) {
        CMAcceleration gravity = motionManager.deviceMotion.gravity;
        Vector orientationInput(gravity.x, gravity.y, gravity.z);
        calibrationTransform.ApplyTo(&orientationInput);
        controlsState->orientationInput = orientationInput;
    }
    
    taskList->Execute();
}

- (void)glkView: (GLKView *)view drawInRect: (CGRect)rect {
    CGSize size = rect.size;
    if ((size.width != width) || (size.height != height)) {
        width  = size.width;
        height = size.height;
        projection->SetViewPort((float)width, (float)height);
        std::printf("view port set, size=(%d,%d)\n", (int)width, (int)height);
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projection->Render(0);
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
