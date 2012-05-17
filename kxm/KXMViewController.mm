//
//  KXMViewController.m
//  kxm
//
//  Created by Kai Hergenroether on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#import "KXMViewController.h"

#include <kxm/Vectoid/PerspectiveProjection.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Game/TaskList.h>
#include <kxm/Game/FrameTimeTask.h>
#include <kxm/Game/AccelerometerTask.h>
#include <kxm/Zarch/LanderGeometry.h>
#include <kxm/Zarch/ZarchTerrain.h>
#include <kxm/Zarch/ThrusterParticlesGeometry.h>
#include <kxm/Zarch/LanderTask.h>
#include <kxm/Zarch/CameraTask.h>
#include <kxm/Zarch/TerrainTask.h>
#include <kxm/Zarch/ThrusterParticlesTask.h>
#include <kxm/Zarch/MapParameters.h>

#include <boost/shared_ptr.hpp>

using namespace kxm::Vectoid;
using namespace kxm::Game;
using namespace kxm::Zarch;
using boost::shared_ptr;


@interface KXMViewController () {
    EAGLContext                       *glContext;
    shared_ptr<PerspectiveProjection> projection;
    shared_ptr<TaskList>              taskList;
    shared_ptr<AccelerometerTask>     accelerometerTask;
    shared_ptr<LanderTask>            landerTask;
    CGFloat                           width, height;
    bool                              accelerometerOverride;
    float                             accelerometerOverrideStartX, accelerometerOverrideStartY;
}

- (void)setupGL;
- (void)tearDownGL;

@end


@implementation KXMViewController

- (void)dealloc {
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
    
    [self setupGL];
    
    //self.preferredFramesPerSecond = 10;
    
    accelerometerOverride = true;
    
    UILongPressGestureRecognizer *pressRecognizer
        = [[UILongPressGestureRecognizer alloc] initWithTarget: self
                                                        action: @selector(handlePress:)];
    pressRecognizer.minimumPressDuration = .001f;
    [view addGestureRecognizer: pressRecognizer];
    [pressRecognizer release];
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
    shared_ptr<ZarchTerrain> terrain(new ZarchTerrain(24, 24, 1.0f, 12, 12));
    camera->AddChild(shared_ptr<Geode>(new Geode(terrain)));
    shared_ptr<Particles> thrusterParticles(new Particles());
    camera->AddChild(
        shared_ptr<Geode>(new Geode(shared_ptr<ThrusterParticlesGeometry>(
            new ThrusterParticlesGeometry(thrusterParticles)))));
    
    taskList = shared_ptr<TaskList>(new TaskList());
    shared_ptr<FrameTimeTask> timeTask(new FrameTimeTask());
    taskList->Add(timeTask);
    accelerometerTask = shared_ptr<AccelerometerTask>(new AccelerometerTask());
    taskList->Add(accelerometerTask);
    landerTask = shared_ptr<LanderTask>(new LanderTask(
        landerCoordSys, timeTask->TimeInfo(), accelerometerTask->Gravity(), mapParameters));
    taskList->Add(landerTask);
    taskList->Add(shared_ptr<CameraTask>(new CameraTask(camera, landerTask->LanderState())));
    taskList->Add(shared_ptr<TerrainTask>(new TerrainTask(terrain, landerTask->LanderState())));
    taskList->Add(
        shared_ptr<ThrusterParticlesTask>(new ThrusterParticlesTask(
            thrusterParticles, landerTask->LanderState(), timeTask->TimeInfo(), mapParameters)));
}

- (void)tearDownGL {
    [EAGLContext setCurrentContext: glContext];
    
    taskList.reset();
    projection.reset();
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update {
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
            landerTask->FireThruster(true);
            if (accelerometerOverride) {
                CGPoint position = [pressRecognizer locationInView: self.view];
                accelerometerOverrideStartX = (float)position.x;
                accelerometerOverrideStartY = (float)position.y;
                accelerometerTask->EnablePanningOverride(true);
            }
            break;
        case UIGestureRecognizerStateChanged:
            if (accelerometerOverride) {
                CGPoint position = [pressRecognizer locationInView: self.view];
                accelerometerTask->UpdatePanningOverride(
                    (float)position.x - accelerometerOverrideStartX,
                    (float)position.y - accelerometerOverrideStartY);
            }
            break;
        case UIGestureRecognizerStateEnded:
        default:
            landerTask->FireThruster(false);
            if (accelerometerOverride) {
                accelerometerTask->EnablePanningOverride(false);
            }
            break;
    }
}

@end
