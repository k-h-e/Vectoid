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

#include <boost/shared_ptr.hpp>

using namespace kxm::Vectoid;
using boost::shared_ptr;


@interface KXMViewController () {
    EAGLContext                       *glContext;
    shared_ptr<PerspectiveProjection> projection;
    shared_ptr<Camera>                camera;
    shared_ptr<CoordSys>              coordSys;   
    CGFloat                           width, height;
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
    projection->SetWindowSize(4.0f);
    projection->SetViewingDepth(4.0f);
    projection->SetEyepointDistance(4.0f);
    camera = shared_ptr<Camera>(new Camera());
    projection->AddChild(camera);
    coordSys = shared_ptr<CoordSys>(new CoordSys());
    camera->AddChild(coordSys);
    coordSys->SetPosition(Vector(0.0f, 0.0f, -2.0f));
    shared_ptr<TestTriangle> testTriangle(new TestTriangle());
    shared_ptr<Geode> geode(new Geode(testTriangle));
    coordSys->AddChild(geode);
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext: glContext];
    
    coordSys.reset();
    camera.reset();
    projection.reset();
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    coordSys->PrependTransform(Transform(YAxis, 3.0f));
    Vector position = coordSys->Position();
    position.x += .02f;
    if (position.x > 2.0f)
        position.x = -2.0f;
    coordSys->SetPosition(position);
    
    camera->PrependTransform(Transform(ZAxis, 1.0f));
}

- (void)glkView: (GLKView *)view drawInRect: (CGRect)rect
{
    glClearColor(0.0f, 0.0f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    CGSize size = rect.size;
    if ((size.width != width) || (size.height != height)) {
        width  = size.width;
        height = size.height;
        projection->SetViewPort((float)width, (float)height);
        std::printf("view port set, size=(%d,%d)\n", (int)width, (int)height);
    }
    projection->Render(0);
}

@end
