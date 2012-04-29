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
#include <kxm/Vectoid/TestTriangle.h>
#include <kxm/Game/TaskList.h>
#include <kxm/Zarch/ZarchTerrain.h>
#include <kxm/Zarch/LanderTask.h>
#include <kxm/Zarch/CameraTask.h>
#include <kxm/Zarch/TerrainTask.h>

#include <boost/shared_ptr.hpp>

using namespace kxm::Vectoid;
using namespace kxm::Game;
using namespace kxm::Zarch;
using boost::shared_ptr;


@interface KXMViewController () {
    EAGLContext                       *glContext;
    shared_ptr<PerspectiveProjection> projection;
    shared_ptr<TaskList>              taskList;
    CGFloat                           width, height;
    float                             animationAngle;
}

- (void)setupGL;
- (void)tearDownGL;

@end


@implementation KXMViewController

- (void)dealloc
{
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    glContext = [[[EAGLContext alloc] initWithAPI: kEAGLRenderingAPIOpenGLES1] autorelease];
    if (!glContext) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = glContext;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
    
    //self.preferredFramesPerSecond = 10;
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

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc. that aren't in use.
}

- (BOOL)shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations.
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (void)setupGL
{
    [EAGLContext setCurrentContext: glContext];
    
    glEnable(GL_DEPTH_TEST);
    
    projection = shared_ptr<PerspectiveProjection>(new PerspectiveProjection());
    projection->SetWindowSize(11.0f);
    projection->SetViewingDepth(11.0f);
    projection->SetEyepointDistance(11.0f);
    shared_ptr<Camera> camera(new Camera());
    projection->AddChild(camera);
    shared_ptr<CoordSys> coordSys(new CoordSys());
    camera->AddChild(coordSys);
    shared_ptr<TestTriangle> testTriangle(new TestTriangle());
    coordSys->AddChild(shared_ptr<Geode>(new Geode(testTriangle)));
    shared_ptr<ZarchTerrain> terrain(new ZarchTerrain(24, 24, 1.0f, 12, 12));
    camera->AddChild(shared_ptr<Geode>(new Geode(terrain)));
    
    taskList = shared_ptr<TaskList>(new TaskList());
    shared_ptr<LanderTask> landerTask(new LanderTask(coordSys));
    taskList->Add(shared_ptr<LanderTask>(landerTask));
    taskList->Add(shared_ptr<CameraTask>(new CameraTask(camera, landerTask->LanderTransform())));
    taskList->Add(shared_ptr<TerrainTask>(new TerrainTask(terrain, landerTask->LanderTransform())));
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext: glContext];
    
    taskList.reset();
    projection.reset();
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    taskList->Execute();
}

- (void)glkView: (GLKView *)view drawInRect: (CGRect)rect
{
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

@end
