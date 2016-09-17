//
//  TestTriangle.h
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KXM_VECTOID_TESTTRIANGLE_H_
#define KXM_VECTOID_TESTTRIANGLE_H_


#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/GeometryInterface.h>


namespace kxm {
namespace Vectoid {

//! Simple triangle geometry for testing purposes.
/*! 
 *  \ingroup Vectoid
 */ 
class TestTriangle : public virtual GeometryInterface {
  public:
    TestTriangle();
    void Render(RenderContext *context);
    
  private:
    TestTriangle(const TestTriangle &other);
    TestTriangle &operator=(const TestTriangle &other);
    static const GLfloat vertices[9];
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_TESTTRIANGLE_H_
