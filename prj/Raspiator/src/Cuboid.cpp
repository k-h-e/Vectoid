#include "Cuboid.h"

#include <cassert>
#include <kxm/Core/NumberTools.h>
#include <Vectoid/Transform.h>

using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace Raspiator {

Cuboid::Cuboid(float width, float height, float depth, const kxm::Vectoid::Vector &color)
        : color_(color) {
    Resize(width, height, depth);
}

void Cuboid::Render(RenderContext *context) {
    glEnable(GL_LIGHTING);
   	glEnableClientState(GL_VERTEX_ARRAY);
   	glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &vertices_[0]);
    glNormalPointer(GL_FLOAT, 0, &normals_[0]);
    GLfloat color[4];
    color[0] = color_.x;  color[1] = color_.y;  color[2] = color_.z;  color[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisable(GL_LIGHTING);
}

void Cuboid::Resize(float width, float height, float depth) {
    assert(width  > 0.0f);
    assert(height > 0.0f);
    assert(depth  > 0.0f);

    width  *= .5f;
    height *= .5f;
    depth  *= .5f;

    vertices_.resize(6 * 18);
    normals_.resize(6 * 18);
    GLfloat *ptr  = &vertices_[0],
            *nptr = &normals_[0];
    *ptr++  = -width;    *ptr++  = -height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ =  1.0f;
    *ptr++  =  width;    *ptr++  = -height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ =  1.0f;
    *ptr++  =  width;    *ptr++  =  height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ =  1.0f;

    *ptr++  = -width;    *ptr++  = -height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ =  1.0f;
    *ptr++  =  width;    *ptr++  =  height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ =  1.0f;
    *ptr++  = -width;    *ptr++  =  height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ =  1.0f;


    *ptr++  =  width;    *ptr++  = -height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ = -1.0f;
    *ptr++  = -width;    *ptr++  = -height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ = -1.0f;
    *ptr++  = -width;    *ptr++  =  height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ = -1.0f;

    *ptr++  =  width;    *ptr++  = -height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ = -1.0f;
    *ptr++  = -width;    *ptr++  =  height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ = -1.0f;
    *ptr++  =  width;    *ptr++  =  height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ =  0.0f;      *nptr++ = -1.0f;


    *ptr++  = -width;    *ptr++  = -height;    *ptr++  = -depth;
    *nptr++ = -1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;
    *ptr++  = -width;    *ptr++  = -height;    *ptr++  =  depth;
    *nptr++ = -1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;
    *ptr++  = -width;    *ptr++  =  height;    *ptr++  =  depth;
    *nptr++ = -1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;

    *ptr++  = -width;    *ptr++  = -height;    *ptr++  = -depth;
    *nptr++ = -1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;
    *ptr++  = -width;    *ptr++  =  height;    *ptr++  =  depth;
    *nptr++ = -1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;
    *ptr++  = -width;    *ptr++  =  height;    *ptr++  = -depth;
    *nptr++ = -1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;


    *ptr++  =  width;    *ptr++  = -height;    *ptr++  =  depth;
    *nptr++ =  1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;
    *ptr++  =  width;    *ptr++  = -height;    *ptr++  = -depth;
    *nptr++ =  1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;
    *ptr++  =  width;    *ptr++  =  height;    *ptr++  = -depth;
    *nptr++ =  1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;

    *ptr++  =  width;    *ptr++  = -height;    *ptr++  =  depth;
    *nptr++ =  1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;
    *ptr++  =  width;    *ptr++  =  height;    *ptr++  = -depth;
    *nptr++ =  1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;
    *ptr++  =  width;    *ptr++  =  height;    *ptr++  =  depth;
    *nptr++ =  1.0f;     *nptr++ =  0.0f;      *nptr++ =  0.0f;


    *ptr++  = -width;    *ptr++  =  height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ =  1.0f;      *nptr++ =  0.0f;
    *ptr++  = -width;    *ptr++  =  height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ =  1.0f;      *nptr++ =  0.0f;
    *ptr++  =  width;    *ptr++  =  height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ =  1.0f;      *nptr++ =  0.0f;

    *ptr++  = -width;    *ptr++  =  height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ =  1.0f;      *nptr++ =  0.0f;
    *ptr++  =  width;    *ptr++  =  height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ =  1.0f;      *nptr++ =  0.0f;
    *ptr++  =  width;    *ptr++  =  height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ =  1.0f;      *nptr++ =  0.0f;


    *ptr++  = -width;    *ptr++  = -height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ = -1.0f;      *nptr++ =  0.0f;
    *ptr++  = -width;    *ptr++  = -height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ = -1.0f;      *nptr++ =  0.0f;
    *ptr++  =  width;    *ptr++  = -height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ = -1.0f;      *nptr++ =  0.0f;

    *ptr++  = -width;    *ptr++  = -height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ = -1.0f;      *nptr++ =  0.0f;
    *ptr++  =  width;    *ptr++  = -height;    *ptr++  = -depth;
    *nptr++ =  0.0f;     *nptr++ = -1.0f;      *nptr++ =  0.0f;
    *ptr++  =  width;    *ptr++  = -height;    *ptr++  =  depth;
    *nptr++ =  0.0f;     *nptr++ = -1.0f;      *nptr++ =  0.0f;
}

}    // Namespace Raspiator.

