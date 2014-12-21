//
//  main.m
//  kxm
//
//  Created by Kai Hergenroether on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <Vectoid/Vector.h>
#include <Vectoid/Transform.h>

#import <UIKit/UIKit.h>

#import "KXMAppDelegate.h"


using kxm::Vectoid::Vector;
using kxm::Vectoid::Transform;


int main(int argc, char *argv[])
{
    Vector vector;
    Transform transform;
    
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([KXMAppDelegate class]));
    }
}
