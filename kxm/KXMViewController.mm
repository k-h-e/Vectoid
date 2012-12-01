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
#include <kxm/Vectoid/PerspectiveProjection.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Vectoid/ParticlesRenderer.h>
#include <kxm/Vectoid/AgeColoredParticles.h>
#include <kxm/Game/EventPool.h>
#include <kxm/Game/EventQueue.h>
#include <kxm/Game/Processes.h>
#include <kxm/Game/FrameTimeProcess.h>
#include <kxm/Zarch/LanderGeometry.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/TerrainRenderer.h>
#include <kxm/Zarch/LanderProcess.h>
#include <kxm/Zarch/CameraProcess.h>
#include <kxm/Zarch/TerrainProcess.h>
#include <kxm/Zarch/ThrusterParticlesProcess.h>
#include <kxm/Zarch/ShotsProcess.h>
#include <kxm/Zarch/StarFieldProcess.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/events.h>
#include <kxm/Zarch/processes.h>

#import "KXMGLView.h"

using namespace std;
using namespace boost;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;
using namespace kxm::Zarch;


@interface KXMViewController () {
    EAGLContext                                *glContext;
    shared_ptr<PerspectiveProjection>          projection;
    shared_ptr<EventQueue<ZarchEvent::Type> >  eventQueue;
    shared_ptr<Processes<ZarchProcess::Type> > processes;
    shared_ptr<ControlsState>                  controlsState;
    CGFloat                                    width, height;
    CMMotionManager                            *motionManager;
    Transform                                  calibrationTransform;
    bool                                       accelerometerOverride;
    float                                      accelerometerOverrideStartX,
                                               accelerometerOverrideStartY;
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
    shared_ptr<Terrain> terrain(new Terrain(mapParameters));
    shared_ptr<TerrainRenderer> terrainRenderer(new TerrainRenderer(terrain, mapParameters));
    camera->AddChild(shared_ptr<Geode>(new Geode(terrainRenderer)));
    shared_ptr<Particles> thrusterParticles(new Particles()),
                          shotsParticles(new Particles()),
                          starFieldParticles(new Particles());
    camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<AgeColoredParticles>(
        new AgeColoredParticles(thrusterParticles)))));
    camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesRenderer>(
        new ParticlesRenderer(shotsParticles)))));
    camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesRenderer>(
        new ParticlesRenderer(starFieldParticles)))));
    
    processes = shared_ptr<Processes<ZarchProcess::Type> >(new Processes<ZarchProcess::Type>());
    FrameTimeProcess *timeProcess = new FrameTimeProcess();
    processes->AddProcess(timeProcess);
    LanderProcess *landerProcess = new LanderProcess(
        landerCoordSys, timeProcess->TimeInfo(), controlsState, terrain, mapParameters);
    processes->AddProcess(landerProcess);
    CameraProcess *cameraProcess = new CameraProcess(camera, landerProcess->LanderState(),
                                                     mapParameters);
    processes->AddProcess(cameraProcess);
    processes->AddProcess(new TerrainProcess(terrainRenderer, landerProcess->LanderState()));
    processes->AddProcess(
        new ThrusterParticlesProcess(thrusterParticles, landerProcess->LanderState(),
                                     timeProcess->TimeInfo(), mapParameters));
    processes->AddProcess(
        new ShotsProcess(shotsParticles, landerProcess->LanderState(), timeProcess->TimeInfo(),
                         mapParameters));
    processes->AddProcess(new StarFieldProcess(starFieldParticles, cameraProcess->CameraState(),
                          mapParameters));
    
    eventQueue = shared_ptr<EventQueue<ZarchEvent::Type> >(new EventQueue<ZarchEvent::Type>());
    eventQueue->RegisterEventType(ZarchEvent::ActorEvent,
                                  shared_ptr<EventPoolInterface>(new EventPool<ActorEvent>()));
    eventQueue->RegisterEventType(ZarchEvent::PositionEvent,
                                  shared_ptr<EventPoolInterface>(new EventPool<PositionEvent>()));
    
    [motionManager startDeviceMotionUpdates];
}

- (void)tearDownGL {
    [EAGLContext setCurrentContext: glContext];
    
    processes.reset();
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
    
    processes->ExecuteProcesses();
    
    eventQueue->ProcessEvents();
}

- (void)glkView: (GLKView *)view drawInRect: (CGRect)rect {
    CGSize size = rect.size;
    if ((size.width != width) || (size.height != height)) {
        width  = size.width;
        height = size.height;
        projection->SetViewPort((float)width, (float)height);
        Log().Stream() << "viewport set" << ", size=(" << (int)width << "," << (int)height << ")"
                       << endl;
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
